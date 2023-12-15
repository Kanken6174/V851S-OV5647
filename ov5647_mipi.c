#include "ov5647_mipi.h"
#define MHZ 1000000
//-------------------------------------------------------------------------------------
/*
 * Code for dealing with controls.
 * fill with different sensor module
 * different sensor module has different settings here
 * if not support the follow function ,retrun -EINVAL
 */

static int sensor_g_exp(struct v4l2_subdev *sd, __s32 *value)
{
	struct sensor_info *info = to_state(sd);

	*value = info->exp;
	sensor_dbg("sensor_get_exposure = %d\n", info->exp);
	return 0;
}

static int sensor_s_exp(struct v4l2_subdev *sd, unsigned int exp_val)
{
	/*unsigned char explow, expmid, exphigh;
	struct sensor_info *info = to_state(sd);

	if (exp_val > 0xfffff)
		exp_val = 0xfffff;
	if (exp_val < 7)
		exp_val = 7;

	exphigh = (unsigned char)((0x0f0000 & exp_val) >> 16);
	expmid = (unsigned char)((0x00ff00 & exp_val) >> 8);
	explow = (unsigned char)(0x0000ff & exp_val);

	sensor_write(sd, 0x3502, explow);
	sensor_write(sd, 0x3501, expmid);
	sensor_write(sd, 0x3500, exphigh);

	info->exp = exp_val;*/
	return 0;
}

static int sensor_g_gain(struct v4l2_subdev *sd, __s32 *value)
{
	struct sensor_info *info = to_state(sd);
	*value = info->gain;
	sensor_dbg("sensor_get_gain = %d\n", info->gain);
	return 0;
}

static int sensor_s_gain(struct v4l2_subdev *sd, unsigned int gain_val)
{
	struct sensor_info *info = to_state(sd);
	unsigned char gainlow = 0;
	unsigned char gainhigh = 0;

	if (gain_val < 1 * 16)
		gain_val = 16;
	if (gain_val > 64 * 16 - 1)
		gain_val = 64 * 16 - 1;

	gainlow = (unsigned char)(gain_val & 0xff);
	gainhigh = (unsigned char)((gain_val >> 8) & 0x3);

	sensor_write(sd, 0x350b, gainlow);
	sensor_write(sd, 0x350a, gainhigh);

	info->gain = gain_val;

	return 0;
}

static int ov5647_sensor_vts;
static int sensor_s_exp_gain(struct v4l2_subdev *sd,
				struct sensor_exp_gain *exp_gain)
{
	/*int exp_val, gain_val, shutter, frame_length;
	unsigned char explow = 0, expmid = 0, exphigh = 0;
	unsigned char gainlow = 0, gainhigh = 0;
	struct sensor_info *info = to_state(sd);

	exp_val = exp_gain->exp_val;
	gain_val = exp_gain->gain_val;
	if (gain_val < 1*16)
		gain_val = 16;
	if (gain_val > 64*16-1)
		gain_val = 64*16-1;

	if (exp_val > 0xfffff)
		exp_val = 0xfffff;

	gainlow = (unsigned char)(gain_val & 0xff);
	gainhigh = (unsigned char)((gain_val >> 8)&0x3);

	exphigh	= (unsigned char)((0x0f0000&exp_val) >> 16);
	expmid	= (unsigned char)((0x00ff00&exp_val) >> 8);
	explow	= (unsigned char)((0x0000ff&exp_val));

	shutter = exp_val/16;
	if (shutter  > ov5647_sensor_vts - 4)
		frame_length = shutter + 4;
	else
		frame_length = ov5647_sensor_vts;

	sensor_write(sd, 0x3208, 0x00);//enter group write
	sensor_write(sd, 0x3503, 0x07);
	sensor_write(sd, 0x380f, (frame_length & 0xff));
	sensor_write(sd, 0x380e, (frame_length >> 8));
	sensor_write(sd, 0x350b, gainlow);
	sensor_write(sd, 0x350a, gainhigh);

	sensor_write(sd, 0x3502, explow);
	sensor_write(sd, 0x3501, expmid);
	sensor_write(sd, 0x3500, exphigh);
	sensor_write(sd, 0x3208, 0x10);//end group write
	sensor_write(sd, 0x3208, 0xa0);//init group write
	info->exp = exp_val;
	info->gain = gain_val;*/
	return 0;
}

