#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/videodev2.h>
#include <linux/clk.h>
#include <media/v4l2-device.h>
#include <media/v4l2-mediabus.h>
#include <linux/io.h>

#include "ov5647_mipi_regs.h"
#include "camera.h"
#include "sensor_helper.h"

MODULE_AUTHOR("YG");
MODULE_DESCRIPTION("A low-level driver for OV5647 sensors");
MODULE_LICENSE("GPL v2");

#define PWDN_ACTIVE_DELAY_MS	20

#define MIPI_CTRL00_CLOCK_LANE_GATE		BIT(5)
#define MIPI_CTRL00_LINE_SYNC_ENABLE		BIT(4)
#define MIPI_CTRL00_BUS_IDLE			BIT(2)
#define MIPI_CTRL00_CLOCK_LANE_DISABLE		BIT(0)

#define OV5647_SW_STANDBY		SOFTWARE_SLEEP_REG
#define OV5647_SW_RESET			SOFTWARE_RESET_REG
#define OV5647_REG_CHIPID_H		SC_CMMN_CHIP_ID_HIGH_REG_ADDR
#define OV5647_REG_CHIPID_L		SC_CMMN_CHIP_ID_LOW_REG_ADDR
#define OV5640_REG_PAD_OUT		SC_CMMN_PAD_OUT2_REG_ADDR
#define OV5647_REG_EXP_HI		EXPOSURE_EXPOSURE_0x3500
#define OV5647_REG_EXP_MID		EXPOSURE_EXPOSURE_0x3501
#define OV5647_REG_EXP_LO		EXPOSURE_EXPOSURE_0x3502
#define OV5647_REG_AEC_AGC		MANUAL_CTRL_0x3503
#define OV5647_REG_GAIN_HI		AGC_AGC_0x350A
#define OV5647_REG_GAIN_LO		AGC_AGC_0x350B
#define OV5647_REG_VTS_HI		TIMING_VTS_REG_ADDR
#define OV5647_REG_VTS_LO		TIMING_VTS_LSB_REG_ADDR
#define OV5647_REG_FRAME_OFF_NUMBER	0x4202
#define OV5647_REG_MIPI_CTRL00		MIPI_CTRL_00_REG_ADDR
#define OV5647_REG_MIPI_CTRL14		MIPI_CTRL_14_REG_ADDR
#define OV5647_REG_AWB			ISP_CTRL01_REG_ADDR
#define OV5647_REG_ISPCTRL3D		ISP_CTRL3D_REG_ADDR

#define REG_TERM 0xfffe
#define VAL_TERM 0xfe
#define REG_DLY  0xffff

/* OV5647 native and active pixel array size */
#define OV5647_NATIVE_WIDTH		2624U
#define OV5647_NATIVE_HEIGHT		1956U

#define OV5647_PIXEL_ARRAY_LEFT		16U
#define OV5647_PIXEL_ARRAY_TOP		16U
#define OV5647_PIXEL_ARRAY_WIDTH	2592U
#define OV5647_PIXEL_ARRAY_HEIGHT	1944U

#define OV5647_VBLANK_MIN		4
#define OV5647_VTS_MAX			32767

#define OV5647_EXPOSURE_MIN		4
#define OV5647_EXPOSURE_STEP		1
#define OV5647_EXPOSURE_DEFAULT		1000
#define OV5647_EXPOSURE_MAX		65535

#define MCLK              (24*1000*1000)
#define V4L2_IDENT_SENSOR 0x5647

#undef DEV_DBG_EN
#define DEV_DBG_EN 1

#define CHIP_ID_ADDR SC_CMMN_CHIP_ID_HIGH_REG_ADDR
#define CHIP_ID_ADDR_L SC_CMMN_CHIP_ID_LOW_REG_ADDR

#define SENSOR_FRAME_RATE 30

#define I2C_ADDR 0x6c

#define SENSOR_NAME "ov5647_mipi"

static const char * const ov5647_test_pattern_menu[] = {
	"Disabled",
	"Color Bars",
	"Color Squares",
	"Random Data",
};

static const u8 ov5647_test_pattern_val[] = {
	0x00,	/* Disabled */
	0x80,	/* Color Bars */
	0x82,	/* Color Squares */
	0x81,	/* Random Data */
};

static const struct regval_list sensor_oe_disable_regs[] = {
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
};

static const struct regval_list sensor_oe_enable_regs[] = {
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0f},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xe4},
};

