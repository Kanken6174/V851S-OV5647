#define AUTHOR "YG"
#define SENSOR_MAT "ov5647"

#define SOFTWARE_SLEEP_REG 0x0100
#define SOFTWARE_RESET_REG 0x0103

#define TIMING_TC_REG20 0x3820 //[0]verical binning [1]vflip_isnr [2]vflip_snr
#define TIMING_TC_REG21 0x3821 //[0]horizontal binning [1]mirror_isnr [2]mirror_snr

//windowing
#define TIMING_X_ADDR_START 0x3800 // 0x00 RW Bit[3:0]: x_addr_start[11:8]
#define TIMING_X_ADDR_START2 0x3801 // 0x0C RW Bit[7:0]: x_addr_start[7:0]
#define TIMING_Y_ADDR_START 0x3802 // 0x00 RW Bit[3:0]: y_addr_start[11:8]
#define TIMING_Y_ADDR_START2 0x3803 // 0x04 RW Bit[7:0]: y_addr_start[7:0]
#define TIMING_X_ADDR_END 0x3804 // 0x0A RW Bit[3:0]: x_addr_end[11:8]
#define TIMING_X_ADDR_END2 0x3805 // 0x33 RW Bit[7:0]: x_addr_end[7:0]
#define TIMING_Y_ADDR_END 0x3806 // 0x07 RW Bit[3:0]: y_addr_end[11:8]
#define TIMING_Y_ADDR_END2 0x3807 // 0xA3 RW Bit[7:0]: y_addr_end[7:0]

//testing
#define ISP_CTRL3D 0x503D // 0x00 [7]test pattern_en [6]rolling_bar [5]tranparent [4]coloring [3:2]bar width [1:0]pattern_type
#define ISP_CTRL3E 0x503E // 0x00 [6]win_cut_en [5]isp_test [4]fixed/random_test [3:0]random_seed

// 50/60 HZ DETECTION
#define CTRL00_50_60_HZ_DETECTION 0x3C00 // CTRL00 0x00 RW
// Bit[5:3]: 50/60 Hz detection control
// Bit[2]: Band definition (Contact local OmniVision FAE for correct settings)
// Bit[1]: Default band (0: 60 Hz as default value, 1: 50 Hz as default value)
// Bit[0]: 50/60 Hz detection control (Contact local OmniVision FAE for correct settings)

#define CTRL01_50_60_HZ_DETECTION 0x3C01 // CTRL01 0x00 RW
// Bit[7]: Band manual mode enable (0: Manual mode disable, 1: Manual mode enable)
// Bit[6:0]: 50/60 Hz detection control (Contact local OmniVision FAE for correct settings)

#define CTRL02_TO_CTRL0B_50_60_HZ_DETECTION_START 0x3C02 // CTRL02 0x00 RW to CTRL0B 0x00 RW
// Bit[7:0]: 50/60 Hz detection control (Contact local OmniVision FAE for correct settings)

#define CTRL0C_50_60_HZ_DETECTION 0x3C0C // CTRL0C – R
// Bit[0]: Detection result (0: Detection result is 60 Hz, 1: Detection result is 50 Hz)

// EXPOSURE
#define EXPOSURE_0x3500 0x3500 // 0x00 RW
// Bit[3:0]: Exposure[19:16]

#define EXPOSURE_0x3501 0x3501 // 0x00 RW
// Bit[7:0]: Exposure[15:8]

#define EXPOSURE_0x3502 0x3502 // 0x20 RW
// Bit[7:0]: Exposure[7:0]

// MANUAL CTRL
#define MANUAL_CTRL_0x3503 0x3503 // 0x00 RW
// Bit[5:4]: Gain latch timing delay
//   00: Gain has no latch delay
//   01: Gain delay of 1 frame
//   11: Gain delay of 2 frames
// Bit[2]: VTS manual
//   0: Auto enable
//   1: Manual enable
// Bit[1]: AGC manual
//   0: Auto enable
//   1: Manual enable
// Bit[0]: AEC manual
//   0: Auto enable
//   1: Manual enable

// AGC
#define AGC_0x350A 0x350A // 0x00 RW
// Bit[1:0]: Gain[9:8] (AGC real gain output high byte)

#define AGC_0x350B 0x350B // 0x00 RW
// Bit[7:0]: Gain[7:0] (AGC real gain output low byte)

// VTS DIFF
#define VTS_DIFF_0x350C 0x350C // 0x06 RW
// Bit[7:0]: vts_diff[15:8]
// When in manual mode, set to 0x00

#define VTS_DIFF_0x350D 0x350D // 0x18 RW
// Bit[7:0]: vts_diff[7:0]
// When in manual mode, set to 0x00

// Average Based Control Function Registers (Table 4-6)
#define WPT_REG_ADDR 0x3A0F // WPT 0x78 RW
// Bit[7:0]: WPT - Stable range high limit (enter)

#define BPT_REG_ADDR 0x3A10 // BPT 0x68 RW
// Bit[7:0]: BPT - Stable range low limit (enter)

#define HIGH_VPT_REG_ADDR 0x3A11 // HIGH VPT 0xD0 RW
// Bit[7:0]: vpt_high - Fast zone high limit when step ratio auto mode is disabled

#define WPT2_REG_ADDR 0x3A1B // WPT2 0x78 RW
// Bit[7:0]: wpt2 - Stable range high limit (from stable state to unstable state)

#define BPT2_REG_ADDR 0x3A1E // BPT2 0x68 RW
// Bit[7:0]: bpt2 - Stable range low limit (from stable state to unstable state)

#define LOW_VPT_REG_ADDR 0x3A1F // LOW VPT 0x40 RW
// Bit[7:0]: vpt_low - Fast zone low limit when step ratio auto mode is disabled

// Average Luminance Control Function Registers (Sheet 1 of 2)------------------------------
#define XSTART_HIGH_BYTE_REG_ADDR 0x5680 // XSTART 0x00 RW
// Bit[3:0]: x_start[11:8] - Horizontal start position for average window high byte

#define XSTART_LOW_BYTE_REG_ADDR 0x5681 // XSTART 0x00 RW
// Bit[7:0]: x_start[7:0] - Horizontal start position for average window low byte

#define YSTART_HIGH_BYTE_REG_ADDR 0x5682 // YSTART 0x00 RW
// Bit[3:0]: y_start[11:8] - Vertical start position for average window high byte

#define YSTART_LOW_BYTE_REG_ADDR 0x5683 // YSTART 0x00 RW
// Bit[7:0]: y_start[7:0] - Vertical start position for average window low byte

#define X_WINDOW_HIGH_BYTE_REG_ADDR 0x5684 // X WINDOW 0x0A RW
// Bit[4:0]: Window X in manual average window mode high byte

#define X_WINDOW_LOW_BYTE_REG_ADDR 0x5685 // X WINDOW 0x20 RW
// Bit[7:0]: Window X in manual average window mode low byte

#define Y_WINDOW_HIGH_BYTE_REG_ADDR 0x5686 // Y WINDOW 0x07 RW
// Bit[3:0]: Window Y in manual average window mode high byte

#define Y_WINDOW_LOW_BYTE_REG_ADDR 0x5687 // Y WINDOW 0x98 RW
// Bit[7:0]: Window Y in manual average window mode low byte

#define WEIGHT00_REG_ADDR 0x5688 // WEIGHT00 0x11 RW
// Bit[7:4]: Window1 weight
// Bit[3:0]: Window0 weight

#define WEIGHT01_REG_ADDR 0x5689 // WEIGHT01 0x11 RW
// Bit[7:4]: Window3 weight
// Bit[3:0]: Window2 weight

#define WEIGHT02_REG_ADDR 0x568A // WEIGHT02 0x11 RW
// Bit[7:4]: Window5 weight
// Bit[3:0]: Window4 weight

#define WEIGHT03_REG_ADDR 0x568B // WEIGHT03 0x11 RW
// Bit[7:4]: Window7 weight
// Bit[3:0]: Window6 weight

#define WEIGHT04_REG_ADDR 0x568C // WEIGHT04 0x11 RW
// Bit[7:4]: Window9 weight
// Bit[3:0]: Window8 weight

#define WEIGHT05_REG_ADDR 0x568D // WEIGHT05 0x11 RW
// Bit[7:4]: Window11 weight
// Bit[3:0]: Window10 weight

#define WEIGHT06_REG_ADDR 0x568E // WEIGHT06 0x11 RW
// Bit[7:4]: Window13 weight
// Bit[3:0]: Window12 weight

#define WEIGHT07_REG_ADDR 0x568F // WEIGHT07 0x11 RW
// Bit[7:4]: Window15 weight
// Bit[3:0]: Window14 weight

#define AVG_CTRL10_REG_ADDR 0x5690 // AVG CTRL10 – R
// Bit[1]: avg_opt - 0: Auto average window, 1: Manual average window
// Bit[0]: avg_man - 0: Auto average window, 1: Manual average window

#define AVG_READOUT_REG_ADDR 0x5693 // AVG READOUT – R
// Bit[7:0]: avg value

// BLC Control Functions (Table 4-8)
#define BLC_CTRL00_REG_ADDR 0x4000 // BLC CTRL00 0x89 RW
// BLC Control (0: disable, 1: enable)
// Bit[7]: blc_median_filter_enable
// Bit[3]: adc_11bit_mode
// Bit[2]: apply2blackline
// Bit[1]: blackline_averageframe
// Bit[0]: BLC enable

#define BLC_CTRL02_REG_ADDR 0x4002 // BLC CTRL02 0x45 RW
// Bit[7]: format_change_en
// format_change_i from fmt will be effect when it is enable
// Bit[6]: blc_auto_en
// Bit[5:0]: reset_frame_num

#define BLC_CTRL05_REG_ADDR 0x4005 // BLC CTRL05 0x18 RW
// Bit[5]: one_line_mode
// Bit[4]: remove_none_imagedata
// Bit[3]: blc_man_1_en
// Bit[2]: blackline_bggr_man_en (0: bgbg/grgr is decided by rblue/hswap, 1: bgbg/grgr fix)
// Bit[1]: bgbg/grgr is decided by rblue/hswap
// Bit[0]: blc_always_up_en (0: Normal freeze, 1: BLC always update)

#define BLC_BLACK_LEVEL_REG_ADDR 0x4009 // BLACK LEVEL 0x10 RW
// Bit[7:0]: blc_blackleveltarget0

#define DEBUG_MODE_REG_ADDR 0x400A //-> 0x400B DEBUG MODE - - Debug Mode

#define BLC_MAN0_MSB_REG_ADDR 0x400C // BLC MAN0 0x00 RW
// Bit[7:0]: blc_man0[15:8]

#define BLC_MAN0_LSB_REG_ADDR 0x400D // BLC MAN0 0x00 RW
// Bit[7:0]: blc_man0[7:0]

#define BLC_MAN1_MSB_REG_ADDR 0x400E // BLC MAN1 0x00 RW
// Bit[7:0]: blc_man1[15:8]

#define BLC_MAN1_LSB_REG_ADDR 0x400F // BLC MAN1 0x00 RW
// Bit[7:0]: blc_man1[7:0]

#define BLC_MAN2_MSB_REG_ADDR 0x4010 // BLC MAN2 0x00 RW
// Bit[7:0]: blc_man2[15:8]

#define BLC_MAN2_LSB_REG_ADDR 0x4011 // BLC MAN2 0x00 RW
// Bit[7:0]: blc_man2[7:0]

#define BLC_MAN3_MSB_REG_ADDR 0x4012 // BLC MAN3 0x00 RW
// Bit[7:0]: blc_man3[15:8]

#define BLC_MAN3_LSB_REG_ADDR 0x4013 // BLC MAN3 0x00 RW
// Bit[7:0]: blc_man3[7:0]

#define BLACK_LEVEL00_MSB_REG_ADDR 0x402C // BLACK_LEVEL00 - R
// Bit[7:0]: blacklevel00[15:8]

#define BLACK_LEVEL00_LSB_REG_ADDR 0x402D // BLACK_LEVEL00 - R
// Bit[7:0]: blacklevel00[7:0]

#define BLACK_LEVEL01_MSB_REG_ADDR 0x402E // BLACK_LEVEL01 - R
// Bit[7:0]: blacklevel01[15:8]

#define BLACK_LEVEL01_LSB_REG_ADDR 0x402F // BLACK_LEVEL01 - R
// Bit[7:0]: blacklevel01[7:0]

#define BLACK_LEVEL10_MSB_REG_ADDR 0x4030 // BLACK_LEVEL10 - R
// Bit[7:0]: blacklevel10[15:8]

#define BLACK_LEVEL10_LSB_REG_ADDR 0x4031 // BLACK_LEVEL10 - R
// Bit[7:0]: blacklevel10[7:0]

#define BLACK_LEVEL11_MSB_REG_ADDR 0x4032 // BLACK_LEVEL11 - R
// Bit[7:0]: blacklevel11[15:8]

#define BLACK_LEVEL11_LSB_REG_ADDR 0x4033 // BLACK_LEVEL11 - R
// Bit[7:0]: blacklevel11[7:0]

#define BLC_MAX_REG_ADDR 0x4050 // BLC MAX 0xFF RW
// Bit[7:0]: blc max black level

#define BLC_STABLE_RANGE_REG_ADDR 0x4051 // STABLE RANGE 0x7F RW
// Bit[7:0]: BLC stable range

#define ONE_CHANNEL_REG_ADDR 0x4052 // ONE CHANNEL 0x00 RW
// Bit[7:0]: blc_one_channel

#define BLC_BR_THRE0_REG_ADDR 0x4060 // BLC BR THRE0 0x00 RW
// Bit[7:0]: blc_br_thr_0