static void sensor_s_sw_stby(struct v4l2_subdev *sd, int on_off)
{

}

/*
 * Stuff that knows about the sensor.
 */
static int sensor_power(struct v4l2_subdev *sd, int on)
{
	sensor_print("entering sensor_power\n");
	sensor_dbg("zzz5648 sensor_power\n");

	switch (on) {
	case STBY_ON:
		sensor_print("entering sensor_power STBY_ON\n");
		sensor_print("STBY_ON!\n");
		cci_lock(sd);
		sensor_s_sw_stby(sd, STBY_ON);
		usleep_range(1000, 1200);
		cci_unlock(sd);
		break;
	case STBY_OFF:
		sensor_print("entering sensor_power STBY_OFF\n");
		sensor_print("STBY_OFF!\n");
		cci_lock(sd);
		usleep_range(1000, 1200);
		sensor_s_sw_stby(sd, STBY_OFF);
		cci_unlock(sd);
		break;
	case PWR_ON:
		sensor_print("entering sensor_power PWR_ON, pins: %d %d\n",PWDN ,POWER_EN);
		gpio_direction_output(GPIOA(8), 0);	//led enable
		gpio_direction_output(GPIOA(9), 0);	//power enable
		sensor_print("PWR_ON!100\n");
		cci_lock(sd);
		vin_gpio_set_status(sd, PWDN, 1);
		//vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);	//not needed for the rpi ov5647 modules
		vin_gpio_set_status(sd, POWER_EN, 1);
		vin_gpio_write(sd, PWDN, CSI_GPIO_HIGH);	//special case, since PWDN is the led we power it ON
		//vin_gpio_write(sd, RESET, CSI_GPIO_LOW);	//ignore reset
		vin_gpio_write(sd, POWER_EN, CSI_GPIO_HIGH);
		usleep_range(7000, 8000);
		vin_set_pmu_channel(sd, IOVDD, ON);
		usleep_range(7000, 8000);
		vin_set_pmu_channel(sd, AVDD, ON);
		vin_set_pmu_channel(sd, AFVDD, ON);
		usleep_range(7000, 8000);
		vin_set_pmu_channel(sd, DVDD, ON);
		usleep_range(7000, 8000);
		vin_set_mclk_freq(sd, MCLK);
		vin_set_mclk(sd, OFF);	//MCLK not connected
		usleep_range(10000, 12000);
		//vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);	//these calls are useless as well
		//vin_gpio_write(sd, PWDN, CSI_GPIO_HIGH);
		vin_set_pmu_channel(sd, CAMERAVDD, ON);/*AFVCC ON*/
		usleep_range(10000, 12000);
		cci_unlock(sd);
		break;
	case PWR_OFF:
		sensor_print("PWR_OFF!\n");
		cci_lock(sd);
		vin_gpio_write(sd, PWDN, CSI_GPIO_LOW);	//LED off
		//vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);
		vin_set_mclk(sd, OFF);
		usleep_range(7000, 8000);
		vin_set_pmu_channel(sd, DVDD, OFF);
		//vin_gpio_write(sd, PWDN, CSI_GPIO_LOW);
		//vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
		vin_gpio_write(sd, POWER_EN, CSI_GPIO_LOW);	//turn off power to the camera
		vin_set_pmu_channel(sd, AVDD, OFF);
		vin_set_pmu_channel(sd, IOVDD, OFF);
		vin_set_pmu_channel(sd, AFVDD, OFF);
		vin_set_pmu_channel(sd, CAMERAVDD, OFF);/*AFVCC ON*/
		cci_unlock(sd);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int sensor_reset(struct v4l2_subdev *sd, u32 val)
{
	printk(KERN_WARNING "entering sensor_reset\n");	//this camera modules doesn't need to reset
	/*
	switch (val) {
	case 0:
		vin_gpio_write(sd, RESET, CSI_GPIO_HIGH);
		usleep_range(100, 120);
		break;
	case 1:
		vin_gpio_write(sd, RESET, CSI_GPIO_LOW);
		usleep_range(100, 120);
		break;
	default:
		return -EINVAL;
	}
	*/
	return 0;
}

static int sensor_detect(struct v4l2_subdev *sd)
{
	data_type rdval, rdval2;
	unsigned int SENSOR_ID = 0;
	printk(KERN_WARNING "entering sensor_detect\n");
	sensor_read(sd, CHIP_ID_ADDR, &rdval);
	sensor_read(sd, CHIP_ID_ADDR_L, &rdval2);

	SENSOR_ID = (rdval << 8) | rdval2;
	sensor_print("V4L2_IDENT_SENSOR = 0x%x\n", SENSOR_ID);
	if (SENSOR_ID != V4L2_IDENT_SENSOR) {
		sensor_print("ov5647 %s error, chip found is not an target chip", __func__);
		printk(KERN_WARNING "exiting sensor_detect, not found\n");
		//return -ENODEV;
	}
	printk(KERN_WARNING "exiting sensor_detect, found\n");
	return 0;
}

static int sensor_init(struct v4l2_subdev *sd, u32 val)
{
	int ret = 0;
	struct sensor_info *info = to_state(sd);

	printk(KERN_WARNING "entering sensor_init\n");

	sensor_print("sensor_init\n");

	sensor_power(sd, PWR_ON);	//added

	/*Make sure it is a target sensor */
	ret = sensor_detect(sd);
	if (ret) {
		printk(KERN_WARNING "exiting sensor_init, not found\n");
		sensor_err("chip found is not an target chip.\n");
		sensor_power(sd, PWR_OFF);
		return ret;
	}

	info->focus_status = 0;
	info->low_speed = 0;
	info->width = 1920;
	info->height = 1080;
	info->hflip = 0;
	info->vflip = 0;
	info->gain = 0;

	info->tpf.numerator = 1;
	info->tpf.denominator = 15;	/* 30fps */

	info->preview_first_flag = 1;

	return 0;
}

static int sensor_get_fmt_mbus_core(struct v4l2_subdev *sd, int *code)
{
	*code = MEDIA_BUS_FMT_SGBRG8_1X8;
	return 0;
}

static long sensor_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
	int ret = 0;
	struct sensor_info *info = to_state(sd);

	switch (cmd) {
	case GET_CURRENT_WIN_CFG:
		if (info->current_wins != NULL) {
			memcpy(arg, info->current_wins,
				sizeof(struct sensor_win_size));
			ret = 0;
		} else {
			sensor_err("empty wins!\n");
			ret = -1;
		}
		break;
	case SET_FPS:
		ret = 0;
		break;
	case VIDIOC_VIN_SENSOR_EXP_GAIN:
		ret = 0;//sensor_s_exp_gain(sd, (struct sensor_exp_gain *)arg);
		break;
	case VIDIOC_VIN_SENSOR_CFG_REQ:
		sensor_cfg_req(sd, (struct sensor_config *)arg);
		break;
	case VIDIOC_VIN_ACT_INIT:
		ret = actuator_init(sd, (struct actuator_para *)arg);
		break;
	case VIDIOC_VIN_ACT_SET_CODE:
		ret = actuator_set_code(sd, (struct actuator_ctrl *)arg);
		break;
	case VIDIOC_VIN_GET_SENSOR_CODE:
		sensor_get_fmt_mbus_core(sd, (int *)arg);
		break;
	default:
		return -EINVAL;
	}
	return ret;
}

/*
 * Store information about the video data format.
 */
//camerademo GBRG10 1296 972 30 bmp /home/ 5
static struct sensor_format_struct sensor_formats[] = {
	{
		.desc = "Raw RGB Bayer 10",
		.mbus_code = MEDIA_BUS_FMT_SGBRG10_1X10,
		.regs = sensor_fmt_raw10,
		.regs_size = ARRAY_SIZE(sensor_fmt_raw10),
		.bpp = 1
	}
};
#define N_FMTS ARRAY_SIZE(sensor_formats)

/*
 * Then there is the issue of window sizes.  Try to capture the info here.
 */

static struct sensor_win_size sensor_win_sizes[] = {
	/*{
	  .width	  = 2592,
	  .height	  = 1944,
	  .hoffset	  = 0,
	  .voffset	  = 0,
	  .hts		  = 2844,
	  .vts		  = 0x7b0,
	  .pclk		  = 87.5*1000*1000,
	  .mipi_bps   = 420*1000*1000,
	  .fps_fixed  = 15,
	  .bin_factor = 1,
	  .intg_min   = 16,
	  .intg_max   = (1984-4)<<4,
	  .gain_min   = 1<<4,
	  .gain_max   = 64<<4,
	  .regs		  = ov5647_2592x1944_10bpp, //sensor_qsxga_regs,
	  .regs_size  = ARRAY_SIZE(ov5647_2592x1944_10bpp),
	  .set_size   = NULL,
	},
	*/{
	.width	  	= 1920,
	.height	  	= 1080,
	.hoffset	= 0,
	.voffset	= 0,
	.hts		= 2416,
	.vts		= 0x450,
	.pclk		= 100*1000*1000,
	.mipi_bps   = 1920*1080*10*30,
	.fps_fixed  = 30,
	.bin_factor = 1,
	.intg_min   = 16,
	.intg_max   = (1984-4)<<4,
	.gain_min   = 1<<4,
	.gain_max   = 64<<4,
	.regs		= ov5647_rpi3_1080,
	.regs_size  = ARRAY_SIZE(ov5647_rpi3_1080),
	.set_size   = NULL,
	},/*
	{
	.width	  	= 1296,
	.height	  	= 972,
	.hoffset	= 0,
	.voffset	= 0,
	.hts		= 1896,
	.vts		= 0x59b,
	.pclk		= 91.2*1000*1000,
	.mipi_bps   = 250*1000*1000,
	.fps_fixed  = 15,
	.bin_factor = 2,
	.intg_min   = 16,
	.intg_max   = (1984-4)<<4,
	.gain_min   = 1<<4,
	.gain_max   = 64<<4,
	.regs		= ov5647_2x2binned_10bpp,
	.regs_size  = ARRAY_SIZE(ov5647_2x2binned_10bpp),
	.set_size   = NULL,
	},*/
	//VGA
	/*{
	.width	  	= 640,
	.height	  	= 480,
	.hoffset	= 0,
	.voffset	= 0,
	.hts		= 0x1200,	//Horizontal total size   1852 (unit pclk)
	.vts		= 0x021E,	//Vertical total size 0x1f8 (unit line)
	.pclk		= 46.5*MHZ*2,
	.mipi_bps   = 222*MHZ*2,
	.fps_fixed  = 60,	//fps = camera_clk /(hts * vts)
	.bin_factor = 1,
	.intg_min   = 16,
	.intg_max   = (1984-4)<<4,
	.gain_min   = 1<<4,
	.gain_max   = 64<<4,
	.regs		= ov5647_640x480_custom_1lane,
	.regs_size  = ARRAY_SIZE(ov5647_640x480_custom_1lane),
	.set_size   = NULL,
	},*/
	{
	.width	  	= 1296,	//camerademo GBRG10 1296 972 15 bmp /tmp 5
	.height	  	= 972,
	.hoffset	= 0,
	.voffset	= 0,
	.hts		= 1128,	//Horizontal total size   1852 (unit pclk)
	.vts		= 1200,	//Vertical total size 0x1f8 (unit line)
	.pclk		= 91.2*MHZ,
	.mipi_bps   = 1296*972*10*30,
	.fps_fixed  = 30,	//fps = camera_clk /(hts * vts)
	.bin_factor = 1,
	.intg_min   = 16,
	.intg_max   = (1984-4)<<4,
	.gain_min   = 1<<4,
	.gain_max   = 64<<4,
	.regs		= ov5647_rpi3,
	.regs_size  = ARRAY_SIZE(ov5647_rpi3),
	.set_size   = NULL,
	},
};
#define N_WIN_SIZES (ARRAY_SIZE(sensor_win_sizes))

static int sensor_reg_init(struct sensor_info *
info)
{
	int ret;
	u8 val = MIPI_CTRL00_BUS_IDLE;
	struct v4l2_subdev *sd = &info->sd;
	struct sensor_format_struct *sensor_fmt = info->fmt;
	struct sensor_win_size *wsize = info->current_wins;

	ret = sensor_write_array(sd, ov5647_640x480_custom_1lane,
				ARRAY_SIZE(ov5647_640x480_custom_1lane));
	if (ret < 0) {
		sensor_err("write ov5647_640x480_10bpp error\n");
		return ret;
	}
	data_type val1;
	//now re-read all the registers to make sure they are set correctly
	ret = sensor_read_array(sd, ov5647_rpi3, ARRAY_SIZE(ov5647_rpi3));

	//read VTS (vertical total size) from the sensor, at address 0x380E and 0x380E, and print the true value
	sensor_read(sd, 0x380e, &val1);
	data_type val2 = 0;
	sensor_read(sd, 0x380f, &val2);
	int vts = (val << 8) | val2;
	sensor_print("sensor_reg_init: VTS = %d\n", vts);

	val2 = 0;

	//now hts (horizontal total size), at address 0x380C and 0x380D
	sensor_read(sd, 0x380c, &val1);
	sensor_read(sd, 0x380d, &val2);
	int hts = (val << 8) | val2;
	sensor_print("sensor_reg_init: HTS = %d\n", hts);

	sensor_win_sizes[0].vts = vts;
	sensor_win_sizes[0].hts = hts;	//auto set the hts and vts


	if (ret < 0) {
		sensor_err("read-back ov5647_640x480_10bpp error\n");
		return ret;
	}

	sensor_print("sensor_reg_init\n");

	sensor_write_array(sd, sensor_fmt->regs, sensor_fmt->regs_size);

	if (wsize->regs)
		sensor_write_array(sd, wsize->regs, wsize->regs_size);

	if (wsize->set_size)
		wsize->set_size(sd);

	info->width = wsize->width;
	info->height = wsize->height;
	info->exp = 0;
	info->gain = 0;
	ov5647_sensor_vts = wsize->vts;
	sensor_print("s_fmt set width = %d, height = %d\n", wsize->width,
				wsize->height);

	//val |= MIPI_CTRL00_CLOCK_LANE_GATE | MIPI_CTRL00_LINE_SYNC_ENABLE;

	//sensor_write(sd, OV5647_REG_MIPI_CTRL00, val);
	//sensor_write(sd, OV5640_REG_PAD_OUT, 0x00);

	return 0;
}

static int sensor_s_stream(struct v4l2_subdev *sd, int enable)
{
	struct sensor_info *info = to_state(sd);

	sensor_print("%s on = %d, %d*%d fps: %d code: %x\n", __func__, enable,
			info->current_wins->width, info->current_wins->height,
			info->current_wins->fps_fixed, info->fmt->mbus_code);

	if (!enable){
		sensor_print("sensor_s_stream off\n");
		return 0;
	}

	return sensor_reg_init(info);
}
static int sensor_g_mbus_config(struct v4l2_subdev *sd,
				struct v4l2_mbus_config *cfg)
{
	cfg->type = V4L2_MBUS_CSI2;
	cfg->flags = 0 | V4L2_MBUS_CSI2_1_LANE | V4L2_MBUS_CSI2_CHANNEL_0;

	return 0;
}

static int sensor_g_ctrl(struct v4l2_ctrl *ctrl)
{
	struct sensor_info *info = container_of(ctrl->handler,
			struct sensor_info, handler);
	struct v4l2_subdev *sd = &info->sd;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		return sensor_g_gain(sd, &ctrl->val);
	case V4L2_CID_EXPOSURE:
		return sensor_g_exp(sd, &ctrl->val);
	}
	return -EINVAL;
}