//these are the registers that are not documented in the datasheet, but are needed for the sensor to work for some reason
#define OV5647_UNDOCUMENTED_MAGIC 	{0x3630, 0x2E},\
	{0x3632, 0xE2},\
	{0x3633, 0x23},\
	{0x3634, 0x44},\
	{0x3636, 0x06},\
	{0x3621, 0xE0},\
	{0x3600, 0x37},\
	{0x3704, 0xA0},\
	{0x3703, 0x5A},\
	{0x3715, 0x78},\
	{0x3717, 0x01},\
	{0x370B, 0x60},\
	{0x3705, 0x1A},\
	{0x3F05, 0x02},\
	{0x3F06, 0x10},\
	{0x3F01, 0x0A},\

/*
 * The default register settings
 */

static struct regval_list ov5647_2592x1944_10bpp[] = {
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1a},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x69},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{SRB_CTRL_REG_ADDR, 0xf5},
	{TIMING_TC_REG21_REG_ADDR, 0x06},
	{TIMING_TC_REG20_REG_ADDR, 0x00},
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x5b},
	{0x3618, 0x04},
	{LENC_CTRL00_REG_ADDR, 0x06},
	{ISP_CTRL02_REG_ADDR, 0x41},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44},
	{DEBUG_MODE_REG_301C_ADDR, 0xf8},
	{DEBUG_MODE_REG_301D_ADDR, 0xf0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},
	{TIMING_HTS_REG_ADDR, 0x0b},
	{TIMING_HTS_LSB_REG_ADDR, 0x1c},
	{TIMING_X_INC_REG_ADDR, 0x11},
	{TIMING_Y_INC_REG_ADDR, 0x11},
	{0x3708, 0x64},
	{0x3709, 0x12},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x07},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x04},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0x38},
	{TIMING_X_ADDR_START_REG_ADDR, 0x01},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x5C},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x01},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0xB2},
	{TIMING_X_ADDR_END_REG_ADDR, 0x08},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0xE3},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x05},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xF1},
	{TIMING_ISP_X_WIN_LSB_REG_ADDR, 0x04},
	{TIMING_ISP_Y_WIN_LSB_REG_ADDR, 0x02},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x28},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xf6},
	{B60_MAX_REG_ADDR, 0x08},
	{B50_MAX_REG_ADDR, 0x06},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x04},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{PCLK_PERIOD_REG_ADDR, 0x19},
	{MIPI_CTRL_00_REG_ADDR, 0x24},
	{MANUAL_CTRL_0x3503, 0x03},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0f},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xe4},
	{SOFTWARE_SLEEP_REG, 0x01},
};

static struct regval_list ov5647_1080p30_10bpp[] = {
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1a},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x62},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{SRB_CTRL_REG_ADDR, 0xf5},
	{TIMING_TC_REG21_REG_ADDR, 0x06},
	{TIMING_TC_REG20_REG_ADDR, 0x00},
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x5b},
	{0x3618, 0x04},
	{LENC_CTRL00_REG_ADDR, 0x06},
	{ISP_CTRL02_REG_ADDR, 0x41},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44},
	{DEBUG_MODE_REG_301C_ADDR, 0xf8},
	{DEBUG_MODE_REG_301D_ADDR, 0xf0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},
	{TIMING_HTS_REG_ADDR, 0x09},
	{TIMING_HTS_LSB_REG_ADDR, 0x70},
	{TIMING_X_INC_REG_ADDR, 0x11},
	{TIMING_Y_INC_REG_ADDR, 0x11},
	{0x3708, 0x64},
	{0x3709, 0x12},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x07},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x04},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0x38},
	{TIMING_X_ADDR_START_REG_ADDR, 0x01},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x5c},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x01},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0xb2},
	{TIMING_X_ADDR_END_REG_ADDR, 0x08},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0xe3},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x05},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xf1},
	{TIMING_ISP_X_WIN_LSB_REG_ADDR, 0x04},
	{TIMING_ISP_Y_WIN_LSB_REG_ADDR, 0x02},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x4b},
	{B60_STEP_HIGH_REG_ADDR, 0x01},
	{B60_STEP_LOW_REG_ADDR, 0x13},
	{B60_MAX_REG_ADDR, 0x04},
	{B50_MAX_REG_ADDR, 0x03},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x04},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{PCLK_PERIOD_REG_ADDR, 0x19},
	{MIPI_CTRL_00_REG_ADDR, 0x34},
	{MANUAL_CTRL_0x3503, 0x03},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0f},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xe4},
	{SOFTWARE_SLEEP_REG, 0x01},
};