#define BLC_BR_THRE1_REG_ADDR 0x4061 // BLC BR THRE1 0x00 RW
// Bit[7:0]: blc_br_thr_1

#define BLC_BR_THRE2_REG_ADDR 0x4062 // BLC BR THRE2 0x00 RW
// Bit[7:0]: blc_br_thr_2

#define BLC_BR_THRE3_REG_ADDR 0x4063 // BLC BR THRE3 0x00 RW
// Bit[7:0]: blc_br_thr_3

#define BLC_BR_THRE4_REG_ADDR 0x4064 // BLC BR THRE4 0x00 RW
// Bit[7:0]: blc_br_thr_4

#define BLC_BR_THRE5_REG_ADDR 0x4065 // BLC BR THRE5 0x00 RW
// Bit[7:0]: blc_br_thr_5

#define BLC_G_THRE0_REG_ADDR 0x4066 // BLC G THRE0 0x00 RW
// Bit[7:0]: blc_g_thr_0

#define BLC_G_THRE1_REG_ADDR 0x4067 // BLC G THRE1 0x00 RW
// Bit[7:0]: blc_g_thr_1

#define BLC_G_THRE2_REG_ADDR 0x4068 // BLC G THRE2 0x00 RW
// Bit[7:0]: blc_g_thr_2

#define BLC_G_THRE3_REG_ADDR 0x4069 // BLC G THRE3 0x00 RW
// Bit[7:0]: blc_g_thr_3

#define BLC_G_THRE4_REG_ADDR 0x406A // BLC G THRE4 0x00 RW
// Bit[7:0]: blc_g_thr_4

#define BLC_G_THRE5_REG_ADDR 0x406B // BLC G THRE5 0x00 RW
// Bit[7:0]: blc_g_thr_5

#define BLC_BRG_COMP_EN_REG_ADDR 0x406C // BLC BRG COMP EN 0x00 RW
// Bit[7:0]: blc_brg_comp_en

// FREX Strobe Control Functions (Table 4-10)
#define STROBE_CTRL_REG_ADDR 0x3B00 // STROBE CTRL 0x00 RW
// Strobe Control
// Bit[7]: Strobe request ON/OFF (0: OFF/BLC, 1: ON)
// Bit[6]: Strobe pulse reverse
// Bit[3:2]: width_in_xenon (00: 1 row period, 01: 2 row period, 10: 3 row period, 11: 4 row period)
// Bit[1:0]: Strobe mode (00: xenon, 01: LED 1, 10: LED 2, 11: LED 3)

#define STROBE_FREX_EXP_H2_REG_ADDR 0x3B01 // STROBE_FREX_EXP_H2 0x00 RW
// Bit[7:0]: frex_exp[23:16]

#define STROBE_SHUTTER_DLY_HIGH_REG_ADDR 0x3B02 // STROBE_SHUTTER_DLY 0x08 RW
// Bit[4:0]: shutter_dly[12:8]

#define STROBE_SHUTTER_DLY_LOW_REG_ADDR 0x3B03 // STROBE_SHUTTER_DLY 0x00 RW
// Bit[7:0]: shutter_dly[7:0]

#define STROBE_FREX_EXP_H_REG_ADDR 0x3B04 // STROBE_FREX_EXP_H 0x04 RW
// Bit[7:0]: frex_exp[15:8]

#define STROBE_FREX_EXP_L_REG_ADDR 0x3B05 // STROBE_ FREX_EXP_L 0x00 RW
// Bit[7:0]: frex_exp[7:0]

#define FREX_CTRL_REG_ADDR 0x3B06 // FREX CTRL 0x04 RW
// FREX Control
// Bit[7:6]: frex_pchg_width
// Bit[5:4]: frex_strobe_option
// Bit[3:0]: frex_strobe_width[3:0]

#define STROBE_FREX_MODE_SEL_REG_ADDR 0x3B07 // STROBE_FREX_MODE_SEL 0x08 RW
// Bit[3]: fx1_fm_en
// Bit[2]: frex_inv
// Bit[1:0]: FREX mode select (00: frex_strobe mode0, 01: frex_strobe mode1, 1x: Rolling strobe)

#define STROBE_FREX_EXP_REQ_REG_ADDR 0x3B08 // STROBE_FREX_EXP_REQ 0x00 RW
// Bit[0]: frex_exp_req

#define FREX_SHUTTER_DELAY_REG_ADDR 0x3B09 // FREX_SHUTTER_DELAY 0x00 RW
// Bit[2:0]: frex end option

#define STROBE_FREX_RST_LENGTH_REG_ADDR 0x3B0A // STROBE_FREX_RST_LENGTH 0x04 RW
// Bit[2:0]: frex_rst_length[2:0]

#define STROBE_WIDTH_HIGH_REG_ADDR 0x3B0B // STROBE_WIDTH 0x00 RW
// Bit[7:0]: frex_strobe_width[19:12]

#define STROBE_WIDTH_LOW_REG_ADDR 0x3B0C // STROBE_WIDTH 0x3D RW
// Bit[7:0]: frex_strobe_width[11:4]

// OTP Control Function Registers (Table 4-11, Sheet 1 of 2)
#define OTP_DATA_0_REG_ADDR 0x3D00 // OTP_DATA_0 0x00 RW
#define OTP_DATA_1_REG_ADDR 0x3D01 // OTP_DATA_1 0x00 RW
#define OTP_DATA_2_REG_ADDR 0x3D02 // OTP_DATA_2 0x00 RW
#define OTP_DATA_3_REG_ADDR 0x3D03 // OTP_DATA_3 0x00 RW
#define OTP_DATA_4_REG_ADDR 0x3D04 // OTP_DATA_4 0x00 RW
#define OTP_DATA_5_REG_ADDR 0x3D05 // OTP_DATA_5 0x00 RW
#define OTP_DATA_6_REG_ADDR 0x3D06 // OTP_DATA_6 0x00 RW
#define OTP_DATA_7_REG_ADDR 0x3D07 // OTP_DATA_7 0x00 RW
#define OTP_DATA_8_REG_ADDR 0x3D08 // OTP_DATA_8 0x00 RW
#define OTP_DATA_9_REG_ADDR 0x3D09 // OTP_DATA_9 0x00 RW
#define OTP_DATA_A_REG_ADDR 0x3D0A // OTP_DATA_A 0x00 RW
#define OTP_DATA_B_REG_ADDR 0x3D0B // OTP_DATA_B 0x00 RW
#define OTP_DATA_C_REG_ADDR 0x3D0C // OTP_DATA_C 0x00 RW
#define OTP_DATA_D_REG_ADDR 0x3D0D // OTP_DATA_D 0x00 RW
#define OTP_DATA_E_REG_ADDR 0x3D0E // OTP_DATA_E 0x00 RW
#define OTP_DATA_F_REG_ADDR 0x3D0F // OTP_DATA_F 0x00 RW
#define OTP_DATA_10_REG_ADDR 0x3D10 // OTP_DATA_16 0x00 RW
#define OTP_DATA_11_REG_ADDR 0x3D11 // OTP_DATA_17 0x00 RW
#define OTP_DATA_12_REG_ADDR 0x3D12 // OTP_DATA_18 0x00 RW
#define OTP_DATA_13_REG_ADDR 0x3D13 // OTP_DATA_19 0x00 RW
#define OTP_DATA_14_REG_ADDR 0x3D14 // OTP_DATA_20 0x00 RW
#define OTP_DATA_15_REG_ADDR 0x3D15 // OTP_DATA_21 0x00 RW
#define OTP_DATA_16_REG_ADDR 0x3D16 // OTP_DATA_22 0x00 RW
#define OTP_DATA_17_REG_ADDR 0x3D17 // OTP_DATA_23 0x00 RW
#define OTP_DATA_18_REG_ADDR 0x3D18 // OTP_DATA_24 0x00 RW
#define OTP_DATA_19_REG_ADDR 0x3D19 // OTP_DATA_25 0x00 RW
#define OTP_DATA_1A_REG_ADDR 0x3D1A // OTP_DATA_26 0x00 RW
#define OTP_DATA_1B_REG_ADDR 0x3D1B // OTP_DATA_27 0x00 RW
#define OTP_DATA_1C_REG_ADDR 0x3D1C // OTP_DATA_28 0x00 RW
#define OTP_DATA_1D_REG_ADDR 0x3D1D // OTP_DATA_29 0x00 RW
#define OTP_DATA_1E_REG_ADDR 0x3D1E // OTP_DATA_30 0x00 RW
#define OTP_DATA_1F_REG_ADDR 0x3D1F // OTP_DATA_31 0x00 RW
#define OTP_PROGRAM_CTRL_REG_ADDR 0x3D20 // OTP_PROGRAM_CTRL 0x00 RW
// Bit[7]: OTP_wr_busy
// Bit[1]: OTP_program_speed (0: Fast, 1: Slow)
// Bit[0]: OTP_program_enable (Changing from 0 to 1 initiates OTP programming)

#define OTP_LOAD_CTRL_REG_ADDR 0x3D21 // OTP_LOAD_CTRL 0x00 RW
// Bit[7]: OTP_rd_busy
// Bit[1]: OTPspeed (0: Fast, 1: Slow)
// Bit[0]: OTP_load_enable (Changing from 0 to 1 initiates OTP read)

// ISP General Control Registers----------------------------------------------------------------------
#define ISP_CTRL00_REG_ADDR 0x5000 // ISP CTRL00 0xFF RW
// Bit[7]: lenc_en (0: Disable, 1: Enable)
// Bit[2]: bc_en (0: Disable, 1: Enable)
// Bit[1]: wc_en (0: Disable, 1: Enable)

#define ISP_CTRL01_REG_ADDR 0x5001 // ISP CTRL01 0x01 RW
// Bit[0]: awb_en (0: Disable, 1: Enable)

#define ISP_CTRL02_REG_ADDR 0x5002 // ISP CTRL02 0x41 RW
// Bit[6]: win_en (0: Disable, 1: Enable)
// Bit[1]: otp_en (0: Disable, 1: Enable)
// Bit[0]: awb_gain_en (0: Disable, 1: Enable)

#define ISP_CTRL03_REG_ADDR 0x5003 // ISP CTRL03 0x0A RW
// Bit[3]: buf_en (0: Disable, 1: Enable)
// Bit[2]: bin_man_set (0: Manual value as 0, 1: Manual value as 1)
// Bit[1]: bin_auto_en (0: Disable, 1: Enable)

#define ISP_CTRL05_REG_ADDR 0x5005 // ISP CTRL05 0x14 RW
// Bit[4]: awb_bias_on (0: Disable AWB bias, 1: Enable AWB bias)
// Bit[2]: lenc_bias_on (0: Disable LENC bias, 1: Enable LENC bias)

#define ISP_CTRL1F_REG_ADDR 0x501F // ISP CTRL1F 0x03 RW
// Bit[5]: enable_opt (0: Not latched by VSYNC, 1: Enable latched by VSYNC)
// Bit[4]: cal_sel (0: DPC cal_start using SOF, 1: DPC cal_start using VSYNC)
// Bit[2:0]: fmt_sel (010: ISP output data, 011: ISP input data bypass)

#define ISP_CTRL25_REG_ADDR 0x5025 // ISP CTRL25 0x00 RW
// Bit[1:0]: avg_sel (00: Inputs of AVG module are from LENC output,
// 01: Inputs of AVG module are from AWB gain output,
// 10: Inputs of AVG module are from DPC output,
// 11: Inputs of AVG module are from binning output)

#define ISP_CTRL3D_REG_ADDR 0x503D // ISP CTRL3D 0x00 RW
// Bit[7]: test_pattern_en (0: Disable, 1: Enable)
// Bit[6]: rolling_bar (0: Disable rolling bar, 1: Enable rolling bar)
// Bit[5]: transparent_mode (0: Disable, 1: Enable)
// Bit[4]: squ_bw_mode (0: Output square is color square, 1: Output square is black-white square)
// Bit[3:2]: bar_style (When set to a different value, a different type of color bar is output)
// Bit[1:0]: test_pattern_type (00: Color bar, 01: Square, 10: Random data, 11: Input data)

#define ISP_CTRL3E_REG_ADDR 0x503E // ISP CTRL3E 0x00 RW
// Bit[6]: win_cut_en
// Bit[5]: isp_test
// Bit[4]: rnd_same
// Bit[3:0]: rnd_seed

#define ISP_CTRL46_REG_ADDR 0x5046 // ISP CTRL46 0x09 RW
// Bit[3]: awbg_en (0: Disable, 1: Enable)
// Bit[0]: isp_en (0: Disable, 1: Enable)

#define ISP_CTRL4B_REG_ADDR 0x504B // ISP CTRL4B 0x30 RW
// ISP Control (0: disable; 1: enable)
// Bit[5]: post_binning h_enable
// Bit[4]: post_binning v_enable
// Bit[3]: flip_man_en
// Bit[2]: flip_man
// Bit[1]: mirror_man_en
// Bit[0]: Mirror

// LENC Control Registers ------------------------------------------------------------------
#define LENC_CTRL00_REG_ADDR 0x5000 // ISP CTRL00 0x89 RW
// Bit[7]: lenc_en (0: Disable, 1: Enable)

#define MAX_GAIN_REG_ADDR 0x583E // MAX GAIN 0x40 RW
// Bit[7:0]: max_gain

#define MIN_GAIN_REG_ADDR 0x583F // MIN GAIN 0x20 RW
// Bit[7:0]: min_gain

#define MIN_Q_REG_ADDR 0x5840 // MIN Q 0x18 RW
// Bit[6:0]: min_q