static int sensor_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct sensor_info *info = container_of(ctrl->handler,
			struct sensor_info, handler);
	struct v4l2_subdev *sd = &info->sd;

	switch (ctrl->id) {
	case V4L2_CID_GAIN:
		return sensor_s_gain(sd, ctrl->val);
	case V4L2_CID_EXPOSURE:
		return sensor_s_exp(sd, ctrl->val);
	}
	return -EINVAL;
}



/* ----------------------------------------------------------------------- */

static const struct v4l2_ctrl_ops sensor_ctrl_ops = {
	.g_volatile_ctrl = sensor_g_ctrl,
	.s_ctrl = sensor_s_ctrl,
};

static const struct v4l2_subdev_core_ops sensor_core_ops = {
	.reset = sensor_reset,
	.init = sensor_init,
	.s_power = sensor_power,
	.ioctl = sensor_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl32 = sensor_compat_ioctl32,
#endif
};

static const struct v4l2_subdev_video_ops sensor_video_ops = {
	.s_parm = sensor_s_parm,
	.g_parm = sensor_g_parm,
	.s_stream = sensor_s_stream,
	.g_mbus_config = sensor_g_mbus_config,
};

static const struct v4l2_subdev_pad_ops sensor_pad_ops = {
	.enum_mbus_code = sensor_enum_mbus_code,
	.enum_frame_size = sensor_enum_frame_size,
	.get_fmt = sensor_get_fmt,
	.set_fmt = sensor_set_fmt,
};