static struct regval_list ov5647_2x2binned_10bpp[] = {
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1a},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x62},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{SRB_CTRL_REG_ADDR, 0xf5},
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},
	{0x370c, 0x03},
	{0x3612, 0x59},
	{0x3618, 0x00},
	{LENC_CTRL00_REG_ADDR, 0x06},
	{ISP_CTRL02_REG_ADDR, 0x41},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44},
	{DEBUG_MODE_REG_301C_ADDR, 0xf8},
	{DEBUG_MODE_REG_301D_ADDR, 0xf0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_X_ADDR_END_REG_ADDR, 0x0a},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x3f},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x07},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xa3},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x05},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x10},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x03},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xcc},
	{TIMING_HTS_REG_ADDR, 0x07},
	{TIMING_HTS_LSB_REG_ADDR, 0x68},
	{TIMING_ISP_X_WIN_LSB_REG_ADDR, 0x0c},
	{TIMING_ISP_Y_WIN_LSB_REG_ADDR, 0x06},
	{TIMING_X_INC_REG_ADDR, 0x31},
	{TIMING_Y_INC_REG_ADDR, 0x31},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x28},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xf6},
	{B60_MAX_REG_ADDR, 0x08},
	{B50_MAX_REG_ADDR, 0x06},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x04},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{PCLK_PERIOD_REG_ADDR, 0x16},
	{MIPI_CTRL_00_REG_ADDR, 0x24},
	{MANUAL_CTRL_0x3503, 0x03},
	{TIMING_TC_REG20_REG_ADDR, 0x41},
	{TIMING_TC_REG21_REG_ADDR, 0x07},
	{AGC_0x350A, 0x00},
	{AGC_0x350B, 0x10},
	{EXPOSURE_0x3500, 0x00},
	{EXPOSURE_0x3501, 0x1a},
	{EXPOSURE_0x3502, 0xf0},
	{0x3212, 0xa0},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0f},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xe4},
	{SOFTWARE_SLEEP_REG, 0x01},
};

static struct regval_list ov5647_640x480_10bpp[] = {
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x11},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x46},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{TIMING_TC_REG21_REG_ADDR, 0x07},
	{TIMING_TC_REG20_REG_ADDR, 0x41},
	{0x370c, 0x03},
	{0x3612, 0x59},
	{0x3618, 0x00},
	{LENC_CTRL00_REG_ADDR, 0x06},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},
	{DEBUG_MODE_REG_301D_ADDR, 0xf0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},
	{TIMING_HTS_REG_ADDR, 0x07},
	{TIMING_HTS_LSB_REG_ADDR, 0x3c},
	{TIMING_X_INC_REG_ADDR, 0x35},
	{TIMING_Y_INC_REG_ADDR, 0x35},
	{0x3708, 0x64},
	{0x3709, 0x52},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x02},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x01},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xe0},
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x10},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_X_ADDR_END_REG_ADDR, 0x0a},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x2f},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x07},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0x9f},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x2e},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xfb},
	{B60_MAX_REG_ADDR, 0x02},
	{B50_MAX_REG_ADDR, 0x01},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x02},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},
	{DEBUG_MODE_REG_301C_ADDR, 0xfc},
	{0x3636, 0x06},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SRB_CTRL_REG_ADDR, 0xf5},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1a},
	{DEBUG_MODE_REG_301C_ADDR, 0xf8},
	{MIPI_CTRL_00_REG_ADDR, 0x34},
	{MANUAL_CTRL_0x3503, 0x03},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0f},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xe4},
	{SOFTWARE_SLEEP_REG, 0x01},
};