#define LENC_CTRL59_REG_ADDR 0x5841 // LENC CTRL59 0x0D RW
// Bit[3]: ADDBLC (0: Disable BLC add back function, 1: Enable BLC add back function)
// Bit[2]: blc_en (0: Disable BLC function, 1: Enable BLC function)
// Bit[1]: gain_man_en
// Bit[0]: autoq_en (0: Used constant Q (0x40), 1: Used calculated Q)

#define BR_HSCALE_REG_ADDR 0x5842 // BR HSCALE 0x01 RW
// Bit[3:0]: br_hscale[11:8]

#define BR_HSCALE2_REG_ADDR 0x5843 // BR HSCALE 0x2B RW
// Bit[7:0]: br_hscale[7:0]

#define BR_VSCALE_REG_ADDR 0x5844 // BR VSCALE 0x01 RW
// Bit[2:0]: br_vscale[10:8]

#define BR_VSCALE2_REG_ADDR 0x5845 // BR VSCALE 0x8D RW
// Bit[7:0]: br_vscale[7:0]

#define G_HSCALE_REG_ADDR 0x5846 // G HSCALE 0x01 RW
// Bit[3:0]: g_hscale[11:8]

#define G_HSCALE2_REG_ADDR 0x5847 // G HSCALE 0x8F RW
// Bit[7:0]: g_hscale[7:0]

#define G_VSCALE_REG_ADDR 0x5848 // G VSCALE 0x01 RW
// Bit[2:0]: g_vscale[10:8]

#define G_VSCALE2_REG_ADDR 0x5849 // G VSCALE 0x09 RW
// Bit[7:0]: g_vscale[7:0]

// AWB Control Registers-----------------------------------------------------------
#define AWB_CTRL_REG_ADDR 0x5180 // AWB CTRL 0x00 RW
// Bit[6]: fast_awb (0: Disable fast AWB calculation function, 1: Enable fast AWB calculation function)
// Bit[5]: freeze_gain_en (Output AWB gains will be input AWB gains when enabled)
// Bit[4]: freeze_sum_en (Sums and averages value will be the same as the previous frame when set)
// Bit[3]: gain_man_en (0: Output calculated gains, 1: Output manual gains set by registers)
// Bit[2]: start_sel (0: Select the last HREF falling edge before gain input as calculated start signal, 1: Select the last HREF falling edge after gain input as calculated start signal)

#define AWB_DELTA_REG_ADDR 0x5181 // AWB DELTA 0x20 RW
// Bit[7]: delta_opt
// Bit[6]: base_man_en
// Bit[5:0]: awb_delta (Delta value to increase or decrease the gains)

#define AWB_STABLE_RANGE_REG_ADDR 0x5182 // STABLE RANGE 0x04 RW
// Bit[7:0]: stable_range

#define STABLE_RANGEW_REG_ADDR 0x5183 // STABLE RANGEW 0x08 RW
// Bit[7:0]: stable_rangew (Wide stable range)

#define HSIZE_MAN_REG_ADDR 0x5184 // HSIZE_MAN 0x01 RW
// Bit[3:0]: hsize_man[11:8]

#define HSIZE_MAN2_REG_ADDR 0x5185 // HSIZE_MAN 0xE0 RW
// Bit[7:0]: hsize_man[7:0]

#define MANUAL_RED_GAIN_MSB_REG_ADDR 0x5186 // MANUAL RED GAIN MSB 0x04 RW
// Bit[3:0]: red_gain_man[11:8]

#define MANUAL_RED_GAIN_LSB_REG_ADDR 0x5187 // MANUAL RED GAIN LSB 0x00 RW
// Bit[7:0]: red_gain_man[7:0]

#define MANUAL_GREEN_GAIN_MSB_REG_ADDR 0x5188 // MANUAL GREEN GAIN MSB 0x04 RW
// Bit[3:0]: grn_gain_man[11:8]

#define MANUAL_GREEN_GAIN_LSB_REG_ADDR 0x5189 // MANUAL GREEN GAIN LSB 0x00 RW
// Bit[7:0]: grn_gain_man[7:0]

#define MANUAL_BLUE_GAIN_MSB_REG_ADDR 0x518A // MANUAL BLUE GAIN MSB 0x04 RW
// Bit[3:0]: blu_gain_man[11:8]

#define MANUAL_BLUE_GAIN_LSB_REG_ADDR 0x518B // MANUAL BLUE GAIN LSB 0x00 RW
// Bit[7:0]: blu_gain_man[7:0]

#define RED_GAIN_LIMIT_REG_ADDR 0x518C // RED GAIN LIMIT 0xF0 RW
// Bit[7:4]: red_gain_up_limit (Highest 4 bits of the upper limit for red gain)
// Bit[3:0]: red_gain_dn_limit (Highest 4 bits of the lower limit for red gain)
// Max red gain is {red_gan_up_limit, FF}
// Min red gain is {red_gain_dn_limit, 00}

#define GREEN_GAIN_LIMIT_REG_ADDR 0x518D // GREEN GAIN LIMIT 0xF0 RW
// Bit[7:4]: green_gain_up_limit (Highest 4 bits of the upper limit for green gain)
// Bit[3:0]: green_gain_dn_limit (Highest 4 bits of the lower limit for green gain)
// Max green gain is {green_gan_up_limit, FF}
// Min green gain is {green_gain_dn_limit, 00}

#define BLUE_GAIN_LIMIT_REG_ADDR 0x518E // BLUE GAIN LIMIT 0xF0 RW
// Bit[7:4]: blue_gain_up_limit (Highest 4 bits of the upper limit for blue gain)
// Bit[3:0]: blue_gain_dn_limit (Highest 4 bits of the lower limit for blue gain)
// Max blue gain is {blue_gan_up_limit, FF}
// Min blue gain is {blue_gain_dn_limit, 00}

// System Control Registers --------------------------------------------------------------------------
#define SC_CMMN_PAD_OEN0_REG_ADDR 0x3000 // SC_CMMN_PAD_OEN0 0x00 RW
// Bit[7:0]: io_y_oen[11:8]

#define SC_CMMN_PAD_OEN1_REG_ADDR 0x3001 // SC_CMMN_PAD_OEN1 0x00 RW
// Bit[7:0]: io_y_oen[7:0]

#define SC_CMMN_PAD_OEN2_REG_ADDR 0x3002 // SC_CMMN_PAD_OEN2 0x00 RW
// Bit[7]: io_vsync_oen
// Bit[6]: io_href_oen
// Bit[5]: io_pclk_oen
// Bit[4]: io_frex_oen
// Bit[3]: io_strobe_oen
// Bit[2]: io_sda_oen
// Bit[1]: io_gpio1_oen
// Bit[0]: io_gpio0_oen

#define SC_CMMN_PLL_CTR13_REG_ADDR 0x3006 // SC_CMMN_PLL_CTR13 0x00 RW
// Bit[5:2]: SDIV (Clock divider for 50/60 Hz detection block)

#define SC_CMMN_PAD_OUT0_REG_ADDR 0x3008 // SC_CMMN_PAD_OUT0 0x00 RW
// Bit[3:0]: io_y_o[11:8]

#define SC_CMMN_PAD_OUT1_REG_ADDR 0x3009 // SC_CMMN_PAD_OUT1 0x00 RW
// Bit[7:0]: io_y_o[7:0]

#define SC_CMMN_CHIP_ID_HIGH_REG_ADDR 0x300A // SC_CMMN_CHIP_ID 0x56 R
// Chip ID High

#define SC_CMMN_CHIP_ID_LOW_REG_ADDR 0x300B // SC_CMMN_CHIP_ID 0x47 R
// Chip ID Low

#define SC_CMMN_SCCB_ID_REG_ADDR 0x300C // SC_CMMN_SCCB_ID 0x6C RW
// SCCB ID

#define SC_CMMN_PAD_OUT2_REG_ADDR 0x300D // SC_CMMN_PAD_OUT2 0x00 RW
// Bit[7]: io_vsync_o
// Bit[6]: io_href_o
// Bit[5]: io_pclk_o
// Bit[4]: io_frex_o
// Bit[3]: io_strobe_o
// Bit[2]: io_sda_o
// Bit[1]: io_gpio1_o
// Bit[0]: io_gpio0_o

#define SC_CMMN_PAD_SEL0_REG_ADDR 0x300E // SC_CMMN_PAD_SEL0 0x00 RW
// Bit[3:0]: io_y_sel[11:8]

// System Control Registers (Sheet 1 of 4)

#define SC_CMMN_PAD_SEL1_REG_ADDR 0x300F // SC_CMMN_PAD_SEL1 0x00 RW
// Bit[7:0]: io_y_sel[7:0]

#define SC_CMMN_PAD_SEL2_REG_ADDR 0x3010 // SC_CMMN_PAD_SEL2 0x00 RW
// Bit[7]: io_vsync_sel
// Bit[6]: io_href_sel
// Bit[5]: io_pclk_sel
// Bit[4]: io_frex_sel
// Bit[3]: io_strobe_sel
// Bit[2]: io_sda_sel
// Bit[1]: io_gpio1_sel
// Bit[0]: io_gpio0_sel

#define SC_CMMN_PAD_PK_REG_ADDR 0x3011 // SC_CMMN_PAD_PK 0x02 RW
// Bit[7]: pd_dato_en
// Bit[6:5]: iP2X3v[3:2]
// Bit[1]: frex_enb
// 0: Enable
// 1: Disable

#define SC_CMMN_A_PWC_PK_O_REG_ADDR 0x3013 // SC_CMMN_A_PWC_PK_O 0x00 RW
// Bit[7:4]: Debug control (Changing these registers is not recommended)
// Bit[3]: bp_regulator
// 0: Enable internal regulator
// 1: Disable internal regulator
// Bit[2:0]: Debug control (Changing these registers is not recommended)

#define SC_CMMN_A_PWC_PK_0B_REG_ADDR 0x3014 // SC_CMMN_A_PWC_PK_0B 0x0B RW
// Bit[6:4]: apd[2:0]
// Bit[3:0]: DIO

#define SC_CMMN_MIPI_PHY_REG_ADDR 0x3016 // SC_CMMN_MIPI_PHY 0x00 RW
// Bit[7:6]: LPH
// Bit[3]: mipi_pad_enable
// Bit[2]: pgm_bp_hs_en_lat (bypass the latch of hs_enable)
// Bit[1:0]: ictl[1:0] (Bias current adjustment)

#define SC_CMMN_MIPI_PHY_10_REG_ADDR 0x3017 // SC_CMMN_MIPI_PHY_10 0x10 RW
// Bit[7:6]: pgm_vcm[1:0] (High-speed common mode voltage)
// Bit[5:4]: pgm_lptx[1:0] (Driving strength of low-speed transmitter)
// Bit[3]: IHALF (Bias current reduction)
// Bit[2]: pgm_vicd (CD input low voltage)
// Bit[1]: pgm_vih (CD input high voltage-dummy)
// Bit[0]: pgm_hs_valid (Valid delay-dummy)

#define SC_CMMN_MIPI_SC_CTRL_REG_ADDR 0x3018 // SC_CMMN_MIPI_SC_CTRL 0x58 RW
// Bit[7:5]: mipi_lane_mode
// 0: One-lane mode
// 1: Two-lane mode
// Bit[4]: r_phy_pd_mipi
// 1: Power down PHY HS TX
// Bit[3]: r_phy_pd_lprx
// 1: Power down PHY LP RX module
// Bit[2]: mipi_en
// 0: DVP enable
// 1: MIPI enable
// Bit[1]: mipi_susp_reg
// MIPI system Suspend register
// 1: Suspend
// Bit[0]: lane_dis_op
// 0: Use mipi_release1/2 and lane_disable1/2 to disable two data lanes
// 1: Use lane_disable1/2 to disable two data lanes

#define SC_CMMN_MIPI_SC_CTRL1_REG_ADDR 0x3019 // SC_CMMN_MIPI_SC_CTRL1 0x10 RW
// Bit[7:0]: MIPI ULPS resume mark1 detect length

#define SC_CMMN_MISC_CTRL_REG_ADDR 0x3021 // SC_CMMN_MISC_CTRL 0x23 RW
// Bit[5]: fst_stby_ctr
// 1: Software standby enter at l_blk
// 0: Software standby enter at v_blk
// Bit[4]: mipi_ctr_en
// 1: Enable MIPI remote reset and suspend control SC
// 0: Disable the function
// Bit[3]: mipi_rst_sel
// 0: MIPI remote reset all registers
// 1: MIPI remote reset all digital modules
// Bit[2]: gpio_pclk_en
// Bit[1]: frex_ef_sel
// Bit[0]: cen_global_o

#define SC_CMMN_MIPI_SC_CTRL2_REG_ADDR 0x3022 // SC_CMMN_MIPI_SC_CTRL2 0x00 RW
// Bit[3]: lptx_ck_opt
// Bit[2]: pull_down_clk_lane
// Bit[1]: pull_down_data_lane2
// Bit[0]: pull_down_data_lane1

#define SC_CMMN_SUB_ID_REG_ADDR 0x302A // SC_CMMN_SUB_ID – R
// Bit[7:4]: Process
// Bit[3:0]: Version

#define SC_CMMN_PLL_CTRL0_REG_ADDR 0x3034 // SC_CMMN_PLL_CTRL0 0x1A RW
// Bit[6:4]: pll_charge_pump
// Bit[3:0]: mipi_bit_mode
// 0000: 8-bit mode
// 0001: 10-bit mode
// Others: Reserved for future use

#define SC_CMMN_PLL_CTRL1_REG_ADDR 0x3035 // SC_CMMN_PLL_CTRL1 0x11 RW
// Bit[7:4]: system_clk_div
// Will slow down all clocks
// Bit[3:0]: scale_divider_mipi
// MIPI PCLK/SERCLK can be slowed down when the image is scaled down