static const struct v4l2_subdev_ops sensor_ops = {
	.core = &sensor_core_ops,
	.video = &sensor_video_ops,
	.pad = &sensor_pad_ops,
};

/* ----------------------------------------------------------------------- */
static struct cci_driver cci_drv = {
		.name = SENSOR_NAME,
		.addr_width = CCI_BITS_16,
		.data_width = CCI_BITS_8,
};

static const struct v4l2_ctrl_config sensor_custom_ctrls[] = {
	{
		.ops = &sensor_ctrl_ops,
		.id = V4L2_CID_FRAME_RATE,
		.name = "frame rate",
		.type = V4L2_CTRL_TYPE_INTEGER,
		.min = 15,
		.max = 120,
		.step = 1,
		.def = 120,
	},
};

static int sensor_init_controls(struct v4l2_subdev *sd,
			const struct v4l2_ctrl_ops *ops)
{
	struct sensor_info *info = to_state(sd);
	struct v4l2_ctrl_handler *handler = &info->handler;
	struct v4l2_ctrl *ctrl;
	int i;
	int ret = 0;

	v4l2_ctrl_handler_init(handler, 2 + ARRAY_SIZE(sensor_custom_ctrls));

	v4l2_ctrl_new_std(handler, ops, V4L2_CID_GAIN, 1 * 1600,
				256 * 1600, 1, 1 * 1600);
	ctrl = v4l2_ctrl_new_std(handler, ops, V4L2_CID_EXPOSURE, 0,
				65536 * 16, 1, 0);
	if (ctrl != NULL)
		ctrl->flags |= V4L2_CTRL_FLAG_VOLATILE;
	for (i = 0; i < ARRAY_SIZE(sensor_custom_ctrls); i++)
		v4l2_ctrl_new_custom(handler, &sensor_custom_ctrls[i], NULL);

	if (handler->error) {
		ret = handler->error;
		v4l2_ctrl_handler_free(handler);
	}

	sd->ctrl_handler = handler;

	return ret;
}