static struct regval_list ov5647_640x480_custom_unclean[] = {
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x11},	//sets PLL1 to datasheet default
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x46},	//sets pll multiplier to 0x46 (4~252) = 70
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},	//sets PLL2 to 0 001(cp) 0001 (div)
	//{TIMING_TC_REG21_REG_ADDR, 0x07},	//sets the mirror modes: 00000 1 1 1 (all mirrored) [removed because useless]
	//{TIMING_TC_REG20_REG_ADDR, 0x41},	//more useless mirroring modes
	//{0x370c, 0x03},	//unknown
	//{0x3612, 0x59},	//unknown
	//{0x3618, 0x00},	//unknown
	{LENC_CTRL00_REG_ADDR, 0x06},	//disables lens correction (0b0000 0110) but enables the basic ISP functions like white balance
	{ISP_CTRL03_REG_ADDR, 0x08},	// 0b0000 1000, disables binning, enables buffer
	//{DIGC_CTRL0_REG_ADDR, 0x08},	//AGC related stuff, let's not touch that
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},  //sets all specific I/O enabled
	//{DEBUG_MODE_REG_301D_ADDR, 0xf0},	//why the debug register? don't touch that!
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},	//gain related stuff
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},	//gain related stuff
	//{CTRL01_50_60_HZ_DETECTION, 0x80},	//don't bother with strobe correction
	//{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},	//same thing here
	{TIMING_HTS_REG_ADDR, 0x07},	//sets the HTS msb for mipi, here it's 1852 so 0x073C in hex
	{TIMING_HTS_LSB_REG_ADDR, 0x3c},	//sets the HTS lsb for mipi
	{TIMING_X_INC_REG_ADDR, 0x35},
	{TIMING_Y_INC_REG_ADDR, 0x35},	//windowing stuff
	//{0x3708, 0x64},	//unk
	//{0x3709, 0x52},	//unk
	/*{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x02},	//we're in mipi not DVP, not needed
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x01},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xe0},*/
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},	//image size settings here (640x480)
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x10},//16
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},//0
	{TIMING_X_ADDR_END_REG_ADDR, 0x09},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x2f},	//2607 (corrected)
	{TIMING_Y_ADDR_END_REG_ADDR, 0x06},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0x9f},	//1951 (corrected)	//strange, that creates an area that starts at 0:16 and finishes at 2607:1951, 
	// that would be 2607:1935 res which is impossible
	/*{0x3630, 0x2e},
	OV5647_UNDOCUMENTED_MAGIC
	{0x3f01, 0x0a},*/ //more stranger danger
	/*{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x2e},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xfb},
	{B60_MAX_REG_ADDR, 0x02},
	{B50_MAX_REG_ADDR, 0x01},*/ // band step stuff, no need to care
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},	//averaging stuff
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x02},
	{BLC_CTRL00_REG_ADDR, 0x09},	//blc stuff

	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	//{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},	//disable all I/O

	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},	//sets mipi settings to 11 10 0 0 0 0	, sets driving strength and high speed voltage
	//{DEBUG_MODE_REG_301C_ADDR, 0xfc},	//more debug stuff that has nothing to do here
	//{0x3636, 0x06},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},	//sets to 00 XX 1 0 0 0 (enable mipi pad but nothing else) 
	//{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},	//more debug???
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x24},	//sets to 010 0 0 1 0 0, enable mipi 2 lane, and don't power anything down, should be corrected to 0b00100100
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},	//sets PLL settings to 0010 0001, clock divided by 4, scaler slow by 1
	{SRB_CTRL_REG_ADDR, 0b11110101},	//sets SRB clock divider to (1111)[X] 01 0 1, pll/2, and SLCK to arber enabled
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0b00010001}, // X 001 1010, pll charge pump enabled, mipi mode set badly (should be 0000 or 0001) (corrected to 8 bit mode)
	//{DEBUG_MODE_REG_301C_ADDR, 0xf8},	//yet another debug that shouldn't be used
	{MIPI_CTRL_00_REG_ADDR, 0x34},	// 0 0 1 1 0 1 0 0, mipi not always in HS mode, ck_mark1 not used, gate clock lane when no packet tx, send line short
									// packet for each line (sync), lane 1 as default, LP11 when no packet tx, first bit 0x55, clock lane not used
									// (which is right, we don't have MLCK since this is a raspi cam)
	{MIPI_CTRL_01_REG_ADDR, 0b00001111},	//just use the defaults for these	
	{MIPI_CTRL_02_REG_ADDR, 0b00000000},	//enable automatic calculations for all values						
	{MANUAL_CTRL_0x3503, 0x00},	// let's just set AEC and AGC to auto...

	{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},	//enable all I/O again

	{SOFTWARE_SLEEP_REG, 0x01},	//and wake up!
};
//camerademo RGGB8 640 480 15 bmp /tmp 5
static struct regval_list ov5647_640x480_custom[] = {
	//{SOFTWARE_SLEEP_REG, 0x00},
	//{SOFTWARE_RESET_REG, 0x01},
	//{REG_DLY,30},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x11},	//sets PLL1 to datasheet default
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x46},	//sets pll multiplier to 0x46 (4~252) = 70
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},	//sets PLL2 to 0 001(cp) 0001 (div)
	{TIMING_TC_REG21_REG_ADDR, 0x07},	//sets the mirror modes: 00000 1 1 1 (all mirrored) [removed because useless]
	//{TIMING_TC_REG20_REG_ADDR, 0x41},	//more useless mirroring modes
	//{0x370c, 0x03},	//unknown
	//{0x3612, 0x59},	//unknown
	//{0x3618, 0x00},	//unknown
	{LENC_CTRL00_REG_ADDR, 0x06},	//disables lens correction (0b0000 0110) but enables the basic ISP functions like white balance
	{ISP_CTRL03_REG_ADDR, 0x08},	// 0b0000 1000, disables binning, enables buffer
	//{DIGC_CTRL0_REG_ADDR, 0x08},	//AGC related stuff, let's not touch that
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},  //sets all specific I/O enabled
	//{DEBUG_MODE_REG_301D_ADDR, 0xf0},	//why the debug register? don't touch that!
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},	//gain related stuff
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},	//gain related stuff
	//{CTRL01_50_60_HZ_DETECTION, 0x80},	//don't bother with strobe correction
	//{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},	//same thing here
	{TIMING_HTS_REG_ADDR, 0x07},	//sets the HTS msb for mipi, here it's 1852 so 0x073C in hex
	{TIMING_HTS_LSB_REG_ADDR, 0x3c},	//sets the HTS lsb for mipi
	{TIMING_X_INC_REG_ADDR, 0x35},
	{TIMING_Y_INC_REG_ADDR, 0x35},	//windowing stuff
	//{0x3708, 0x64},	//unk
	//{0x3709, 0x52},	//unk
	/*{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x02},	//we're in mipi not DVP, not needed
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x01},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xe0},*/
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},	//image size settings here (640x480)
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x00},//00
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},//0
	{TIMING_X_ADDR_END_REG_ADDR, 0x02},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x80},	//2607 (corrected to 640)
	{TIMING_Y_ADDR_END_REG_ADDR, 0x01},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xe0},	//1951 (corrected to 480)	//strange, that creates an area that starts at 0:16 and finishes at 2607:1951, 
	// that would be 2607:1935 res which is impossible
	//modified to be 640x480
	/*OV5647_UNDOCUMENTED_MAGIC*/ //more stranger danger
	/*{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x2e},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xfb},
	{B60_MAX_REG_ADDR, 0x02},
	{B50_MAX_REG_ADDR, 0x01},*/ // band step stuff, no need to care
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},	//averaging stuff
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x02},
	{BLC_CTRL00_REG_ADDR, 0x09},	//blc stuff

	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	//{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},	//disable all I/O

	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},	//sets mipi settings to 11 10 0 0 0 0	, sets driving strength and high speed voltage
	//{DEBUG_MODE_REG_301C_ADDR, 0xfc},	//more debug stuff that has nothing to do here
	//{0x3636, 0x06},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},	//sets to 00 XX 1 0 0 0 (enable mipi pad but nothing else) 
	//{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},	//more debug???
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x24},	//sets to 010 0 0 1 0 0, enable mipi 2 lane, and don't power anything down, should be corrected to 0b00100100
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},	//sets PLL settings to 0010 0001, clock divided by 4, scaler slow by 1
	{SRB_CTRL_REG_ADDR, 0b11110101},	//sets SRB clock divider to (1111)[X] 01 0 1, pll/2, and SLCK to arber enabled
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0b00010001}, // X 001 1010, pll charge pump enabled, mipi mode set badly (should be 0000 or 0001) (corrected to 8 bit mode)
	//{DEBUG_MODE_REG_301C_ADDR, 0xf8},	//yet another debug that shouldn't be used
	{MIPI_CTRL_00_REG_ADDR, 0x34},	// 0 0 1 1 0 1 0 0, mipi not always in HS mode, ck_mark1 not used, gate clock lane when no packet tx, send line short
									// packet for each line (sync), lane 1 as default, LP11 when no packet tx, first bit 0x55, clock lane not used
									// (which is right, we don't have MLCK since this is a raspi cam)
	{MIPI_CTRL_01_REG_ADDR, 0b00001111},	//just use the defaults for these	
	{MIPI_CTRL_02_REG_ADDR, 0b00000000},	//enable automatic calculations for all values						
	{MANUAL_CTRL_0x3503, 0x00},	// let's just set AEC and AGC to auto...

	{REG_DLY,30},

	/*{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},	//enable all I/O again
	*/
	//{SOFTWARE_SLEEP_REG, 0x01},	//and wake up!
	//{REG_DLY,400},
};