#define SC_CMMN_PLL_MULTIPLIER_REG_ADDR 0x3036 // SC_CMMN_PLL_MULTIPLIER 0x69 RW
// Bit[7:0]: PLL_multiplier (4~252) can be any integer during 4~127 and only even integer during 128~252

#define SC_CMMN_PLL_CTRL13_REG_ADDR 0x3037 // SC_CMMN_PLL_CTRL13 0x03 RW
// Bit[4]: pll_root_div
// 0: Bypass
// 1: /2
// Bit[3:0]: pll_prediv
// 1, 2, 3, 4, 6, 8

#define SC_CMMN_PLL_CTRL_R_REG_ADDR 0x3039 // SC_CMMN_PLL_CTRL_R 0x00 RW
// Bit[7]: pll_bypass

#define SC_CMMN_PLLS_CTRL0_REG_ADDR 0x303A // SC_CMMN_PLLS_CTRL0 0x00 RW
// Bit[7]: plls_bypass

#define SC_CMMN_PLLS_CTRL1_REG_ADDR 0x303B // SC_CMMN_PLLS_CTRL1 0x19 RW
// Bit[4:0]: plls_multiplier

#define SC_CMMN_PLLS_CTRL2_REG_ADDR 0x303C // SC_CMMN_PLLS_CTRL2 0x11 RW
// Bit[6:4]: plls_cp
// Bit[3:0]: plls_sys_div

#define SC_CMMN_PLLS_CTRL3_REG_ADDR 0x303D // SC_CMMN_PLLS_CTRL3 0x30 RW
// Bit[5:4]: plls_pre_div
// 00: /1
// 01: /1.5
// 10: /2
// 11: /3
// Bit[2]: plls_div_r
// 0: /1
// 1: /2
// Bit[1:0]: plls_seld5
// 00: /1
// 01: /1
// 10: /2
// 11: /2.5

//SCCB related registers----------------------------------------------------------
// SCCB Control Registers

#define SCCB_CTRL_REG_ADDR 0x3100 // SCCB CTRL 0x00 RW
// Bit[3]: r_sda_dly_en
// Bit[2:0]: r_sda_dly

#define SCCB_OPT_REG_ADDR 0x3101 // SCCB OPT 0x12 RW
// Bit[4]: en_ss_addr_inc
// Bit[3]: r_sda_byp_sync
// 0: Two clock stage SYNC for sda_i
// 1: No sync for sda_i
// Bit[2]: r_scl_byp_sync
// 0: Two clock stage SYNC for scl_i
// 1: No sync for scl_i
// Bit[1]: r_msk_glitch
// Bit[0]: r_msk_stop

#define SCCB_FILTER_REG_ADDR 0x3102 // SCCB FILTER 0x00 RW
// Bit[7:4]: r_sda_num
// Bit[3:0]: r_scl_num

#define SCCB_SYSREG_REG_ADDR 0x3103 // SCCB SYSREG 0x00 RW
// Bit[6]: ctrl_rst_mipisc
// Bit[5]: ctrl_rst_srb
// Bit[4]: ctrl_rst_sccb_s
// Bit[3]: ctrl_rst_pon_sccb_s
// Bit[2]: ctrl_rst_clkmod
// Bit[1]: ctrl_rst_mipi_phy_rst_o
// Bit[0]: ctrl_pll_rst_o

#define PWUP_DIS_REG_ADDR 0x3104 // PWUP DIS 0x01 RW
// Bit[4]: r_srb_clk_syn_en
// Bit[3]: pwup_dis2
// Bit[2]: pwup_dis1
// Bit[1]: pll_clk_sel
// Bit[0]: pwup_dis0

#define PADCLK_DIV_REG_ADDR 0x3105 // PADCLK DIV 0x11 RW
// Bit[5]: SCLK use p_clk_i
// Bit[4]: Sleep enable
// Bit[3:0]: PADCLK divider for SCCB

#define SRB_CTRL_REG_ADDR 0x3106 // SRB CTRL 0xF9 RW
// Bit[3:2]: PLL clock divider
// 00: pll_sclk
// 01: pll_sclk/2
// 10: pll_sclk/4
// 11: pll_sclk
// Bit[1]: rst_arb
// 1: Reset arbiter
// Bit[0]: sclk_arb
// 1: Enable SCLK to arbiter

//group addressing for SCCB:
// Group Address Registers
#define GROUP_ADR0_REG_ADDR 0x3200 // GROUP ADR0 0x00 RW
// Group0 Start Address in SRAM, actual address is {0x3200[3:0], 4'h0}

#define GROUP_ADR1_REG_ADDR 0x3201 // GROUP ADR1 0x04 RW
// Group1 Start Address in SRAM, actual address is {0x3201[3:0], 4'h0}

#define GROUP_ADR2_REG_ADDR 0x3202 // GROUP ADR2 0x08 RW
// Group2 Start Address in SRAM, actual address is {0x3202[3:0], 4'h0}

#define GROUP_ADR3_REG_ADDR 0x3203 // GROUP ADR3 0x0B RW
// Group3 Start Address in SRAM, actual address is {0x3203[3:0], 4'h0}

#define GROUP_LEN0_REG_ADDR 0x3204 // GROUP LEN0 – R
// Length of Group0

#define GROUP_LEN1_REG_ADDR 0x3205 // GROUP LEN1 – R
// Length of Group1

#define GROUP_LEN2_REG_ADDR 0x3206 // GROUP LEN2 – R
// Length of Group2

#define GROUP_LEN3_REG_ADDR 0x3207 // GROUP LEN3 – R
// Length of Group3

#define GROUP_ACCESS_REG_ADDR 0x3208 // GROUP ACCESS – W
// Bit[7:4]: Group_ctrl
// 0000: Enter group write mode
// 0001: Exit group write mode
// 1010: Initiate group write
// Bit[3:0]: Group ID
// 0000: Group 0
// 0001: Group 1
// 0010: Group 2
// 0011: Group 3

// Timing Control Registers--------------------------------------------------------------------
#define TIMING_X_ADDR_START_REG_ADDR 0x3800 // TIMING_X_ADDR_START 0x00 RW
// Bit[3:0]: x_addr_start[11:8]

#define TIMING_X_ADDR_START_LSB_REG_ADDR 0x3801 // TIMING_X_ADDR_START 0x0C RW
// Bit[7:0]: x_addr_start[7:0]

#define TIMING_Y_ADDR_START_REG_ADDR 0x3802 // TIMING_Y_ADDR_START 0x00 RW
// Bit[3:0]: y_addr_start[11:8]

#define TIMING_Y_ADDR_START_LSB_REG_ADDR 0x3803 // TIMING_Y_ADDR_START 0x04 RW
// Bit[7:0]: y_addr_start[7:0]

#define TIMING_X_ADDR_END_REG_ADDR 0x3804 // TIMING_X_ADDR_END 0x0A RW
// Bit[3:0]: x_addr_end[11:8]

#define TIMING_X_ADDR_END_LSB_REG_ADDR 0x3805 // TIMING_X_ADDR_END 0x33 RW
// Bit[7:0]: x_addr_end[7:0]

#define TIMING_Y_ADDR_END_REG_ADDR 0x3806 // TIMING_Y_ADDR_END 0x07 RW
// Bit[3:0]: y_addr_end[11:8]

#define TIMING_Y_ADDR_END_LSB_REG_ADDR 0x3807 // TIMING_Y_ADDR_END 0xA3 RW
// Bit[7:0]: y_addr_end[7:0]

#define TIMING_X_OUTPUT_SIZE_REG_ADDR 0x3808 // TIMING_X_OUTPUT_SIZE 0x0A RW
// Bit[3:0]: DVP output horizontal width[11:8]

#define TIMING_X_OUTPUT_SIZE_LSB_REG_ADDR 0x3809 // TIMING_X_OUTPUT_SIZE 0x20 RW
// Bit[7:0]: DVP output horizontal width[7:0]

#define TIMING_Y_OUTPUT_SIZE_REG_ADDR 0x380A // TIMING_Y_OUTPUT_SIZE 0x07 RW
// Bit[3:0]: DVP output vertical height[11:8]

#define TIMING_Y_OUTPUT_SIZE_LSB_REG_ADDR 0x380B // TIMING_Y_OUTPUT_SIZE 0x98 RW
// Bit[7:0]: DVP output vertical height[7:0]

#define TIMING_HTS_REG_ADDR 0x380C // TIMING_HTS 0x0A RW
// Bit[4:0]: Total horizontal size[12:8]

#define TIMING_HTS_LSB_REG_ADDR 0x380D // TIMING_HTS 0x8C RW
// Bit[7:0]: Total horizontal size[7:0]

#define TIMING_VTS_REG_ADDR 0x380E // TIMING_VTS 0x07 RW
// Bit[1:0]: Total vertical size[9:8]

#define TIMING_VTS_LSB_REG_ADDR 0x380F // TIMING_VTS 0xB0 RW
// Bit[7:0]: Total vertical

#define TIMING_ISP_X_WIN_REG_ADDR 0x3810 // TIMING_ISP_X_WIN 0x00 RW
// Bit[3:0]: ISP horizontal offset[11:8]

#define TIMING_ISP_X_WIN_LSB_REG_ADDR 0x3811 // TIMING_ISP_X_WIN 0x04 RW
// Bit[7:0]: ISP horizontal offset[7:0]

#define TIMING_ISP_Y_WIN_REG_ADDR 0x3812 // TIMING_ISP_Y_WIN 0x00 RW
// Bit[3:0]: ISP vertical offset[11:8]

#define TIMING_ISP_Y_WIN_LSB_REG_ADDR 0x3813 // TIMING_ISP_Y_WIN 0x02 RW
// Bit[7:0]: ISP vertical offset[7:0]

#define TIMING_X_INC_REG_ADDR 0x3814 // TIMING_X_INC 0x11 RW
// Bit[7:4]: h_odd_inc
// Horizontal subsample odd increase number
// Bit[3:0]: h_even_inc
// Horizontal subsample even increase number

#define TIMING_Y_INC_REG_ADDR 0x3815 // TIMING_Y_INC 0x11 RW
// Bit[7:4]: v_odd_inc
// Vertical subsample odd increase number
// Bit[3:0]: v_even_inc
// Vertical subsample even increase number

#define TIMING_HSYNCST_REG_ADDR 0x3816 // TIMING_HSYNCST 0x00 RW
// Bit[3:0]: HSYNC start point[11:8]

#define TIMING_HSYNCST_LSB_REG_ADDR 0x3817 // TIMING_HSYNCST 0x00 RW
// Bit[7:0]: HSYNC start point[7:0]

#define TIMING_HSYNCW_REG_ADDR 0x3818 // TIMING_HSYNCW 0x00 RW
// Bit[3:0]: HSYNC window[11:8]

#define TIMING_HSYNCW_LSB_REG_ADDR 0x3819 // TIMING_HSYNCW 0x00 RW
// Bit[7:0]: HSYNC window[7:0]

#define TIMING_TC_REG20_REG_ADDR 0x3820 // TIMING_TC_REG20 0x40 RW
// Bit[2]: r_vflip_isp
// Bit[1]: r_vflip_snr
// Bit[0]: r_vbin

#define TIMING_TC_REG21_REG_ADDR 0x3821 // TIMING_TC_REG21 0x00 RW
// Bit[2]: r_mirror_isp
// Bit[1]: r_mirror_snr
// Bit[0]: r_hbin

#define TIMING_TC_REG22_REG_ADDR 0x3822 // TIMING_TC_REG22 0x10 RW
// Bit[4:0]: r_ablc

//Strobe control related registers ---------------------------------------------------------
#define STROBE_RSTRB_REG_ADDR 0x3B00 // STROBE_RSTRB 0x00 RW
// Bit[7]: Strobe ON
// Bit[6]: Reverse
// Bit[3:2]: width_in_xenon
// Bit[1:0]: Mode select
// 00: Xenon
// 01: LED1
// 10: LED2
// 11: LED3

#define STROBE_FREX_EXP_H2_REG_ADDR 0x3B01 // STROBE_FREX_EXP_H2 0x00 RW
// Bit[7:0]: frex_exp[23:16]

#define STROBE_SHUTTER_DLY_REG_ADDR 0x3B02 // STROBE_SHUTTER_DLY 0x08 RW
// Bit[4:0]: shutter_dly[12:8]

#define STROBE_SHUTTER_DLY_LSB_REG_ADDR 0x3B03 // STROBE_SHUTTER_DLY 0x00 RW
// Bit[7:0]: shutter_dly[7:0]

#define STROBE_FREX_EXP_H_REG_ADDR 0x3B04 // STROBE_FREX_EXP_H 0x04 RW
// Bit[7:0]: frex_exp[15:8]

#define STROBE_FREX_EXP_L_REG_ADDR 0x3B05 // STROBE_FREX_EXP_L 0x00 RW
// Bit[7:0]: frex_exp[7:0]

#define STROBE_FREX_CTRL0_REG_ADDR 0x3B06 // STROBE_FREX_CTRL0 0x04 RW
// Bit[7:6]: frex_pchg_width
// Bit[5:4]: frex_strobe_option
// Bit[3:0]: frex_strobe_width[3:0]

#define STROBE_FREX_MODE_SEL_REG_ADDR 0x3B07 // STROBE_FREX_MODE_SEL 0x08 RW
// Bit[4]: frex_sa1
// Bit[3]: fx1_fm_en
// Bit[2]: frex_inv
// Bit[1:0]: Frex mode select
// 00: frex_strobe mode 0
// 01: frex_strobe mode 1
// 1x: Rolling strobe