static int sensor_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct v4l2_subdev *sd;
	struct sensor_info *info;
	printk(KERN_WARNING "entering sensor_probe\n");

	info = kzalloc(sizeof(struct sensor_info), GFP_KERNEL);
	if (info == NULL)
		return -ENOMEM;
	sd = &info->sd;

	cci_dev_probe_helper(sd, client, &sensor_ops, &cci_drv);
	sensor_init_controls(sd, &sensor_ctrl_ops);

	mutex_init(&info->lock);
#ifdef CONFIG_SAME_I2C
	info->sensor_i2c_addr = I2C_ADDR >> 1;
#endif
	info->fmt = &sensor_formats[1]; //default rgb8
	info->fmt_pt = &sensor_formats[1];
	info->win_pt = &sensor_win_sizes[0];	//default 640x480
	info->fmt_num = N_FMTS;
	info->win_size_num = N_WIN_SIZES;
	info->sensor_field = V4L2_FIELD_NONE;
	info->stream_seq = MIPI_BEFORE_SENSOR;
	info->af_first_flag = 1;
	info->exp = 0;
	info->gain = 0;

	return 0;
}

static int sensor_remove(struct i2c_client *client)
{
	struct v4l2_subdev *sd;
	printk(KERN_WARNING "entering sensor_remove\n");

	sd = cci_dev_remove_helper(client, &cci_drv);

	kfree(to_state(sd));
	return 0;
}

static const struct i2c_device_id sensor_id[] = {
	{SENSOR_NAME, 0},
	{}
};

MODULE_DEVICE_TABLE(i2c, sensor_id);

static struct i2c_driver sensor_driver = {
		.driver = {
				.owner = THIS_MODULE,
				.name = SENSOR_NAME,
				},
		.probe = sensor_probe,
		.remove = sensor_remove,
		.id_table = sensor_id,
};
static __init int init_sensor(void)
{
	return cci_dev_init_helper(&sensor_driver);
}

static __exit void exit_sensor(void)
{
	cci_dev_exit_helper(&sensor_driver);
}

module_init(init_sensor);
module_exit(exit_sensor);