static struct regval_list ov5647_640x480_custom_1lane[] = {
	//{SOFTWARE_SLEEP_REG, 0x00},
	//{SOFTWARE_RESET_REG, 0x01},
	//{REG_DLY,30},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x11},	//sets PLL1 to datasheet default
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x46},	//sets pll multiplier to 0x46 (4~252) = 70
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},	//sets PLL2 to 0 001(cp) 0001 (div)
	{TIMING_TC_REG21_REG_ADDR, 0x07},	//sets the mirror modes: 00000 1 1 1 (all mirrored) [removed because useless]
	//{TIMING_TC_REG20_REG_ADDR, 0x41},	//more useless mirroring modes
	//{0x370c, 0x03},	//unknown
	//{0x3612, 0x59},	//unknown
	//{0x3618, 0x00},	//unknown
	{LENC_CTRL00_REG_ADDR, 0x06},	//disables lens correction (0b0000 0110) but enables the basic ISP functions like white balance
	{ISP_CTRL03_REG_ADDR, 0x08},	// 0b0000 1000, disables binning, enables buffer
	//{DIGC_CTRL0_REG_ADDR, 0x08},	//AGC related stuff, let's not touch that
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},	//sets all gpio enabled
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},  //sets all specific I/O enabled
	//{DEBUG_MODE_REG_301D_ADDR, 0xf0},	//why the debug register? don't touch that!
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},	//gain related stuff
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xf8},	//gain related stuff
	//{CTRL01_50_60_HZ_DETECTION, 0x80},	//don't bother with strobe correction
	//{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0c},	//same thing here
	{TIMING_HTS_REG_ADDR, 0x07},	//sets the HTS msb for mipi, here it's 1852 so 0x073C in hex
	{TIMING_HTS_LSB_REG_ADDR, 0x3c},	//sets the HTS lsb for mipi
	{TIMING_X_INC_REG_ADDR, 0x35},
	{TIMING_Y_INC_REG_ADDR, 0x35},	//windowing stuff
	//{0x3708, 0x64},	//unk
	//{0x3709, 0x52},	//unk
	/*{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x02},	//we're in mipi not DVP, not needed
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x80},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x01},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xe0},*/
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},	//image size settings here (640x480)
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x00},//00
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},//0
	{TIMING_X_ADDR_END_REG_ADDR, 0x02},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x80},	//2607 (corrected to 640)
	{TIMING_Y_ADDR_END_REG_ADDR, 0x01},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xe0},	//1951 (corrected to 480)	//strange, that creates an area that starts at 0:16 and finishes at 2607:1951, 
	// that would be 2607:1935 res which is impossible
	//modified to be 640x480
	/*OV5647_UNDOCUMENTED_MAGIC*/ //more stranger danger
	/*{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x2e},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xfb},
	{B60_MAX_REG_ADDR, 0x02},
	{B50_MAX_REG_ADDR, 0x01},*/ // band step stuff, no need to care
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},	//averaging stuff
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x02},
	{BLC_CTRL00_REG_ADDR, 0x09},	//blc stuff

	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	//{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},	//disable all I/O

	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xe0},	//sets mipi settings to 11 10 0 0 0 0	, sets driving strength and high speed voltage
	//{DEBUG_MODE_REG_301C_ADDR, 0xfc},	//more debug stuff that has nothing to do here
	//{0x3636, 0x06},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},	//sets to 00 XX 1 0 0 0 (enable mipi pad but nothing else) 
	//{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xec},	//more debug???
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x04},	//sets to 010 0 0 1 0 0, enable mipi 2 lane, and don't power anything down, should be corrected to 0b00100100
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},	//sets PLL settings to 0010 0001, clock divided by 4, scaler slow by 1
	{SRB_CTRL_REG_ADDR, 0b11110101},	//sets SRB clock divider to (1111)[X] 01 0 1, pll/2, and SLCK to arber enabled
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0b00010001}, // X 001 1010, pll charge pump enabled, mipi mode set badly (should be 0000 or 0001) (corrected to 8 bit mode)
	//{DEBUG_MODE_REG_301C_ADDR, 0xf8},	//yet another debug that shouldn't be used
	{MIPI_CTRL_00_REG_ADDR, 0x34},	// 0 0 1 1 0 1 0 0, mipi not always in HS mode, ck_mark1 not used, gate clock lane when no packet tx, send line short
									// packet for each line (sync), lane 1 as default, LP11 when no packet tx, first bit 0x55, clock lane not used
									// (which is right, we don't have MLCK since this is a raspi cam)
	{MIPI_CTRL_01_REG_ADDR, 0b00001111},	//just use the defaults for these	
	{MIPI_CTRL_02_REG_ADDR, 0b00000000},	//enable automatic calculations for all values						
	{MANUAL_CTRL_0x3503, 0x00},	// let's just set AEC and AGC to auto...

	{REG_DLY,30},

	/*{SC_CMMN_PAD_OEN0_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xff},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xff},	//enable all I/O again
	*/
	//{SOFTWARE_SLEEP_REG, 0x01},	//and wake up!
	//{REG_DLY,400},
};