#define STROBE_FREX_EXP_REQ_REG_ADDR 0x3B08 // STROBE_FREX_EXP_REQ 0x00 RW
// Bit[0]: frex_exp_req

#define FREX_SHUTTER_DELAY_REG_ADDR 0x3B09 // FREX_SHUTTER_DELAY 0x00 RW
// Bit[2:0]: FREX end option

#define STROBE_FREX_RST_LENGTH_REG_ADDR 0x3B0A // STROBE_FREX_RST_LENGTH 0x04 RW
// Bit[2:0]: frex_rst_length[2:0]

#define STROBE_WIDTH_REG_ADDR 0x3B0B // STROBE_WIDTH 0x00 RW
// Bit[7:0]: frex_strobe_width [19:12]

#define STROBE_WIDTH_LSB_REG_ADDR 0x3B0C // STROBE_WIDTH 0x3D RW
// Bit[7:0]: frex_strobe_width[11:4]

//Frame control registers (frame skipping) ----------------------------------------------------
#define FRAME_CONTROL00_REG_ADDR 0x4200 // FRAME CONTROL00 0x00 RW
// Bit[2]: fcnt_eof_sel
// Bit[1]: fcnt_mask_dis
// Bit[0]: Frame counter reset

//Digital video port (parrallel csi) related registers ------------------------------------------
#define DVP_MODE_SELECT_REG_ADDR 0x4700 // DVP MODE SELECT 0x04 RW
// Bit[3]: CCIR v select
// Bit[2]: CCIR f select
// Bit[1]: CCIR656 mode enable
// Bit[0]: HSYNC mode enable

#define DVP_VSYNC_WIDTH_CTRL_REG_ADDR 0x4701 // DVP VSYNC WIDTH CONTRL 0x01 RW
// VSYNC Width (in terms of number of lines)

#define DVP_HSYVSY_NEG_WIDTH_MSB_REG_ADDR 0x4702 // DVP_HSYVSY_NEG_WIDTH 0x01 RW
// Bit[7:0]: VSYNC length in terms of pixel count[15:8]

#define DVP_HSYVSY_NEG_WIDTH_LSB_REG_ADDR 0x4703 // DVP_HSYVSY_NEG_WIDTH 0x00 RW
// Bit[7:0]: VSYNC length in terms of pixel count[7:0]

#define DVP_VSYNC_MODE_REG_ADDR 0x4704 // DVP VSYNC MODE 0x00 RW
// Bit[3:2]: r_vsyncount_sel
// Bit[1]: r_vsync3_mod
// Bit[0]: r_vsync2_mod

#define DVP_EOF_VSYNC_DELAY_MSB_REG_ADDR 0x4705 // DVP_EOF_VSYNC DELAY 0x00 RW
// Bit[7:0]: eof_vsync_delay[23:16]

#define DVP_EOF_VSYNC_DELAY_MID_REG_ADDR 0x4706 // DVP_EOF_VSYNC DELAY 0x00 RW
// Bit[7:0]: eof_vsync_delay[15:8]

#define DVP_EOF_VSYNC_DELAY_LSB_REG_ADDR 0x4707 // DVP_EOF_VSYNC DELAY 0x00 RW
// Bit[7:0]: eof_vsync_delay[7:0]

#define DVP_POL_CTRL_REG_ADDR 0x4708 // DVP_POL_CTRL 0x01 RW
// Bit[7]: Clock DDR mode enable
// Bit[5]: VSYNC gated clock enable
// Bit[4]: HREF gated clock enable
// Bit[3]: No first for FIFO
// Bit[2]: HREF polarity reverse
// Bit[1]: VSYNC polarity reverse
// Bit[0]: PCLK polarity reverse

#define BIT_TEST_PATTERN_REG_ADDR 0x4709 // BIT_TEST_PATTERN 0x00 RW
// Bit[7]: FIFO bypass mode
// Bit[6:4]: Data bit swap
// Bit[3]: Bit test mode
// Bit[2]: 10-bit bit test
// Bit[1]: 8-bit bit test
// Bit[0]: Bit test enable

#define DVP_BYP_CTRL_MSB_REG_ADDR 0x470A // DVP_BYP_CTRL 0x00 RW
// Bit[7:0]: bypass_ctrl[15:8]

#define DVP_BYP_CTRL_LSB_REG_ADDR 0x470B // DVP_BYP_CTRL 0x00 RW
// Bit[7:0]: bypass_ctrl[7:0]

#define DVP_BYP_SEL_REG_ADDR 0x470C // DVP_BYP_SEL 0x00 RW
// Bit[4]: HREF select
// Bit[3:0]: Bypass select

// MIPI-csi related registers -----------------------------------------------------------------
#define MIPI_CTRL_00_REG_ADDR 0x4800 // MIPI CTRL 00 0x04 RW
// Bit[7]: MIPI High-Speed Mode Only
// 0: MIPI supports CD and ESCAPE mode
// 1: MIPI always in High-Speed mode
// Bit[6]: Enable Clock Lane Mark1 during Resume
// Bit[5]: Clock Lane Gating Enable
// 0: Clock lane is free running
// 1: Gate clock lane when no packet to transmit
// Bit[4]: Line Sync Enable
// 0: Do not send a line short packet for each line
// 1: Send a line short packet for each line
// Bit[3]: Data Lane Select
// 0: Use lane1 as the default data lane
// 1: Use lane2 as the default data lane
// Bit[2]: Idle Status
// 0: MIPI bus will be LP00 when no packet to transmit
// 1: MIPI bus will be LP11 when no packet to transmit
// Bit[1]: Clock Lane First Bits
// 0: Output 0x55
// 1: Output 0xAA
// Bit[0]: Clock Lane Disable
// 1: Manually set the clock lane to low power mode

#define MIPI_CTRL_01_REG_ADDR 0x4801 // MIPI CTRL 01 0x0F RW
// Bit[7]: Long Packet Data Type Manual Enable
// 0: Use mipi_dt
// 1: Use dt_man_o as long packet data (see register 0x4814[5:0])
// Bit[6]: Short Packet Data Type Manual Enable
// 1: Use dt_spkt as short packet data (see register 0x4815[5:0])
// Bit[5]: Short Packet Word Counter Manual Enable
// 0: Use frame counter or line counter
// 1: Select spkt_wc_reg_o (see {0x4812, 0x4813})
// Bit[4]: PH Bit Order for ECC
// 0: {DI[7:0],WC[7:0],WC[15:8]}
// 1: {DI[0:7],WC[0:7],WC[8:15]}
// Bit[3]: PH Byte Order for ECC
// 0: {DI,WC_l,WC_h}
// 1: {DI,WC_h,WC_l}
// Bit[2]: PH Byte Order2 for ECC
// 0: {DI,WC}
// 1: {WC,DI}
// Bit[1]: Mark1 Enable for Lane 1
// 1: After each reset release, lane 1 should send mark1 for wkup_dly_o when mipi_sys_susp = 1
// Bit[0]: Mark1 Enable for Lane 2
// 1: After each reset release, lane 2 should send mark1 for wkup_dly_o when mipi_sys_susp = 1

#define MIPI_CTRL_02_REG_ADDR 0x4802 // MIPI CTRL 02 0x00 RW
// Bit[7]: High-Speed Prepare Select
// 0: Auto calculate T_hs_prepare, unit pclk2x
// 1: Use hs_prepare_min_o[7:0]
// Bit[6]: Clock Prepare Select
// 0: Auto calculate T_clk_prepare, unit pclk2x
// 1: Use clk_prepare_min_o[7:0]
// Bit[5]: Clock Post Select
// 0: Auto calculate T_clk_post, unit pclk2x
// 1: Use clk_post_min_o[7:0]
// Bit[4]: Clock Trail Select
// 0: Auto calculate T_clk_trail, unit pclk2x
// 1: Use clk_trail_min_o[7:0]
// Bit[3]: High-Speed Exit Select
// 0: Auto calculate T_hs_exit, unit pclk2x
// 1: Use hs_exit_min_o[7:0]
// Bit[2]: High-Speed Zero Select
// 0: Auto calculate T_hs_zero, unit pclk2x
// 1: Use hs_zero_min_o[7:0]
// Bit[1]: High-Speed Trail Select
// 0: Auto calculate T_hs_trail, unit pclk2x
// 1: Use hs_trail.min_o[7:0]
// Bit[0]: Clock Zero Select
// 0: Auto calculate T_clk_zero, unit pclk2x
// 1: Use clk_zero_min_o[7:0]

#define MIPI_CTRL_03_REG_ADDR 0x4803 // MIPI CTRL 03 0x50 RW
// Bit[7:6]: LP Glitch Number
// 0: Use 2d of lp_in
// 1: Mask one SCLK cycle glitch of lp_in
// Bit[5:4]: CD Glitch Number
// 0: Use 2d of lp_cd_in
// 1: Mask one SCLK cycle glitch of lp_cd_in
// Bit[3]: Enable CD Plus of Data Lane 1
// 0: Disable
// 1: Enable
// Bit[2]: Enable CD Plus of Data Lane 2
// 0: Disable
// 1: Enable
// Bit[1]: Enable CD of Data Lane 1 from PHY
// 0: Disable
// 1: Enable
// Bit[0]: Enable CD of Data Lane 2 from PHY
// 0: Disable
// 1: Enable

#define MIPI_CTRL_04_REG_ADDR 0x4804 // MIPI CTRL 04 0x8D RW
// MIPI Control 04
// Bit[7]: Wait Packet End
// 1: Wait HS packet end when sending UL command
// Bit[6]: Transmit LSB First
// 0: lp_tx and lp_rx high bit first
// 1: Low power transmit low bit first
// Bit[5]: Direction Recover Select
// 0: Auto change to output only when TurnAround command
// 1: Auto change to output when LP11 and GPIO are output
// Bit[4]: MIPI Register Enable
// 0: Disable MIPI_REG_P to access registers, LP data will write to VFIFO
// 1: Enable MIPI_REG_P to access registers
// Bit[3]: Address Read/Write Register Will Auto Add 1
// 0: Disable
// 1: Enable
// Bit[2]: LP TX Lane Select
// 0: Select lane1 to transmit LP data
// 1: Select lane2 to transmit LP data
// Bit[1]: Write First Byte
// 1: lp_rx will write the first byte (command byte) to RAM
// Bit[0]: Read Turnaround Enable
// 1: Send TurnAround command after sending register read data

#define MIPI_CTRL_05_REG_ADDR 0x4805 // MIPI CTRL 05 0x10 RW
// MIPI Control 05
// Bit[7]: MIPI Lane 1 Disable
// 1: Disable MIPI data lane 1, lane 1 will be LP00
// Bit[6]: MIPI Lane 2 Disable
// 1: Disable MIPI data lane 2, lane 2 will be LP00
// Bit[5]: LPX P Select
// 0: Automatically calculate t_lpx_o in pclkex domain, unit pclk2x
// 1: Use lp_p_min[7:0]
// Bit[4]: LP RX Intr Select
// 0: Send lp_rx_intr_o at the first byte
// 1: Send lp_rx_intr_o at the end of receiving
// Bit[3]: CD Test Select
// 1: Select PHY test pins
// Bit[2]: MIPI Register Mask
// 1: Disable MIPI access SRB
// Bit[1]: Clip Enable
// Bit[0]: HD SK Enable
// 0: Disable MIPI and MCU handshake registers
// 1: Enable MIPI and MCU handshake registers

#define MIPI_REG_RW_CTRL_REG_ADDR 0x4806 // MIPI REG RW CTRL 0x28 RW
// Bit[7]: PRBS Enable (Test Mode)
// Bit[6]: MIPI Test
// Bit[5]: MIPI LP Operation
// 0: Use new option to reduce mipi_lptx_p
// Bit[4]: Two Lane Manual Enable
// 1: Use two_lane_man to manually control two_lane_mode
// Bit[3]: Two Lane Manual
// Bit[2]: Reset Return Enable
// 1: Change to input to allow host RW register after reset
// Bit[1]: Frame End Enable
// 1: After frame end packet, change to input to allow host RW register
// Bit[0]: Line End Enable
// 1: After line end packet, change to input to allow host RW register

#define MIPI_BIT_ORDER_REG_ADDR 0x480A // MIPI BIT ORDER 0x00 RW
// Bit[2]: Bit Order Reverse
// Bit[1:0]: Bit Position Adjustment
// 01: {D[7:0],D[9:8]}
// 10: {D[1:0],D[9:2]}

#define MIPI_MAX_FRAME_COUNT_HIGH_REG_ADDR 0x4810 // MIPI MAX FRAME COUNT 0xFF RW
// High Byte of Max Frame Count of Frame Sync Short Packet

#define MIPI_MAX_FRAME_COUNT_LOW_REG_ADDR 0x4811 // MIPI MAX FRAME COUNT 0xFF RW
// Low Byte of Max Frame Count of Frame Sync Short Packet

#define MIPI_CTRL_14_REG_ADDR 0x4814 // MIPI CTRL14 0x2A RW
// MIPI Control 14
// Bit[7:6]: Virtual Channel of MIPI
// Bit[5:0]: Data Type in Manual Mode

#define MIPI_DT_SPKT_REG_ADDR 0x4815 // MIPI_DT_SPKT 0x00 RW
// Bit[6]: PCLK Div
// 0: Use rising edge of mipi_pclk_o to generate MIPI bus to PHY
// 1: Use falling edge of mipi_pclk_o to generate MIPI bus to PHY
// Bit[5:0]: Manual Data Type for Short Packet

#define HS_ZERO_MIN_HIGH_REG_ADDR 0x4818 // HS_ZERO_MIN 0x00 RW
// High Byte of the Minimum Value for hs_zero (Unit ns)

#define HS_ZERO_MIN_LOW_REG_ADDR 0x4819 // HS_ZERO_MIN 0x96 RW
// Low Byte of the Minimum Value for hs_zero (Unit ns)
// hs_zero_real = hs_zero_min_o + Tui * ui_hs_zero_min_o

#define HS_TRAIL_MIN_HIGH_REG_ADDR 0x481A // HS_TRAIL_MIN 0x00 RW
// High Byte of the Minimum Value for hs_trail (Unit ns)

#define HS_TRAIL_MIN_LOW_REG_ADDR 0x481B // HS_TRAIL_MIN 0x3C RW
// Low Byte of the Minimum Value for hs_trail
// hs_trail_real = hs_trail_min_o + Tui * ui_hs_trail_min_o

#define CLK_ZERO_MIN_HIGH_REG_ADDR 0x481C // CLK_ZERO_MIN 0x01 RW
// High Byte of the Minimum Value for clk_zero (Unit ns)

#define CLK_ZERO_MIN_LOW_REG_ADDR 0x481D // CLK_ZERO_MIN 0x86 RW
// Low Byte of the Minimum Value for clk_zero (Unit ns)
// clk_zero_real = clk_zero_min_o + Tui * ui_clk_zero_min_o

#define CLK_PREPARE_MIN_HIGH_REG_ADDR 0x481E // CLK_PREPARE_MIN 0x00 RW
// High Byte of the Minimum Value for clk_prepare (Unit ns)
// Bit[1:0]: clk_prepare_min[9:8]

#define CLK_PREPARE_MIN_LOW_REG_ADDR 0x481F // CLK_PREPARE_MIN 0x3C RW
// Low Byte of the Minimum Value for clk_prepare
// clk_prepare_real = clk_prepare_min_o + Tui * ui_clk_prepare_min_o

#define CLK_POST_MIN_HIGH_REG_ADDR 0x4820 // CLK_POST_MIN 0x00 RW
// High Byte of the Minimum Value for clk_post (Unit ns)
// Bit[1:0]: clk_post_min[9:8]

#define CLK_POST_MIN_LOW_REG_ADDR 0x4821 // CLK_POST_MIN 0x56 RW
// Low Byte of the Minimum Value for clk_post
// clk_post_real = clk_post_min_o + Tui * ui_clk_post_min_o

#define CLK_TRAIL_MIN_HIGH_REG_ADDR 0x4822 // CLK_TRAIL_MIN 0x00 RW
// High Byte of the Minimum Value for clk_trail (Unit ns)
// Bit[1:0]: clk_trail_min[9:8]

#define CLK_TRAIL_MIN_LOW_REG_ADDR 0x4823 // CLK_TRAIL_MIN 0x3C RW
// Low Byte of the Minimum Value for clk_trail
// clk_trail_real = clk_trail_min_o + Tui * ui_clk_trail_min_o

#define WKUP_DLY_REG_ADDR 0x4838 // WKUP_DLY 0x02 RW
// Wakeup delay for MIPI

#define DIR_DLY_REG_ADDR 0x483A // DIR_DLY 0x08 RW
// Change LP direction delay/2 after LP11

#define MIPI_CTRL_33_REG_ADDR 0x483C // MIPI CTRL 33 0x4F RW
// Bit[7:4]: t_lpx, unit: sclk cycles
// Bit[3:0]: t_clk_pre, unit: sclk cycles

#define MIPI_T_TA_GO_REG_ADDR 0x483D // MIPI_T_TA_GO 0x10 RW
// t_ta_go
// Unit: SCLK cycles

#define MIPI_T_TA_SURE_REG_ADDR 0x483E // MIPI_T_TA_SURE 0x06 RW
// t_ta_sure
// Unit: SCLK cycles

#define MIPI_T_TA_GET_REG_ADDR 0x483F // MIPI_T_TA_GET 0x14 RW
// t_ta_get
// Unit: SCLK cycles

#define SNR_PCLK_DIV_REG_ADDR 0x4843 // SNR_PCLK_DIV 0x00 RW
// Bit[0]: PCLK divider
// 0: PCLK/SCLK = 2 and pclk_div = 1
// 1: PCLK/SCLK = 1 and pclk_div = 1

#define MIPI_CTRL_60_REG_ADDR 0x4860 // MIPI CTRL 60 – R
// MIPI Read/Write Only
// Bit[0]: mipi_dis_me
// 0: Enable MIPI read/write registers
// 1: Disable MIPI read/write registers

#define HD_SK_REG0_REG_ADDR 0x4861 // HD_SK_REG0 – R
// MIPI Read/Write, SCCB and MCU Read Only

#define HD_SK_REG1_REG_ADDR 0x4862 // HD_SK_REG1 – R
// MIPI Read/Write, SCCB and MCU Read Only

#define HD_SK_REG2_REG_ADDR 0x4863 // HD_SK_REG2 – R
// MIPI Read/Write, SCCB and MCU Read Only

#define HD_SK_REG3_REG_ADDR 0x4864 // HD_SK_REG3 – R
// MIPI Read/Write, SCCB and MCU Read Only

#define MIPI_ST_REG_ADDR 0x4865 // MIPI_ST – R
// Bit[5]: lp_rx_sel_i
// 1: MIPI_LP_RX receives LP data
// Bit[4]: tx_busy_i
// 1: MIPI_TX_LP_TX is busy to send LP data
// Bit[3]: mipi_lp_p1_i
// MIPI low power input for lane 1p
// Bit[2]: mipi_lp_n1_i
// MIPI low power input for lane 1n
// Bit[1]: mipi_lp_p2_i
// MIPI low power input for lane 2p
// Bit[0]: mipi_lp_n2_i
// MIPI low power input for lane 2n

#define T_GLB_TIM_H_REG_ADDR 0x4866 // T_GLB_TIM_H – R
// Bit[7]: VHREF ahead of flag, must delay VHREF
// Bit[6:0]: vhref_delay_h

#define T_GLB_TIM_L_REG_ADDR 0x4867 // T_GLB_TIM_L – R
// vhref_delay

//AEC registers ----------------------------------------------------------------
#define AEC_CTRL00_REG_ADDR 0x3A00 // AEC CTRL00 0x78 RW
// Bit[7]: Not used
// Bit[6]: Less one line mode
// Bit[5]: Band function
// Bit[4]: Band low limit mode
// Bit[3]: start_sel
// Bit[2]: Night mode
// Bit[1]: Not used
// Bit[0]: Freeze

#define MIN_EXPO_REG_ADDR 0x3A01 // MIN EXPO 0x01 RW
// Bit[7:0]: min expo

#define MAX_EXPO_HIGH_REG_ADDR 0x3A02 // MAX EXPO 60 0x3D RW
// Bit[7:0]: max expo[15:8]

#define MAX_EXPO_LOW_REG_ADDR 0x3A03 // MAX EXPO 60 0x80 RW
// Bit[7:0]: max expo[7:0]

#define AEC_CTRL05_REG_ADDR 0x3A05 // AEC CTRL05 0x30 RW
// Bit[7]: f50_reverse
// 0: Hold 50, 60Hz detect input
// 1: Switch 50, 60Hz detect input
// Bit[6]: frame_insert
// 0: In night mode, insert frame disable
// 1: In night mode, insert frame enable
// Bit[5]: step_auto_en
// 0: Step manual mode
// 1: Step auto_mode
// Bit[4:0]: step_auto_ratio
// In step auto mode, set the step ratio setting to adjust speed

#define AEC_CTRL06_REG_ADDR 0x3A06 // AEC CTRL06 0x10 RW
// Bit[7:5]: Not used
// Bit[4:0]: step_man1
// Step manual
// Increase mode fast step

#define AEC_CTRL07_REG_ADDR 0x3A07 // AEC CTRL07 0x18 RW
// Bit[7:4]: step_man2
// Step manual, slow step
// Bit[3:0]: step_man3
// Step manual, decrease mode fast step

#define B50_STEP_HIGH_REG_ADDR 0x3A08 // B50 STEP 0x01 RW
// Bit[7:2]: Not used
// Bit[1:0]: b50_step[9:8]

#define B50_STEP_LOW_REG_ADDR 0x3A09 // B50 STEP 0x27 RW
// Bit[7:0]: b50_step[7:0]

#define B60_STEP_HIGH_REG_ADDR 0x3A0A // B60 STEP 0x00 RW
// Bit[7:2]: Not used
// Bit[1:0]: b60_step[9:8]

#define B60_STEP_LOW_REG_ADDR 0x3A0B // B60 STEP 0xF6 RW
// Bit[7:0]: b60_step[7:0]

#define AEC_CTRL0C_REG_ADDR 0x3A0C // AEC CTRL0C 0xE4 RW
// Bit[7:4]: e1_max
// Decimal line high limit zone
// Bit[3:0]: e1_min
// Decimal line low limit zone

#define B60_MAX_REG_ADDR 0x3A0D // B60 MAX 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: b60_max

#define B50_MAX_REG_ADDR 0x3A0E // B50 MAX 0x06 RW
// Bit[7:6]: Not used
// Bit[5:0]: b50_max

#define MANUAL_AVG_REG_ADDR 0x3A12 // MANUAL AVG 0x00 RW
// Bit[7:0]: avg_man

#define PRE_GAIN_REG_ADDR 0x3A13 // PRE GAIN 0x40 RW
// Bit[7]: Not used
// Bit[6]: pre-gain enable
// Bit[5:0]: pre-gain value

#define MAX_EXPO_50_HIGH_REG_ADDR 0x3A14 // MAX EXPO 50 0x0E RW
// Bit[7:0]: Maximum expo[15:8]

#define MAX_EXPO_50_LOW_REG_ADDR 0x3A15 // MAX EXPO 50 0x40 RW
// Bit[7:0]: Maximum expo[7:0]

#define NIGHT_MODE_GAIN_BASE_REG_ADDR 0x3A17 // NIGHT MODE GAIN BASE 0x01 RW
// Bit[7:2]: Not used
// Bit[1:0]: gnight_thre
// 00: 0x00
// 01: 0x10
// 10: 0x30
// 11: 0x70

#define AEC_GAIN_CEILING_HIGH_REG_ADDR 0x3A18 // AEC GAIN CEILING 0x00 RW
// Bit[7:2]: Not used
// Bit[1:0]: gain_ceiling[9:8]

#define AEC_GAIN_CEILING_LOW_REG_ADDR 0x3A19 // AEC GAIN CEILING 0x7C RW
// Bit[7:0]: gain_ceiling[7:0]

#define DIFF_MAX_REG_ADDR 0x3A1A // DIFF MAX 0x04 RW
// Bit[7:0]: diff_max

#define LED_ADD_ROW_HIGH_REG_ADDR 0x3A1C // LED ADD ROW 0x06 RW
// Bit[7:0]: led_add_row[15:8]
// Exposure values added when STROBE is ON

#define LED_ADD_ROW_LOW_REG_ADDR 0x3A1D // LED ADD ROW 0x18 RW
// Bit[7:0]: led_add_row[7:0]
// Exposure values added when STROBE is ON

#define AEC_CTRL20_REG_ADDR 0x3A20 // AEC CTRL20 0x00 RW
// Bit[7:2]: Not used
// Bit[1]: man_avg_en_i
// 0: Disable
// 1: Enable
// Bit[0]: Not used

#define AEC_CTRL21_REG_ADDR 0x3A21 // AEC CTRL21 0x70 RW
// Bit[7:]: Not used
// Bit[6:4]: Frame insert number
// Bit[3:0]: Not used

#define FRAME_CTRL0_REG_ADDR 0x4900 // FRAME CTRL0 0x00 RW
// Bit[7:3]: Not used
// Bit[2]: fcnt_eof_sel
// Bit[1]: fcnt_mask_dis
// Bit[0]: fcnt_reset

#define FRAME_ON_NUMBER_REG_ADDR 0x4901 // FRAME ON NUMBER 0x00 RW
// Bit[7:3]: Not used
// Bit[3:0]: Frame ON number

#define FRAME_OFF_NUMBER_REG_ADDR 0x4902 // FRAME OFF NUMBER 0x00 RW
// Bit[7:3]: Not used
// Bit[3:0]: Frame OFF number

#define FRAME_CTRL1_REG_ADDR 0x4903 // FRAME CTRL1 0x00 RW
// Bit[7:6]: Not used
// Bit[5]: data_mask_dis
// Bit[4]: valid_mask_dis
// Bit[3]: href_mask_dis
// Bit[2]: eof_mask_dis
// Bit[1]: sof_mask_dis
// Bit[0]: all_mask_dis

#define ISP_CTRL06_REG_ADDR 0x5006 // ISP CTRL06 0x00 RW
// ISP Control (0: disable ISP; 1: enable ISP)
// Bit[7]: x_odd_inc_man_en
// Bit[6]: y_even_inc_man_en
// Bit[5]: x_odd_inc_man_en
// Bit[4]: y_even_inc_man_en
// Bit[3]: x_offset_man_en
// Bit[2]: y_offset_man_en
// Bit[1]: x_skip_man_en
// Bit[0]: y_skip_man_en

#define ISP_CTRL07_REG_ADDR 0x5007 // ISP CTRL07 0x00 RW
// ISP Control (0: disable ISP; 1: enable ISP)
// Bit[7]: bin_mode_man_en
// Bit[6]: bin_mode_man
// Bit[5]: win_x_off_man_en
// Bit[4]: win_y_off_man_en
// Bit[3]: win_x_out_man_en
// Bit[2]: win_y_out_man_en
// Bit[1]: isp_input_h_man_en
// Bit[0]: isp_input_v_man_en

#define X_OFFSET_MAN_MSB_REG_ADDR 0x5008 // X OFFSET MAN 0x00 RW
// Bit[7:4]: Not used
// Bit[3:0]: x_offset_man[11:8]