//SGBRG10_CSI2P, 1296x972
static struct regval_list ov5647_rpi3[] = {
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0F},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xFF},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xE4},
	{MIPI_CTRL_00_REG_ADDR, 0x25},
	{0x4202, 0x0F},
	{SC_CMMN_PAD_OUT2_REG_ADDR, 0x01},
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1A},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x62},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{SRB_CTRL_REG_ADDR, 0xF5},
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xEC},
	{0x370C, 0x03},	
	{0x3612, 0x59},
	{0x3618, 0x00},
	{LENC_CTRL00_REG_ADDR, 0x06},
	//???? //0b01101100 001010000 000000100 010000010 
	// 6C 50 04 82
	{0x5002, 0x41},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xE0},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44}, //0b01000100 one lane mode, mipi enable, no suspend, use both release
	{DEBUG_MODE_REG_301C_ADDR, 0xF8},
	{DEBUG_MODE_REG_301D_ADDR, 0xF0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xF8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0C},
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_X_ADDR_END_REG_ADDR, 0x0A},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x3F},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x07},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xA3},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x05},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x10},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x03},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xCC},
	{TIMING_HTS_REG_ADDR, 0x07},
	{TIMING_HTS_LSB_REG_ADDR, 0x68},
	{TIMING_ISP_X_WIN_LSB_REG_ADDR, 0x0C},
	{TIMING_ISP_Y_WIN_LSB_REG_ADDR, 0x06},
	{TIMING_X_INC_REG_ADDR, 0x31},
	{TIMING_Y_INC_REG_ADDR, 0x31},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x28},
	{B60_STEP_HIGH_REG_ADDR, 0x00},
	{B60_STEP_LOW_REG_ADDR, 0xF6},
	{B60_MAX_REG_ADDR, 0x08},
	{B50_MAX_REG_ADDR, 0x06},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x04},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{PCLK_PERIOD_REG_ADDR, 0x16},
	{0x4800, 0x24},
	{0x3503, 0x03},
	{0x3820, 0x41},
	{0x3821, 0x21},
	{0x350A, 0x00},
	{0x350B, 0x10},
	{0x3500, 0x00},
	{0x3501, 0x1A},
	{0x3502, 0xF0},
	{0x3212, 0xA0},
	{0x0100, 0x01},

	{0x4814, 0x2A},
	{0x3503, 0x03},
	{0x5001, 0x00},
	{0x3503, 0x03},
	{0x3500, 0x00},
	{0x3501, 0x02},
	{0x3502, 0xB0},
	{0x350A, 0x00},
	{0x350B, 0x10},
	{0x380E, 0x05},
	{0x380F, 0x9B},

	{0x3821, 0x03},
	{0x3820, 0x41},
	{0x4800, 0x34},
	{0x4202, 0x00},
	{0x300D, 0x00},

	{REG_DLY,70},	//wait 70ms
	{EXPOSURE_0x3500, 0x00},	//exposure
	{EXPOSURE_0x3501, 0x50},
	{EXPOSURE_0x3502, 0xC0},
	{AGC_0x350A, 0x00},	//AGC
	{AGC_0x350B, 0x2A},

	{REG_DLY, 30},
	{EXPOSURE_0x3500, 0x00},	//exposure
	{EXPOSURE_0x3501, 0x59},
	{EXPOSURE_0x3502, 0x70},
	{AGC_0x350A, 0x00},	//AGC
	{AGC_0x350B, 0x80},
};