#define X_OFFSET_MAN_LSB_REG_ADDR 0x5009 // X OFFSET MAN 0x00 RW
// Bit[7:0]: x_offset_man[7:0]

#define Y_OFFSET_MAN_MSB_REG_ADDR 0x500A // Y OFFSET MAN 0x00 RW
// Bit[7:3]: Not used
// Bit[2:0]: y_offset_man[10:8]

#define Y_OFFSET_MAN_LSB_REG_ADDR 0x500B // Y OFFSET MAN 0x00 RW
// Bit[7:0]: y_offset_man[7:0]

#define WIN_X_OFFSET_MAN_MSB_REG_ADDR 0x500C // WIN X OFFSET MAN 0x00 RW
// Bit[7:4]: Not used
// Bit[3:0]: win_x_offset_man[11:8]

#define WIN_X_OFFSET_MAN_LSB_REG_ADDR 0x500D // WIN X OFFSET MAN 0x00 RW
// Bit[7:0]: win_x_offset_man[7:0]

#define WIN_Y_OFFSET_MAN_MSB_REG_ADDR 0x500E // WIN Y OFFSET MAN 0x00 RW
// Bit[7:3]: Not used
// Bit[2:0]: win_y_offset_man[10:8]

#define WIN_Y_OFFSET_MAN_LSB_REG_ADDR 0x500F // WIN Y OFFSET MAN 0x00 RW
// Bit[7:0]: win_y_offset_man[7:0]

#define WIN_X_OUT_MAN_MSB_REG_ADDR 0x5010 // WIN X OUT MAN 0x00 RW
// Bit[7:4]: Not used
// Bit[3:0]: win_x_out_man[11:8]

#define WIN_X_OUT_MAN_LSB_REG_ADDR 0x5011 // WIN X OUT MAN 0x00 RW
// Bit[7:0]: win_x_out_man[7:0]

#define WIN_Y_OUT_MAN_MSB_REG_ADDR 0x5012 // WIN Y OUT MAN 0x00 RW
// Bit[7:3]: Not used
// Bit[2:0]: win_y_out_man[10:8]

#define WIN_Y_OUT_MAN_LSB_REG_ADDR 0x5013 // WIN Y OUT MAN 0x00 RW
// Bit[7:0]: win_y_out_man[7:0]

#define ISP_INPUT_X_MAN_MSB_REG_ADDR 0x5014 // ISP INPUT X MAN 0x00 RW
// Bit[7:4]: Not used
// Bit[3:0]: isp_x_input_man[11:8]

#define ISP_INPUT_X_MAN_LSB_REG_ADDR 0x5015 // ISP INPUT X MAN 0x00 RW
// Bit[7:0]: isp_x_input_man[7:0]

#define ISP_INPUT_Y_MAN_MSB_REG_ADDR 0x5016 // ISP INPUT Y MAN 0x00 RW
// Bit[7:3]: Not used
// Bit[2:0]: isp_y_input_man[10:8]

#define ISP_INPUT_Y_MAN_LSB_REG_ADDR 0x5017 // ISP INPUT Y MAN 0x00 RW
// Bit[7:0]: isp_y_input_man[7:0]

#define ISP_CTRL18_REG_ADDR 0x5018 // ISP CTRL18 0x00 RW
// Bit[7:4]: x_odd_inc_man
// Bit[3:0]: x_even_inc_man

#define ISP_CTRL19_REG_ADDR 0x5019 // ISP CTRL19 0x00 RW
// Bit[7:4]: y_odd_inc_man
// Bit[3:0]: y_even_inc_man

#define ISP_CTRL1A_REG_ADDR 0x501A // ISP CTRL1A 0x00 RW
// Bit[7:4]: Not used
// Bit[3:2]: x_skip_man
// Bit[1:0]: y_skip_man

#define ISP_CTRL1D_REG_ADDR 0x501D // ISP CTRL1D 0x00 RW
// Bit[7]: Not used
// Bit[6:4]: win_y_offset_adjust
// Bit[3:0]: Not used

#define ISP_CTRL4C_REG_ADDR 0x504C // ISP CTRL4C 0x04 RW
// Bit[7:0]: bias_man

#define ISP_CTRL4D_REG_ADDR 0x504D // ISP CTRL4D 0x00 RW
// Bit[7:4]: Not used
// Bit[3]: lenc_xoff_man_en
// Bit[2]: lenc_yoff_man_en
// Bit[1]: lenc_gain_man_en
// Bit[0]: lenc_bias_man_en

#define ISP_CTRL4E_REG_ADDR 0x504E // ISP CTRL4E 0x04 RW
// Bit[7:4]: Not used
// Bit[3:0]: lenc_xoff_man[11:8]

#define ISP_CTRL4F_REG_ADDR 0x504F // ISP CTRL4F 0x00 RW
// Bit[7:0]: lenc_xoff_man[7:0]

#define ISP_CTRL52_REG_ADDR 0x5052 // ISP CTRL52 0x0A RW
// Bit[7:4]: Not used
// Bit[3:0]: lenc_yoff_man[11:8]

#define ISP_CTRL53_REG_ADDR 0x5053 // ISP CTRL53 0x00 RW
// Bit[7:0]: lenc_yoff_man[7:0]

#define ISP_CTRL54_REG_ADDR 0x5054 // ISP CTRL54 0x00 RW
// Bit[7:2]: Not used
// Bit[1:0]: lenc_gain_man[9:8]

#define ISP_CTRL55_REG_ADDR 0x5055 // ISP CTRL55 0x00 RW
// Bit[7:0]: lenc_gain_man[7:0]

#define ISP_CTRL56_REG_ADDR 0x5056 // ISP CTRL56 0x00 RW
// Bit[7:6]: Not used
// Bit[5]: lenc_skipx_man
// Bit[4]: lenc_skipy_man
// Bit[3:2]: lenc_skipy_man
// Bit[1:0]: lenc_skipx_man

#define ISP_CTRL57_REG_ADDR 0x5057 // ISP CTRL57 0x00 RW
// Bit[7]: sram_test_dpc1
// Bit[6]: sram_test_dpc2
// Bit[5]: sram_test_dpc3
// Bit[4]: sram_test_dpc4
// Bit[3:0]: Not used

#define ISP_CTRL58_REG_ADDR 0x5058 // ISP CTRL58 0xAA RW
// Bit[7:4]: sram_rm_dpc1
// Bit[3:0]: sram_rm_dpc2

#define ISP_CTRL59_REG_ADDR 0x5059 // ISP CTRL59 0xAA RW
// Bit[7:4]: sram_rm_dpc3
// Bit[3:0]: sram_rm_dpc4

#define GMTRX00_REG_ADDR 0x5800 // GMTRX00 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_00

#define GMTRX01_REG_ADDR 0x5801 // GMTRX01 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_01

#define GMTRX02_REG_ADDR 0x5802 // GMTRX02 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_02

#define GMTRX03_REG_ADDR 0x5803 // GMTRX03 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_03

#define GMTRX04_REG_ADDR 0x5804 // GMTRX04 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_04

#define GMTRX05_REG_ADDR 0x5805 // GMTRX05 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_05

#define GMTRX10_REG_ADDR 0x5806 // GMTRX10 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_06

#define GMTRX11_REG_ADDR 0x5807 // GMTRX11 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_07

#define GMTRX12_REG_ADDR 0x5808 // GMTRX12 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_08

#define GMTRX13_REG_ADDR 0x5809 // GMTRX13 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_09

#define GMTRX14_REG_ADDR 0x580A // GMTRX14 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0a

#define GMTRX15_REG_ADDR 0x580B // GMTRX15 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0b

#define GMTRX20_REG_ADDR 0x580C // GMTRX20 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0c

#define GMTRX21_REG_ADDR 0x580D // GMTRX21 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0d

#define GMTRX22_REG_ADDR 0x580E // GMTRX22 0x00 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0e

#define GMTRX23_REG_ADDR 0x580F // GMTRX23 0x00 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_0f

#define GMTRX24_REG_ADDR 0x5810 // GMTRX24 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_10

#define GMTRX25_REG_ADDR 0x5811 // GMTRX25 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_11

#define GMTRX30_REG_ADDR 0x5812 // GMTRX30 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_12

#define GMTRX31_REG_ADDR 0x5813 // GMTRX31 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_13

#define GMTRX32_REG_ADDR 0x5814 // GMTRX32 0x00 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_14

#define GMTRX33_REG_ADDR 0x5815 // GMTRX33 0x00 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_15

#define GMTRX34_REG_ADDR 0x5816 // GMTRX34 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_16

#define GMTRX35_REG_ADDR 0x5817 // GMTRX35 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_17

#define GMTRX40_REG_ADDR 0x5818 // GMTRX40 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_18

#define GMTRX41_REG_ADDR 0x5819 // GMTRX41 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_19

#define GMTRX42_REG_ADDR 0x581A // GMTRX42 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_1a

#define GMTRX43_REG_ADDR 0x581B // GMTRX43 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_1b

#define GMTRX44_REG_ADDR 0x581C // GMTRX44 0x08 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_1c

#define GMTRX45_REG_ADDR 0x581D // GMTRX45 0x10 RW
// Bit[7:6]: Not used
// Bit[5:0]: green_matrix_1d

#define BRMATRX00_REG_ADDR 0x5824 // BRMATRX00 0xAA RW
// Bit[7:4]: blue_matrix_00
// Bit[3:0]: red_matrix_00

#define BRMATRX01_REG_ADDR 0x5825 // BRMATRX01 0xAA RW
// Bit[7:4]: blue_matrix_01
// Bit[3:0]: red_matrix_01

#define BRMATRX02_REG_ADDR 0x5826 // BRMATRX02 0xAA RW
// Bit[7:4]: blue_matrix_02
// Bit[3:0]: red_matrix_02

#define BRMATRX03_REG_ADDR 0x5827 // BRMATRX03 0xAA RW
// Bit[7:4]: blue_matrix_03
// Bit[3:0]: red_matrix_03

#define BRMATRX04_REG_ADDR 0x5828 // BRMATRX04 0xAA RW
// Bit[7:4]: blue_matrix_04
// Bit[3:0]: red_matrix_04

#define BRMATRX05_REG_ADDR 0x5829 // BRMATRX05 0xAA RW
// Bit[7:4]: blue_matrix_05
// Bit[3:0]: red_matrix_05

#define BRMATRX06_REG_ADDR 0x582A // BRMATRX06 0x99 RW
// Bit[7:4]: blue_matrix_06
// Bit[3:0]: red_matrix_06

#define BRMATRX07_REG_ADDR 0x582B // BRMATRX07 0x99 RW
// Bit[7:4]: blue_matrix_07
// Bit[3:0]: red_matrix_07

#define BRMATRX08_REG_ADDR 0x582C // BRMATRX08 0x99 RW
// Bit[7:4]: blue_matrix_08
// Bit[3:0]: red_matrix_08

#define BRMATRX09_REG_ADDR 0x582D // BRMATRX09 0xAA RW
// Bit[7:4]: blue_matrix_09
// Bit[3:0]: red_matrix_09

#define BRMATRX20_REG_ADDR 0x582E // BRMATRX20 0xAA RW
// Bit[7:4]: blue_matrix_20
// Bit[3:0]: red_matrix_20

#define BRMATRX21_REG_ADDR 0x582F // BRMATRX21 0x99 RW
// Bit[7:4]: blue_matrix_21
// Bit[3:0]: red_matrix_21

#define BRMATRX22_REG_ADDR 0x5830 // BRMATRX22 0x88 RW
// Bit[7:4]: blue_matrix_22
// Bit[3:0]: red_matrix_22

#define BRMATRX23_REG_ADDR 0x5831 // BRMATRX23 0x99 RW
// Bit[7:4]: blue_matrix_23
// Bit[3:0]: red_matrix_23

#define BRMATRX24_REG_ADDR 0x5832 // BRMATRX24 0xAA RW
// Bit[7:4]: blue_matrix_24
// Bit[3:0]: red_matrix_24

#define BRMATRX30_REG_ADDR 0x5833 // BRMATRX30 0xAA RW
// Bit[7:4]: blue_matrix_30
// Bit[3:0]: red_matrix_30

#define BRMATRX31_REG_ADDR 0x5834 // BRMATRX31 0x99 RW
// Bit[7:4]: blue_matrix_31
// Bit[3:0]: red_matrix_31

#define BRMATRX32_REG_ADDR 0x5835 // BRMATRX32 0x99 RW
// Bit[7:4]: blue_matrix_32
// Bit[3:0]: red_matrix_32

#define BRMATRX33_REG_ADDR 0x5836 // BRMATRX33 0x99 RW
// Bit[7:4]: blue_matrix_33
// Bit[3:0]: red_matrix_33

#define BRMATRX34_REG_ADDR 0x5837 // BRMATRX34 0xAA RW
// Bit[7:4]: blue_matrix_34
// Bit[3:0]: red_matrix_34

#define BRMATRX40_REG_ADDR 0x5838 // BRMATRX40 0xAA RW
// Bit[7:4]: blue_matrix_40
// Bit[3:0]: red_matrix_40

#define BRMATRX41_REG_ADDR 0x5839 // BRMATRX41 0xAA RW
// Bit[7:4]: blue_matrix_41
// Bit[3:0]: red_matrix_41

#define BRMATRX42_REG_ADDR 0x583A // BRMATRX42 0xAA RW
// Bit[7:4]: blue_matrix_42
// Bit[3:0]: red_matrix_42

#define BRMATRX43_REG_ADDR 0x583B // BRMATRX43 0xAA RW
// Bit[7:4]: blue_matrix_43
// Bit[3:0]: red_matrix_43

#define BRMATRX44_REG_ADDR 0x583C // BRMATRX44 0xAA RW
// Bit[7:4]: blue_matrix_44
// Bit[3:0]: red_matrix_44

#define OTP_CTRL07_REG_ADDR 0x5907 // OTP CTRL07 0x38 RW
// Bit[7]: Not used
// Bit[6:4]: remain_bit
// Bit[3:0]: Threshold

#define OTP_MAN_X_EVEN_INC_REG_ADDR 0x5908 // OTP MAN X EVEN INC 0x01 RW
// Bit[7:4]: Not used
// Bit[3:0]: otp_man_x_even_inc

#define OTP_MAN_X_ODD_INC_REG_ADDR 0x5909 // OTP MAN X ODD INC 0x01 RW
// Bit[7:4]: Not used
// Bit[3:0]: otp_man_x_odd_inc

#define OTP_MAN_Y_EVEN_INC_REG_ADDR 0x590A // OTP MAN Y EVEN INC 0x01 RW
// Bit[7:4]: Not used
// Bit[3:0]: otp_man_y_even_inc

#define OTP_MAN_Y_ODD_INC_REG_ADDR 0x590B // OTP MAN Y ODD INC 0x01 RW
// Bit[7:4]: Not used
// Bit[3:0]: otp_man_y_odd_inc

#define WINDOW_XSTART_MSB_REG_ADDR 0x5980 // WINDOW XSTART 0x00 RW
// Bit[7:5]: Not used
// Bit[4:0]: window_xstart[12:8]

#define WINDOW_XSTART_LSB_REG_ADDR 0x5981 // WINDOW XSTART 0x00 RW
// Bit[7:0]: window_xstart[7:0]

#define WINDOW_YSTART_MSB_REG_ADDR 0x5982 // WINDOW YSTART 0x00 RW
// Bit[7:4]: Not used
// Bit[3:0]: window_ystart[11:8]

#define WINDOW_YSTART_LSB_REG_ADDR 0x5983 // WINDOW YSTART 0x00 RW
// Bit[7:0]: window_ystart[7:0]

#define WIN_X_WIN_MSB_REG_ADDR 0x5984 // WIN X WIN 0x10 RW
// Bit[7:5]: Not used
// Bit[4:0]: window_x_win[12:8]

#define WIN_X_WIN_LSB_REG_ADDR 0x5985 // WIN X WIN 0xA0 RW
// Bit[7:0]: window_x_win[7:0]

#define WIN_Y_WIN_MSB_REG_ADDR 0x5986 // WIN Y WIN 0x0C RW
// Bit[7:4]: Not used
// Bit[3:0]: window_y_win[11:8]

#define WIN_Y_WIN_LSB_REG_ADDR 0x5987 // WIN Y WIN 0x78 RW
// Bit[7:0]: window_y_win[7:0]

#define WIN_MAN_REG_ADDR 0x5988 // WIN MAN 0x00 RW
// Bit[7:1]: Not used
// Bit[0]: Window manual enable
// 0: Auto mode
// 1: Manual mode

#define DIGC_CTRL0_REG_ADDR 0x5A00 // DIGC CTRL0 0x00 RW
// Bit[7:3]: Not used
// Bit[2]: dig_comp_bypass
// Bit[1]: man_opt
// Bit[0]: man_en

#define DIG_COMP_MAN_MSB_REG_ADDR 0x5A02 // DIG COMP MAN 0x02 RW
// Bit[7:2]: Not used
// Bit[1:0]: dig_comp_man[9:8]

#define DIG_COMP_MAN_LSB_REG_ADDR 0x5A03 // DIG COMP MAN 0x00 RW
// Bit[7:0]: dig_comp_man[7:0]

#define SNR_GAIN_MAN_MSB_REG_ADDR 0x5A20 // SNR GAIN MAN 0x00 RW
// Bit[7:1]: Not used
// Bit[0]: gainc_sg_man[8]

#define SNR_GAIN_MAN_LSB_REG_ADDR 0x5A21 // SNR GAIN MAN 0x00 RW
// Bit[7:0]: gainc_sg_man[7:0]

#define DIG_GAIN_MAN_MSB_REG_ADDR 0x5A22 // DIG GAIN MAN 0x00 RW
// Bit[7:2]: Not used
// Bit[1:0]: gainc_dg_man[9:8]

#define DIG_GAIN_MAN_LSB_REG_ADDR 0x5A23 // DIG GAIN MAN 0x00 RW
// Bit[7:0]: gainc_dg_man[7:0]

#define GAINC_CTRL0_REG_ADDR 0x5A24 // GAINC CTRL0 0x00 RW
// Bit[7:3]: Not used
// Bit[2]: OPT
// Bit[1]: bypass_opt
// Bit[0]: gainc_man_en

#define GAINC_DG_RDOUT_MSB_REG_ADDR 0x5A25 // GAINC DG RDOUT – R
// Bit[7:2]: Not used
// Bit[1:0]: gainc_dig_comp[9:8]

#define GAINC_DG_RDOUT_LSB_REG_ADDR 0x5A26 // GAINC DG RDOUT – R
// Bit[7:0]: gainc_dig_comp[7:0]

#define GAINC_SG_RDOUT_MSB_REG_ADDR 0x5A27 // GAINC SG RDOUT – R
// Bit[7:1]: Not used
// Bit[0]: gainc_snr[8]

#define GAINC_SG_RDOUT_LSB_REG_ADDR 0x5A28 // GAINC SG RDOUT – R
// Bit[7:0]: gainc_snr[7:0]

#define GAINC_REALGAIN_MSB_REG_ADDR 0x5A29 // GAINC SG RDOUT – R
// Bit[7:2]: Not used
// Bit[1:0]: gainc_realgain[9:8]

#define GAINC_REALGAIN_LSB_REG_ADDR 0x5A2A // GAINC SG RDOUT – R
// Bit[7:0]: gainc_realgain[7:0]

#define GAINF_ANA_NUM_REG_ADDR 0x5A40 // GAINF ANA NUM 0x07 RW
// Bit[7:0]: gainf_ana_bit_num

#define GAINF_DIG_GAIN_REG_ADDR 0x5A41 // GAINF DIG GAIN 0x00 RW
// Bit[7:0]: gainf_dig_gain

#define LPX_P_MIN_MSB_REG_ADDR 0x4824 // LPX_P_MIN 0x00 RW
// High byte of the minimum value for lpx_p, unit ns
// Bit[1:0]: lpx_p_min[9:8]

#define LPX_P_MIN_LSB_REG_ADDR 0x4825 // LPX_P_MIN 0x32 RW
// Low byte of the minimum value for lpx_p
// lpx_p_real = lpx_p_min_o + Tui*ui_lpx_p_min_o

#define HS_PREPARE_MIN_MSB_REG_ADDR 0x4826 // HS_PREPARE_MIN 0x00 RW
// High byte of the minimum value for hs_prepare, unit ns
// Bit[1:0]: hs_prepare_min[9:8]

#define HS_PREPARE_MIN_LSB_REG_ADDR 0x4827 // HS_PREPARE_MIN 0x32 RW
// Low byte of the minimum value for hs_prepare
// hs_prepare_real = hs_prepare_min_o + Tui*ui_hs_prepare_min_o

#define HS_EXIT_MIN_MSB_REG_ADDR 0x4828 // HS_EXIT_MIN 0x00 RW
// High byte of the minimum value for hs_exit, unit ns
// Bit[1:0]: hs_exit_min[9:8]

#define HS_EXIT_MIN_LSB_REG_ADDR 0x4829 // HS_EXIT_MIN 0x64 RW
// Low byte of the minimum value for hs_exit
// hs_exit_real = hs_exit_min_o + Tui*ui_hs_exit_min_o

#define UI_HS_ZERO_MIN_REG_ADDR 0x482A // UI_HS_ZERO_MIN 0x05 RW
// Minimum UI Value of hs_zero, unit UI

#define UI_HS_TRAIL_MIN_REG_ADDR 0x482B // UI_HS_TRAIL_MIN 0x04 RW
// Minimum UI Value of hs_trail, unit UI

#define UI_CLK_ZERO_MIN_REG_ADDR 0x482C // UI_CLK_ZERO_MIN 0x00 RW
// Minimum UI Value of clk_zero, unit UI

#define UI_CLK_PREPARE_MIN_REG_ADDR 0x482D // UI_CLK_PREPARE_MIN 0x00 RW
// Minimum UI Value of clk_prepare, unit UI

#define UI_CLK_POST_MIN_REG_ADDR 0x482E // UI_CLK_POST_MIN 0x34 RW
// Minimum UI Value of clk_post, unit UI

#define UI_CLK_TRAIL_MIN_REG_ADDR 0x482F // UI_CLK_TRAIL_MIN 0x00 RW
// Minimum UI Value of clk_trail, unit UI

#define UI_LPX_P_MIN_REG_ADDR 0x4830 // UI_LPX_P_MIN 0x00 RW
// Minimum UI Value of lpx_p, unit UI

#define UI_HS_PREPARE_MIN_REG_ADDR 0x4831 // UI_HS_PREPARE_MIN 0x04 RW
// Minimum UI Value of hs_prepare, unit UI

#define UI_HS_EXIT_MIN_REG_ADDR 0x4832 // UI_HS_EXIT_MIN 0x00 RW
// Minimum UI Value of hs_exit, unit UI

#define MIPI_REG_MIN_MSB_REG_ADDR 0x4833 // MIPI_REG_MIN 0x00 RW
// MIPI register address, lower bound (high byte)
// Address range of MIPI RW registers is from mipi_reg_min to mipi_reg_max

#define MIPI_REG_MIN_LSB_REG_ADDR 0x4834 // MIPI_REG_MIN 0x00 RW
// MIPI register address, lower bound (low byte)

#define MIPI_REG_MAX_MSB_REG_ADDR 0x4835 // MIPI_REG_MAX 0xFF RW
// MIPI register address, upper bound (high byte)

#define MIPI_REG_MAX_LSB_REG_ADDR 0x4836 // MIPI_REG_MAX 0xFF RW
// MIPI register address, upper bound (low byte)

#define PCLK_PERIOD_REG_ADDR 0x4837 // PCLK_PERIOD 0x15 RW
// Period of pclk2x, pclk_div = 1, and 1-bit decimal

#define BLC_CTRL00_REG_ADDR 0x4000 // BLC CTRL00 0x89 RW
// BLC Control
// (0: disable ISP; 1: enable ISP)
// Bit[7]: blc_median_filter_enable
// Bit[6:4]: Not used
// Bit[3]: adc_11bit_mode
// Bit[2]: apply2blackline
// Bit[1]: blackline_averageframe
// Bit[0]: BLC enable

#define BLC_CTRL01_REG_ADDR 0x4001 // BLC CTRL01 0x00 RW
// Bit[7:6]: Not used
// Bit[5:0]: start_line

#define BLC_CTRL02_REG_ADDR 0x4002 // BLC CTRL02 0x45 RW
// Bit[7]: format_change_en
// format_change_i from fmt will be
// effect when it is enable
// Bit[6]: blc_auto_en
// Bit[5:0]: reset_frame_num

#define BLC_CTRL03_REG_ADDR 0x4003 // BLC CTRL03 0x08 RW
// Bit[7]: blc_redo_en
// Write 1 into it will trigger a BLC
// redo N frames begin
// Bit[6]: Freeze
// Bit[5:0]: manual_frame_num

#define BLC_CTRL04_REG_ADDR 0x4004 // BLC CTRL04 0x08 RW
// Bit[7:0]: blc_line_num

#define BLC_CTRL05_REG_ADDR 0x4005 // BLC CTRL05 0x18 RW
// Bit[7:6]: Not used
// Bit[5]: one_line_mode
// Bit[4]: remove_none_imagedata
// Bit[3]: blc_man_1_en
// Bit[2]: blackline_bggr_man_en
// 0: bgbg/grgr is decided by
// rblue/hswap
// 1: bgbg/grgr fix
// Bit[1]: bgbg/grgr is decided by
// rblue/hswap
// blc_always_up_en
// 0: Normal freeze
// 1: BLC always update
// Bit[0]: Not used

#define BLC_CTRL06_REG_ADDR 0x4006 // BLC CTRL06 0x08 RW
// Bit[7:6]: Not used
// Bit[5]: bl_num_man_en
// Bit[4:0]: bl_num_man

#define DEBUG_MODE_REG_301A_ADDR 0x301A // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_301B_ADDR 0x301B // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_301C_ADDR 0x301C // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_301D_ADDR 0x301D // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_301E_ADDR 0x301E // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_301F_ADDR 0x301F // DEBUG MODE – – Debug Mode
#define DEBUG_MODE_REG_3020_ADDR 0x3020 // DEBUG MODE – – Debug Mode

#define DEBUG_MODE_TIMING_REG_3822_ADDR 0x3822 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3823_ADDR 0x3823 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3824_ADDR 0x3824 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3825_ADDR 0x3825 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3826_ADDR 0x3826 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3827_ADDR 0x3827 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3828_ADDR 0x3828 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3829_ADDR 0x3829 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382A_ADDR 0x382A // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382B_ADDR 0x382B // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382C_ADDR 0x382C // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382D_ADDR 0x382D // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382E_ADDR 0x382E // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_382F_ADDR 0x382F // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3830_ADDR 0x3830 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3831_ADDR 0x3831 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3832_ADDR 0x3832 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3833_ADDR 0x3833 // DEBUG MODE_TIMING – – Debug Mode
#define DEBUG_MODE_TIMING_REG_3834_ADDR 0x3834 // DEBUG MODE_TIMING – – Debug Mode