static struct regval_list ov5647_rpi3_1080[] = {
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x0F},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0xFF},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0xE4},
	{MIPI_CTRL_00_REG_ADDR, 0x25},
	{0x4202, 0x0F},
	{SC_CMMN_PAD_OUT2_REG_ADDR, 0x01},
	{SOFTWARE_SLEEP_REG, 0x00},
	{SOFTWARE_RESET_REG, 0x01},
	{SC_CMMN_PLL_CTRL0_REG_ADDR, 0x1A},
	{SC_CMMN_PLL_CTRL1_REG_ADDR, 0x21},
	{SC_CMMN_PLL_MULTIPLIER_REG_ADDR, 0x62},
	{SC_CMMN_PLLS_CTRL2_REG_ADDR, 0x11},
	{SRB_CTRL_REG_ADDR, 0xF5},
	{0x3821, 0x00},// added?
	{0x3820, 0x00},// added?
	{DEBUG_MODE_TIMING_REG_3827_ADDR, 0xEC},
	{0x370C, 0x03},	
	{0x3612, 0x5B},
	{0x3618, 0x04},
	{LENC_CTRL00_REG_ADDR, 0x06},
	//???? //0b01101100 001010000 000000100 010000010 
	// 6C 50 04 82
	{0x5002, 0x41},
	{ISP_CTRL03_REG_ADDR, 0x08},
	{DIGC_CTRL0_REG_ADDR, 0x08},
	{SC_CMMN_PAD_OEN0_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN1_REG_ADDR, 0x00},
	{SC_CMMN_PAD_OEN2_REG_ADDR, 0x00},
	{SC_CMMN_MIPI_PHY_REG_ADDR, 0x08},
	{SC_CMMN_MIPI_PHY_10_REG_ADDR, 0xE0},
	{SC_CMMN_MIPI_SC_CTRL_REG_ADDR, 0x44}, //0b01000100 one lane mode, mipi enable, no suspend, use both release
	{DEBUG_MODE_REG_301C_ADDR, 0xF8},
	{DEBUG_MODE_REG_301D_ADDR, 0xF0},
	{AEC_GAIN_CEILING_HIGH_REG_ADDR, 0x00},
	{AEC_GAIN_CEILING_LOW_REG_ADDR, 0xF8},
	{CTRL01_50_60_HZ_DETECTION, 0x80},
	{STROBE_FREX_MODE_SEL_REG_ADDR, 0x0C},
	{TIMING_X_ADDR_START_REG_ADDR, 0x00},
	{TIMING_X_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_REG_ADDR, 0x00},
	{TIMING_Y_ADDR_START_LSB_REG_ADDR, 0x00},
	{TIMING_X_ADDR_END_REG_ADDR, 0x0A},
	{TIMING_X_ADDR_END_LSB_REG_ADDR, 0x3F},
	{TIMING_Y_ADDR_END_REG_ADDR, 0x07},
	{TIMING_Y_ADDR_END_LSB_REG_ADDR, 0xA3},
	{TIMING_X_OUTPUT_SIZE_REG_ADDR, 0x05},
	{TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR, 0x10},
	{TIMING_Y_OUTPUT_SIZE_REG_ADDR, 0x03},
	{TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR, 0xCC},

	{TIMING_HTS_REG_ADDR, 0x09},
	{TIMING_HTS_LSB_REG_ADDR, 0x70},
	{TIMING_ISP_X_WIN_LSB_REG_ADDR, 0x0C},
	{TIMING_ISP_Y_WIN_LSB_REG_ADDR, 0x06},
	{TIMING_X_INC_REG_ADDR, 0x11},
	{TIMING_Y_INC_REG_ADDR, 0x11},
	OV5647_UNDOCUMENTED_MAGIC
	{B50_STEP_HIGH_REG_ADDR, 0x01},
	{B50_STEP_LOW_REG_ADDR, 0x4B},
	{B60_STEP_HIGH_REG_ADDR, 0x01},
	{B60_STEP_LOW_REG_ADDR, 0x13},
	{B60_MAX_REG_ADDR, 0x04},
	{B50_MAX_REG_ADDR, 0x03},
	{WPT_REG_ADDR, 0x58},
	{BPT_REG_ADDR, 0x50},
	{WPT2_REG_ADDR, 0x58},
	{BPT2_REG_ADDR, 0x50},
	{HIGH_VPT_REG_ADDR, 0x60},
	{LOW_VPT_REG_ADDR, 0x28},
	{BLC_CTRL01_REG_ADDR, 0x02},
	{BLC_CTRL04_REG_ADDR, 0x04},
	{BLC_CTRL00_REG_ADDR, 0x09},
	{PCLK_PERIOD_REG_ADDR, 0x19},
	{0x4800, 0x34},
	{0x3503, 0x03},

	/*{0x0100, 0x01},
	{0x3820, 0x41},
	{0x3821, 0x21},
	{0x350A, 0x00},
	{0x350B, 0x10},
	{0x3500, 0x00},
	{0x3501, 0x1A},
	{0x3502, 0xF0},
	{0x3212, 0xA0},*/
	{0x0100, 0x01},

	{0x4814, 0x2A},
	{0x3503, 0x03},
	{0x5001, 0x02},
	{0x3503, 0x03},
	{0x3500, 0x00},
	{0x3501, 0x02},
	{0x3502, 0x10},
	{0x350A, 0x00},
	{0x350B, 0x10},
	{0x380E, 0x04},
	{0x380F, 0x66},

	{0x3821, 0x02},
	{0x3820, 0x00},
	{0x4800, 0x34},
	{0x4202, 0x00},
	{0x300D, 0x00},

	{REG_DLY,70},	//wait 70ms
	{EXPOSURE_0x3500, 0x00},	//exposure
	{EXPOSURE_0x3501, 0x46},
	{EXPOSURE_0x3502, 0x20},
	{AGC_0x350A, 0x00},	//AGC
	{AGC_0x350B, 0x80},
};

static struct regval_list sensor_fmt_raw8[] = {
	{0x3034, 0b01110000},
};

static struct regval_list sensor_fmt_raw10[] = {
	{0x3034, 0b01110000},
};