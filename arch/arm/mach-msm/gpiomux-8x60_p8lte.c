/* Copyright (c) 2010-2011, Code Aurora Forum. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <mach/irqs.h>
#include <asm/mach-types.h>
#include <mach/gpiomux.h>
#include "gpiomux-8x60.h"

//I2S
static struct gpiomux_setting i2s_susp_sck2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting i2s_susp_ws2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting i2s_susp_sd2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting i2s_susp_mclk2 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};


// hsil
static struct gpiomux_setting usb_switch = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting console_uart = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi1 = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gsbi3 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi4 = {
	.func = GPIOMUX_FUNC_1, 
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN, // GPIOMUX_PULL_NONE
};

#if defined(CONFIG_KOR_OPERATOR_SKT) || defined(CONFIG_JPN_OPERATOR_NTT)
static struct gpiomux_setting gsbi4_p8 = {
	.func = GPIOMUX_FUNC_1, 
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_DOWN, // GPIOMUX_PULL_NONE
};
#endif

static struct gpiomux_setting gsbi7 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi8 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting gsbi10 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ps_hold = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_12MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_switch_en_actv_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_switch_cntl_actv_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_hub_reset_actv_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_switch_en_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting usb_switch_cntl_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting usb_hub_reset_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting msm_snddev_active_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting msm_snddev_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting wlan_pwdn_n_actv_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wlan_pwdn_n_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting ebi2_a_d = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ebi2_oe = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ebi2_we = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ebi2_cs2 = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ebi2_cs3 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
static struct gpiomux_setting ebi2_cs4 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};
#endif

static struct gpiomux_setting ebi2_adv = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
static struct gpiomux_setting usb_isp1763_actv_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting usb_isp1763_susp_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

static struct gpiomux_setting sdcc1_dat_0_3_cmd_actv_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc1_dat_4_7_cmd_actv_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc1_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdcc1_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc2_dat_0_3_cmd_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc2_dat_4_7_cmd_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc2_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdcc2_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP, 
};

static struct gpiomux_setting sdcc5_dat_0_3_cmd_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_10MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting sdcc5_clk_actv_cfg = {
	.func = GPIOMUX_FUNC_2,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting sdcc5_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting aux_pcm_active_config = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting aux_pcm_suspend_config = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting uart1dm_active = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting uart1dm_suspended = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mi2s_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mi2s_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting lcdc_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting lcdc_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting hdmi_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_status_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_status_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting cam_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_sync_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_sync_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting tm_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting tm_suspended = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting tma_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting max_touch_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting max_touch_suspended = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ts_ldo_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ts_ldo_suspended = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting lock_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting ts_active = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_6MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting ts_suspended = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdp_vsync_active_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting hdmi_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting hdmi_active_2_cfg = {
#ifdef CONFIG_SAMSUNG_HDMI_DDC_I2C_SOLUTION
	.func = GPIOMUX_FUNC_GPIO,
#else
	.func = GPIOMUX_FUNC_1,
#endif
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting hdmi_active_3_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting pmic_suspended_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cam_active_1_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting cam_active_2_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

#if 0//samsung LTE
static struct gpiomux_setting cam_active_3_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting cam_active_4_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting cam_active_5_cfg = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_4MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879) || defined (CONFIG_WM8994_AMP)
static struct gpiomux_setting amp_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting amp_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_SENSORS_K3DH
static struct gpiomux_setting accel_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
static struct gpiomux_setting accel_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif

#ifdef CONFIG_GYRO_K3G
static struct gpiomux_setting gyro_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
        .dir = 2,
};

static struct gpiomux_setting gyro_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
};

#if defined(CONFIG_KOR_OPERATOR_SKT) ||defined(CONFIG_KOR_OPERATOR_LGU)||defined(CONFIG_KOR_OPERATOR_KT) \
	|| defined(CONFIG_JPN_OPERATOR_NTT)
static struct gpiomux_setting gyro_fifo_int_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
static struct gpiomux_setting gyro_fifo_int_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};
#endif
#endif

#ifdef CONFIG_CMC623_P5LTE
static struct gpiomux_setting cmc623_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
    .dir  = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting cmc623_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
    .dir  = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_CMC624_P8LTE
static struct gpiomux_setting cmc624_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
    .dir  = GPIOMUX_OUT_LOW,
};
static struct gpiomux_setting cmc624_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv  = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
    .dir  = GPIOMUX_IN,
};
#endif

#ifdef CONFIG_MSM_GSBI9_UART
static struct gpiomux_setting uart9dm_active = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA ,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting gsbi9 = {
	.func = GPIOMUX_FUNC_1,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};
#endif

static struct gpiomux_setting ap2mdm_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_status_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_vfr_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting mdm2ap_vfr_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting mdm2ap_errfatal_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_16MA,
	.pull = GPIOMUX_PULL_DOWN,
};

static struct gpiomux_setting ap2mdm_kpdpwr_n_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_8MA,
	.pull = GPIOMUX_PULL_NONE,
};


static struct gpiomux_setting mdm2ap_vddmin_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting mdm2ap_vddmin_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
};

static struct gpiomux_setting wlan_en_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting wlan_en_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};


static struct gpiomux_setting wlan_host_wake_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = 0,
};

#ifdef CONFIG_ISDBTMM
static struct gpiomux_setting tmm_active_in_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting tmm_suspend_in_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting tmm_active_out_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_OUT_LOW,
};

static struct gpiomux_setting tmm_suspend_out_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = GPIOMUX_OUT_LOW,
};
#endif

#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
static struct gpiomux_setting tdmb_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = 0,
};

static struct gpiomux_setting tdmb_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = 0,
};
#endif
static struct gpiomux_setting accessory_id_active_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = GPIOMUX_IN,
};

static struct gpiomux_setting motor_i2c_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
  .dir = 0,
};

static struct gpiomux_setting motor_en_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
        .dir = 2,
};

static struct gpiomux_setting nc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = 0,
};

static struct gpiomux_setting boot_config_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = 0,
};

static struct gpiomux_setting mhl_ddc_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};

static struct gpiomux_setting output_pd_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = 2,
};

static struct gpiomux_setting output_pn_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = 2,
};

static struct gpiomux_setting input_pu_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
	.dir = 0,
};

static struct gpiomux_setting input_pd_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
	.dir = 0,
};

static struct gpiomux_setting input_pn_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_NONE,
	.dir = 0,
};


static struct gpiomux_setting mxt768e_touch_irq_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_UP,
};
static struct gpiomux_setting mxt768e_touch_suspend_cfg = {
	.func = GPIOMUX_FUNC_GPIO,
	.drv = GPIOMUX_DRV_2MA,
	.pull = GPIOMUX_PULL_DOWN,
    .dir  = GPIOMUX_IN,	
};

static struct msm_gpiomux_config msm8x60_gsbi_configs[] __initdata = {
	{
		.gpio      = 33,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1,
		},
	},
	{
		.gpio      = 34,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1,
		},
	},
	{
		.gpio      = 35,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1,
		},
	},
	{
		.gpio      = 36,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1,
		},
	},
	{
		.gpio      = 124,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi1,
		},
	},
	{
		.gpio      = 43,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3,
		},
	},
	{
		.gpio      = 44,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi3,
		},
	},
	{
		.gpio      = 59,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi7,
		},
	},
	{
		.gpio      = 60,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi7,
		},
	},
	{
		.gpio      = 64,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi8,
		},
	},
	{
		.gpio      = 65,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi8,
		},
	},
#if defined(CONFIG_PN544)
	{
		.gpio      = 72,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
	{
		.gpio      = 73,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},	
#endif	
};

static struct msm_gpiomux_config msm8x60_fluid_gsbi_configs[] __initdata = {
#ifndef CONFIG_CMC624_P8LTE
	{
		.gpio      = 70,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
	{
		.gpio      = 72,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
#endif	
	{
		.gpio      = 73,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi10,
		},
	},
};

static struct msm_gpiomux_config msm8x60_ebi2_configs[] __initdata = {
	{
		.gpio      = 40,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs2,
		},
	},
	{
		.gpio      = 92,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ps_hold,
		},
	},
#if defined(CONFIG_KOR_OPERATOR_SKT) || defined(CONFIG_JPN_OPERATOR_NTT)/*  123 ~ 130 is normal gpio */
	{
		.gpio      = 123,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 124,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 126,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 127,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 128,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 129,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 130,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
#endif
#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
	/* ISP VDD_3V3_EN */
	{
		.gpio      = 132,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs4,
		},
	},
#endif
#if 0
	{
		.gpio      = 133,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_cs3,
		},
	},
#endif
	{
		.gpio      = 135,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 136,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 138,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 139,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 140,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 143,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 144,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 145,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 146,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 147,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 148,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 149,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 150,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_a_d,
		},
	},
	{
		.gpio      = 151,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ebi2_oe,
		},
	},
};

#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
static struct msm_gpiomux_config msm8x60_amp_configs[] __initdata = {
	{
		.gpio      = 154,
		.settings = {
			[GPIOMUX_ACTIVE]    = &amp_active_cfg,
			[GPIOMUX_SUSPENDED] = &amp_suspend_cfg,
		},
	},
	{
		.gpio      = 155,
		.settings = {
			[GPIOMUX_ACTIVE]    = &amp_active_cfg,
			[GPIOMUX_SUSPENDED] = &amp_suspend_cfg,
		},
	},
};
#endif


#ifdef CONFIG_SENSORS_K3DH
static struct msm_gpiomux_config msm8x60_accel_configs[] __initdata = {
	{
		.gpio      = 51,
		.settings = {
			[GPIOMUX_ACTIVE]    = &accel_active_cfg,
			[GPIOMUX_SUSPENDED] = &input_pd_cfg,
		},
	},
	{
		.gpio      = 52,
		.settings = {
			[GPIOMUX_ACTIVE]    = &accel_active_cfg,
			[GPIOMUX_SUSPENDED] = &input_pd_cfg,
		},
	},
};
#endif

#ifdef CONFIG_GYRO_K3G
static struct msm_gpiomux_config msm8x60_gyro_configs[] __initdata = {
	{
		.gpio      = 38,
		.settings = {
		    [GPIOMUX_ACTIVE] = &gyro_active_cfg,
			[GPIOMUX_SUSPENDED] = &input_pd_cfg,
		},
	},
	{
		.gpio      = 39,
		.settings = {
		    [GPIOMUX_ACTIVE] = &gyro_active_cfg,
			[GPIOMUX_SUSPENDED] = &input_pd_cfg,
		},
	},
	{
		.gpio      = 102,
		.settings = {
			[GPIOMUX_SUSPENDED] = &output_pn_cfg,
		},
	},
};
#endif

#ifdef CONFIG_CMC623_P5LTE
static struct msm_gpiomux_config msm8x60_cmc623_configs[] __initdata = {
	{
		.gpio      = 70,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},

	{
		.gpio      = 103,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},
	{
		.gpio      = 104,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},
	{
		.gpio      = 106,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},

	{
		.gpio      = 156,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},
	{
		.gpio      = 157,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc623_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc623_suspend_cfg,
		},
	},
};
#endif

#ifdef CONFIG_CMC624_P8LTE
static struct msm_gpiomux_config msm8x60_cmc624_configs[] __initdata = {
	{
		.gpio      = 70,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
	{
		.gpio      = 72,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
	{
		.gpio      = 103,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
	{
		.gpio      = 104,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
	{
		.gpio      = 156,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
	{
		.gpio      = 157,
		.settings = {
			[GPIOMUX_ACTIVE]	= &cmc624_active_cfg,
			[GPIOMUX_SUSPENDED] = &cmc624_suspend_cfg,
		},
	},
};
#endif

#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
static struct msm_gpiomux_config msm8x60_isp_usb_configs[] __initdata = {
	{
		.gpio      = 117,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_isp1763_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_isp1763_susp_cfg,
		},
	},
	{
		.gpio      = 152,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_isp1763_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_isp1763_susp_cfg,
		},
	},

};
#endif

static struct msm_gpiomux_config p5_lte_usb_sel[] __initdata = {
	{ 
		.gpio      = 37, //USB_SEL_2
		.settings = {
			[GPIOMUX_SUSPENDED] = &usb_switch,
		},
	},
};

static struct msm_gpiomux_config p8_lte_usb_sel[] __initdata = {
#ifndef CONFIG_CMC624_P8LTE	
	{
		.gpio      = 70, //USB_SEL_1
		.settings = {
			[GPIOMUX_SUSPENDED] = &usb_switch,
		},
	},
#endif
	{
		.gpio      = 37, //USB_SEL_2
		.settings = {
			[GPIOMUX_SUSPENDED] = &usb_switch,
		},
	},
};

static struct msm_gpiomux_config msm8x60_uart_configs[] __initdata = {
	{ /* UARTDM_TX */
		.gpio      = 53,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_RX */
		.gpio      = 54,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_CTS */
		.gpio      = 55,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
	{ /* UARTDM_RFR */
		.gpio      = 56,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart1dm_active,
			[GPIOMUX_SUSPENDED] = &uart1dm_suspended,
		},
	},
#if !defined(CONFIG_USB_PEHCI_HCD) && !defined(CONFIG_USB_PEHCI_HCD_MODULE)
	/* USB ISP1763 may also use 117 GPIO */
	{
		.gpio      = 117,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
#endif
	{
		.gpio      = 118,
		.settings = {
			[GPIOMUX_SUSPENDED] = &console_uart,
		},
	},
};

#ifdef CONFIG_MSM_GSBI9_UART
static struct msm_gpiomux_config msm8x60_charm_uart_configs[] __initdata = {
	{ /* UART9DM  RX */
		.gpio	   = 66,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart9dm_active,
			[GPIOMUX_SUSPENDED] = &gsbi9,
		},
	},
	{ /* UART9DM TX */
		.gpio	   = 67,
		.settings = {
			[GPIOMUX_ACTIVE]    = &uart9dm_active,
			[GPIOMUX_SUSPENDED] = &gsbi9,
		},
	},
};
#endif

static struct msm_gpiomux_config msm8x60_max_touch_configs[] __initdata = {
	{
		/* TS_INTERRUPT */
		.gpio = 61,
		.settings = {
			[GPIOMUX_ACTIVE] = &max_touch_active,
			[GPIOMUX_SUSPENDED] = &max_touch_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_lock_configs[] __initdata = {
	{
		/* TS_ATTN */
		.gpio = 67,
		.settings = {
			[GPIOMUX_ACTIVE] = &lock_active,
		},
	},
};

static struct msm_gpiomux_config msm8x60_ts_ldo_configs[] __initdata = {
	{
		/* TS_LDO_EN */
		.gpio = 69,
		.settings = {
			[GPIOMUX_ACTIVE] = &ts_ldo_active,
			[GPIOMUX_SUSPENDED] = &ts_ldo_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_ts_reset_configs[] __initdata = {
	{
		/* TS_ATTN */
		.gpio = 58,
		.settings = {
			[GPIOMUX_ACTIVE] = &ts_active,
			[GPIOMUX_SUSPENDED] = &ts_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_ts_configs[] __initdata = {
	{
		/* TS_ATTN */
		.gpio = 58,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ts_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_tmg200_configs[] __initdata = {
	{
		.gpio = 61,
		.settings = {
			[GPIOMUX_ACTIVE] = &tm_active,
			[GPIOMUX_SUSPENDED] = &tm_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_tma300_configs[] __initdata = {
	{
		.gpio = 61,
		.settings = {
			[GPIOMUX_ACTIVE]    = &tma_active,
			[GPIOMUX_SUSPENDED] = &tm_suspended,
		},
	},
};

static struct msm_gpiomux_config msm8x60_aux_pcm_configs[] __initdata = {
	{
		.gpio = 111,
		.settings = {
			[GPIOMUX_ACTIVE]    = &aux_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &aux_pcm_suspend_config,
		},
	},
	{
		.gpio = 112,
		.settings = {
			[GPIOMUX_ACTIVE]    = &aux_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &aux_pcm_suspend_config,
		},
	},
	{
		.gpio = 113,
		.settings = {
			[GPIOMUX_ACTIVE]    = &aux_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &aux_pcm_suspend_config,
		},
	},
	{
		.gpio = 114,
		.settings = {
			[GPIOMUX_ACTIVE]    = &aux_pcm_active_config,
			[GPIOMUX_SUSPENDED] = &aux_pcm_suspend_config,
		},
	},
};

static struct msm_gpiomux_config msm8x60_sdc_configs[] __initdata = {
	/* SDCC1 data[0] */
	{
		.gpio = 159,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[1] */
	{
		.gpio = 160,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[2] */
	{
		.gpio = 161,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[3] */
	{
		.gpio = 162,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[4] */
	{
		.gpio = 163,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[5] */
	{
		.gpio = 164,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[6] */
	{
		.gpio = 165,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 data[7] */
	{
		.gpio = 166,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 CLK */
	{
		.gpio = 167,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
	/* SDCC1 CMD */
	{
		.gpio = 168,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc1_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc1_suspend_config,
		},
	},
};

static struct msm_gpiomux_config msm_qrdc_sdc_configs[] __initdata = {
	{
		.gpio      = 118,
		.settings = {
			[GPIOMUX_ACTIVE]    = &wlan_pwdn_n_actv_cfg,
			[GPIOMUX_SUSPENDED] = &wlan_pwdn_n_susp_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_charm_sdc_configs[] __initdata = {
	/* SDCC5 cmd */
	{
		.gpio = 95,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* SDCC5 data[3]*/
	{
		.gpio = 96,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* SDCC5 clk */
	{
		.gpio = 97,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* SDCC5 data[2]*/
	{
		.gpio = 98,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* SDCC5 data[1]*/
	{
		.gpio = 99,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* SDCC5 data[0]*/
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc5_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc5_suspend_config,
		},
	},
	/* MDM2AP_SYNC */
	{
		.gpio = 129,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdm2ap_sync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdm2ap_sync_suspend_cfg,
		},
	},

	/* MDM2AP_VDDMIN */
	{
		.gpio = 140,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdm2ap_vddmin_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdm2ap_vddmin_suspend_cfg,
		},
	},
	/* SDCC2 data[0] */
	{
		.gpio = 143,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[1] */
	{
		.gpio = 144,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[2] */
	{
		.gpio = 145,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[3] */
	{
		.gpio = 146,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[4] */
	{
		.gpio = 147,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[5] */
	{
		.gpio = 148,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[6] */
	{
		.gpio = 149,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 data[7] */
	{
		.gpio = 150,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_4_7_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
	/* SDCC2 CMD */
	{
		.gpio = 151,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_dat_0_3_cmd_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},

	/* SDCC2 CLK */
	{
		.gpio = 152,
		.settings = {
			[GPIOMUX_ACTIVE]    = &sdcc2_clk_actv_cfg,
			[GPIOMUX_SUSPENDED] = &sdcc2_suspend_config,
		},
	},
};

static struct msm_gpiomux_config msm_qrdc_usb_configs[] __initdata = {
	{
		.gpio      = 34,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_hub_reset_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_hub_reset_susp_cfg,
		},
	},
	{
		.gpio      = 131,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_switch_cntl_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_switch_cntl_susp_cfg,
		},
	},
	{
		.gpio      = 132,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_switch_en_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_switch_en_susp_cfg,
		},
	},
};

static struct msm_gpiomux_config msm_qt_usb_configs[] __initdata = {
	{
		.gpio      = 63,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_hub_reset_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_hub_reset_susp_cfg,
		},
	},
	{
		.gpio      = 131,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_switch_cntl_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_switch_cntl_susp_cfg,
		},
	},
	{
		.gpio      = 132,
		.settings = {
			[GPIOMUX_ACTIVE]    = &usb_switch_en_actv_cfg,
			[GPIOMUX_SUSPENDED] = &usb_switch_en_susp_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_snd_configs[] __initdata = {
	{
		.gpio = 108,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm_snddev_active_config,
			[GPIOMUX_SUSPENDED] = &msm_snddev_suspend_config,
		},
	},
	{
		.gpio = 109,
		.settings = {
			[GPIOMUX_ACTIVE]    = &msm_snddev_active_config,
			[GPIOMUX_SUSPENDED] = &msm_snddev_suspend_config,
		},
	},
};

static struct msm_gpiomux_config msm8x60_i2s_configs[] __initdata = {
	{
		.gpio = 119,
		.settings = {
			[GPIOMUX_SUSPENDED] = &i2s_susp_sck2,
		},
	},
	{
		.gpio = 120,
		.settings = {
			[GPIOMUX_SUSPENDED] = &i2s_susp_ws2,
		},
	},
	{
		.gpio = 121,
		.settings = {
			[GPIOMUX_SUSPENDED] = &i2s_susp_sd2,
		},
	},
	{
		.gpio = 122,
		.settings = {
			[GPIOMUX_SUSPENDED] = &i2s_susp_mclk2,
		},
	},
};

static struct msm_gpiomux_config msm8x60_mi2s_configs[] __initdata = {
	/* MI2S WS */
	{
		.gpio = 101,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mi2s_active_cfg,
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_cfg,
		},
	},
	/* MI2S SD3 */
	{
		.gpio = 107,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mi2s_active_cfg,
			[GPIOMUX_SUSPENDED] = &mi2s_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_lcdc_configs[] __initdata = {
	/* lcdc_pclk */
	{
		.gpio = 0,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_hsync */
	{
		.gpio = 1,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_vsync */
	{
		.gpio = 2,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_den */
	{
		.gpio = 3,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red7 */
	{
		.gpio = 4,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red6 */
	{
		.gpio = 5,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red5 */
	{
		.gpio = 6,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red4 */
	{
		.gpio = 7,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red3 */
	{
		.gpio = 8,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red2 */
	{
		.gpio = 9,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red1 */
	{
		.gpio = 10,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_red0 */
	{
		.gpio = 11,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn7 */
	{
		.gpio = 12,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn6 */
	{
		.gpio = 13,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn5 */
	{
		.gpio = 14,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn4 */
	{
		.gpio = 15,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn3 */
	{
		.gpio = 16,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn2 */
	{
		.gpio = 17,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn1 */
	{
		.gpio = 18,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_grn0 */
	{
		.gpio = 19,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu7 */
	{
		.gpio = 20,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu6 */
	{
		.gpio = 21,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu5 */
	{
		.gpio = 22,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu4 */
	{
		.gpio = 23,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu3 */
	{
		.gpio = 24,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu2 */
	{
		.gpio = 25,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu1 */
	{
		.gpio = 26,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
	/* lcdc_blu0 */
	{
		.gpio = 27,
		.settings = {
			[GPIOMUX_ACTIVE]    = &lcdc_active_cfg,
			[GPIOMUX_SUSPENDED] = &lcdc_suspend_cfg,
		},
	},
};

/*  [PxLTE] SAMSUNG, actually 28 pin is connected to CMC623_nRST  */
static struct msm_gpiomux_config msm8x60_mdp_vsync_configs[] __initdata = {
	{
		.gpio = 28,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdp_vsync_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdp_vsync_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_hdmi_configs[] __initdata = {
	{
		.gpio = 170,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &mhl_ddc_cfg,
		},
	},
	{
		.gpio = 171,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &mhl_ddc_cfg,
		},
	},
	{
		.gpio = 172,
		.settings = {
			[GPIOMUX_ACTIVE]    = &hdmi_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &hdmi_suspend_cfg,
		},
	},
};

/* Because PMIC drivers do not use gpio-management routines and PMIC
 * gpios must never sleep, a "good enough" config is obtained by placing
 * the active config in the 'suspended' slot and leaving the active
 * config invalid: the suspended config will be installed at boot
 * and never replaced.
 */

static struct msm_gpiomux_config msm8x60_pmic_configs[] __initdata = {
	{
		.gpio = 88,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pmic_suspended_cfg,
		},
	},
	{
		.gpio = 91,
		.settings = {
			[GPIOMUX_SUSPENDED] = &pmic_suspended_cfg,
		},
	},
};

#if 0
static struct msm_gpiomux_config msm8x60_common_configs[] __initdata = {
	/* MDM2AP_STATUS */
	{
		.gpio = 77,
		.settings = {
			[GPIOMUX_ACTIVE]    = &mdm2ap_status_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdm2ap_status_suspend_cfg,
		},
	},
};
#endif

static struct msm_gpiomux_config msm8x60_cam_configs[] __initdata = {
	// CAM_MCLK
	{
		.gpio = 32,
		.settings = {
//			[GPIOMUX_ACTIVE]    = &cam_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &output_pd_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
#if defined(CONFIG_KOR_OPERATOR_SKT) || defined(CONFIG_JPN_OPERATOR_NTT)
		// cam sda
	{
		.gpio      = 47,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4_p8,
		},
	},
	// cam scl
	{
		.gpio      = 48,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4_p8,
		},
	},	
#else	
	// cam sda
	{
		.gpio      = 47,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4,
		},
	},
	// cam scl
	{
		.gpio      = 48,
		.settings = {
			[GPIOMUX_SUSPENDED] = &gsbi4,
		},
	},
#endif	
	// cam pmic en1
	{
		.gpio      = 57,
		.settings = {
			[GPIOMUX_SUSPENDED] = &output_pd_cfg,
		},
	},
	// cam flash_en
	{
		.gpio = 137,
		.settings = {
			[GPIOMUX_SUSPENDED] = &output_pd_cfg,
		},
	},
	// cam movie_en
	{
		.gpio = 142,
		.settings = {
			[GPIOMUX_SUSPENDED] = &output_pd_cfg,
		},
	},
};
static struct msm_gpiomux_config msm_qt_cam_configs[] __initdata = {
	{
		.gpio = 32,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_1_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
	{
		.gpio = 42,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
#if 0 //samsung LTE
	{
		.gpio = 47,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
	{
		.gpio = 48,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_3_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
#endif
	{
		.gpio = 105,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
	{
		.gpio = 106,
		.settings = {
			[GPIOMUX_ACTIVE]    = &cam_active_2_cfg,
			[GPIOMUX_SUSPENDED] = &cam_suspend_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_charm_configs[] __initdata = {
	/* AP2MDM_WAKEUP */
	{
		.gpio = 135,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_VFR */
	{
		.gpio = 29,
		.settings = {
			[GPIOMUX_ACTIVE] = &mdm2ap_vfr_active_cfg,
			[GPIOMUX_SUSPENDED] = &mdm2ap_vfr_suspend_cfg,
		}
	},
	/* AP2MDM_STATUS */
	{
		.gpio = 136,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_STATUS */
	{
		.gpio = 134,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_status_cfg,
		}
	},
	/* MDM2AP_WAKEUP */
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* MDM2AP_ERRFATAL */
	{
		.gpio = 133,
		.settings = {
			[GPIOMUX_SUSPENDED] = &mdm2ap_errfatal_cfg,
		}
	},
	/* AP2MDM_ERRFATAL */
	{
		.gpio = 93,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_cfg,
		}
	},
	/* AP2MDM_KPDPWR_N */
	{
		.gpio = 132,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	},
	/* AP2MDM_PMIC_RESET_N */
	{
		.gpio = 131,
		.settings = {
			[GPIOMUX_SUSPENDED] = &ap2mdm_kpdpwr_n_cfg,
		}
	}
};

static struct msm_gpiomux_config msm8x60_wlan_configs[] __initdata = {
	/* GPIO_WLAN_REG_ON  */
	{
		.gpio = 45,
		.settings = {
			[GPIOMUX_ACTIVE] = &wlan_en_active_cfg,
			[GPIOMUX_SUSPENDED] = &wlan_en_suspend_cfg,
		}
	},
	/* GPIO_WLAN_HOST_WAKE */
	{
		.gpio = 105,
		.settings = {
			[GPIOMUX_ACTIVE] = &wlan_host_wake_active_cfg,
			[GPIOMUX_SUSPENDED] = &wlan_host_wake_active_cfg,
		}
	}
};

#ifdef CONFIG_ISDBTMM
static struct msm_gpiomux_config msm8x60_tmm_configs[] __initdata = {
	/* GPIO_TMM_FRMLOCK */
	{
		.gpio = 21,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_suspend_in_cfg,
		}
	},
	/* GPIO_TMM_SPIC_XIRQ */
	{
		.gpio = 26,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_suspend_in_cfg,
		}
	},
	/* GPIO_TMM_SPIS_XIRQ */
	{
		.gpio = 27,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_suspend_in_cfg,
		}
	},
	/* GPIO_TMM_XIRQ */
	{
		.gpio = 124,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_suspend_in_cfg,
		}
	},
	/* GPIO_TMM_XRESET */
	{
		.gpio = 126,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_suspend_in_cfg,
		}
	},
	/* GPIO_TMM_PWR_EN */
	{
		.gpio = 130,
		.settings = {
			[GPIOMUX_ACTIVE] = &tmm_active_in_cfg,
			[GPIOMUX_SUSPENDED] = &tmm_active_in_cfg,
		}
	},
};
#endif

#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
static struct msm_gpiomux_config msm8x60_tdmb_configs[] __initdata = {
	/* GPIO_TDMB_RST  */
	{
		.gpio = 126,
		.settings = {
			[GPIOMUX_ACTIVE] = &tdmb_active_cfg,
			[GPIOMUX_SUSPENDED] = &tdmb_suspend_cfg,
		}
	},
	/* GPIO_TDMB_INT  */
	{
		.gpio = 128,
		.settings = {
			[GPIOMUX_ACTIVE] = &tdmb_active_cfg,
			[GPIOMUX_SUSPENDED] = &tdmb_suspend_cfg,
		}
	},
	/* GPIO_TDMB_EN */
	{
		.gpio = 130,
		.settings = {
			[GPIOMUX_ACTIVE] = &tdmb_active_cfg,
			[GPIOMUX_SUSPENDED] = &tdmb_suspend_cfg,
		}
	}
};
#endif

static struct msm_gpiomux_config msm8x60_accessory_configs[] __initdata = {
	/* ACCESSORY_INT  */
	{
		.gpio = 123,
		.settings = {
			[GPIOMUX_ACTIVE] = &accessory_id_active_cfg,
			[GPIOMUX_SUSPENDED] = &accessory_id_active_cfg,
		}
	},
};

static struct msm_gpiomux_config msm8x60_boot_configs[] __initdata = {
	/* BOOT_CONFIG_6 */
	{
		.gpio = 76,
		.settings = {
			[GPIOMUX_SUSPENDED] = &boot_config_cfg,
		}
	},
	/* BOOT_CONFIG_0 */
	{
		.gpio = 81,
		.settings = {
			[GPIOMUX_SUSPENDED] = &boot_config_cfg,
		}
	},
	/* BOOT_CONFIG_1 */
	{
		.gpio = 84,
		.settings = {
			[GPIOMUX_SUSPENDED] = &boot_config_cfg,
		}
	},
};


static struct msm_gpiomux_config msm8x60_motor_configs[]	__initdata = {
	// motor_en
	{
		
		.gpio			=	30,
		.settings	= {
			[GPIOMUX_SUSPENDED]	=	&motor_en_suspend_cfg,
		}
	},
	// motor_scl
	{
		
		.gpio			=	115,
		.settings	= {
			[GPIOMUX_SUSPENDED]	=	&motor_i2c_suspend_cfg,
		}
	},
	// motor_sda
	{
		
		.gpio			=	116,
		.settings	= {
			[GPIOMUX_SUSPENDED]	=	&motor_i2c_suspend_cfg,
		}
	},
};


static struct msm_gpiomux_config msm8x60_mxt768e_configs[]	__initdata = {
	// touch irq
	{
		
		.gpio			=	125,
		.settings	= {
			[GPIOMUX_ACTIVE] = &mxt768e_touch_irq_cfg,		
			[GPIOMUX_SUSPENDED]	=	&mxt768e_touch_suspend_cfg,
		}
	},

};

static struct msm_gpiomux_config msm8x60_nc_configs[] __initdata = {
	{		
		.gpio			=	62,
		.settings	= {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},  
	{
		.gpio      = 153,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 73,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 74,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 75,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 169,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 141,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},

#ifndef CONFIG_CMC624_P8LTE	
	{
		.gpio      = 70,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 72,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 156,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio      = 157,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
#endif
};

struct msm_gpiomux_configs
msm8x60_surf_ffa_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{msm8x60_ebi2_configs, ARRAY_SIZE(msm8x60_ebi2_configs)},
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
#if defined(CONFIG_USB_PEHCI_HCD) || defined(CONFIG_USB_PEHCI_HCD_MODULE)
	{msm8x60_isp_usb_configs, ARRAY_SIZE(msm8x60_isp_usb_configs)},
#endif
	{msm8x60_ts_configs, ARRAY_SIZE(msm8x60_ts_configs)},
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
//	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
	{msm8x60_i2s_configs, ARRAY_SIZE(msm8x60_i2s_configs)},
#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
	{msm8x60_amp_configs, ARRAY_SIZE(msm8x60_amp_configs)},
#endif
#ifdef CONFIG_SENSORS_K3DH
	{msm8x60_accel_configs, ARRAY_SIZE(msm8x60_accel_configs)},
#endif
#ifdef CONFIG_GYRO_K3G
	{msm8x60_gyro_configs, ARRAY_SIZE(msm8x60_gyro_configs)},
#endif
	{msm8x60_tmg200_configs, ARRAY_SIZE(msm8x60_tmg200_configs)},
	{NULL, 0},
};

struct msm_gpiomux_configs
msm8x60_fluid_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{msm8x60_fluid_gsbi_configs, ARRAY_SIZE(msm8x60_fluid_gsbi_configs)},
	{msm8x60_ebi2_configs, ARRAY_SIZE(msm8x60_ebi2_configs)},
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
	{msm8x60_ts_configs, ARRAY_SIZE(msm8x60_ts_configs)},
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
//	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
	{msm8x60_amp_configs, ARRAY_SIZE(msm8x60_amp_configs)},
#endif
	{msm8x60_i2s_configs, ARRAY_SIZE(msm8x60_i2s_configs)},
#ifdef CONFIG_SENSORS_K3DH
	{msm8x60_accel_configs, ARRAY_SIZE(msm8x60_accel_configs)},
#endif
#ifdef CONFIG_GYRO_K3G
	{msm8x60_gyro_configs, ARRAY_SIZE(msm8x60_gyro_configs)},
#endif
	{msm8x60_tma300_configs, ARRAY_SIZE(msm8x60_tma300_configs)},
	{NULL, 0},
};
struct msm_gpiomux_configs
msm8x60_qrdc_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{msm8x60_ebi2_configs, ARRAY_SIZE(msm8x60_ebi2_configs)},
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
	{msm8x60_ts_configs, ARRAY_SIZE(msm8x60_ts_configs)},
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
//	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
	{msm8x60_amp_configs, ARRAY_SIZE(msm8x60_amp_configs)},
#endif
	{msm8x60_i2s_configs, ARRAY_SIZE(msm8x60_i2s_configs)},
#ifdef CONFIG_SENSORS_K3DH
	{msm8x60_accel_configs, ARRAY_SIZE(msm8x60_accel_configs)},
#endif
#ifdef CONFIG_GYRO_K3G
	{msm8x60_gyro_configs, ARRAY_SIZE(msm8x60_gyro_configs)},
#endif
	{msm_qrdc_usb_configs, ARRAY_SIZE(msm_qrdc_usb_configs)},
	{msm_qrdc_sdc_configs, ARRAY_SIZE(msm_qrdc_sdc_configs)},
	{NULL, 0},
};
struct msm_gpiomux_configs
msm8x60_charm_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
#ifdef CONFIG_MSM_GSBI9_UART
	{msm8x60_charm_uart_configs, ARRAY_SIZE(msm8x60_charm_uart_configs)},
#endif
	{msm8x60_ts_configs, ARRAY_SIZE(msm8x60_ts_configs)},
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
//	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
	{msm8x60_amp_configs, ARRAY_SIZE(msm8x60_amp_configs)},
#endif
	{msm8x60_i2s_configs, ARRAY_SIZE(msm8x60_i2s_configs)},
#ifdef CONFIG_SENSORS_K3DH
	{msm8x60_accel_configs, ARRAY_SIZE(msm8x60_accel_configs)},
#endif
#ifdef CONFIG_GYRO_K3G
	{msm8x60_gyro_configs, ARRAY_SIZE(msm8x60_gyro_configs)},
#endif
	{msm8x60_tmg200_configs, ARRAY_SIZE(msm8x60_tmg200_configs)},
	{msm8x60_charm_sdc_configs, ARRAY_SIZE(msm8x60_charm_sdc_configs)},
	{msm8x60_charm_configs, ARRAY_SIZE(msm8x60_charm_configs)},

#ifdef CONFIG_ISDBTMM
	{msm8x60_tmm_configs, ARRAY_SIZE(msm8x60_tmm_configs)},
#endif
	
#if defined(CONFIG_TDMB) || defined(CONFIG_TDMB_MODULE)
	{msm8x60_tdmb_configs, ARRAY_SIZE(msm8x60_tdmb_configs)},
#endif
	{NULL, 0},
};
struct msm_gpiomux_configs
msm8x60_p8_lte_gpiomux_cfgs[] __initdata = {
	{msm8x60_gsbi_configs, ARRAY_SIZE(msm8x60_gsbi_configs)},
	{p8_lte_usb_sel, ARRAY_SIZE(p8_lte_usb_sel)}, 
	{msm8x60_uart_configs, ARRAY_SIZE(msm8x60_uart_configs)},
#ifdef CONFIG_MSM_GSBI9_UART
	{msm8x60_charm_uart_configs, ARRAY_SIZE(msm8x60_charm_uart_configs)},
#endif
#if !defined(CONFIG_KOR_OPERATOR_SKT) && !defined(CONFIG_JPN_OPERATOR_NTT)
	{msm8x60_aux_pcm_configs, ARRAY_SIZE(msm8x60_aux_pcm_configs)},
#endif	
	{msm8x60_sdc_configs, ARRAY_SIZE(msm8x60_sdc_configs)},
	{msm8x60_snd_configs, ARRAY_SIZE(msm8x60_snd_configs)},
	{msm8x60_mi2s_configs, ARRAY_SIZE(msm8x60_mi2s_configs)},
#if !defined(CONFIG_KOR_OPERATOR_SKT) && !defined(CONFIG_JPN_OPERATOR_NTT)
	{msm8x60_lcdc_configs, ARRAY_SIZE(msm8x60_lcdc_configs)},
#endif	
//	{msm8x60_mdp_vsync_configs, ARRAY_SIZE(msm8x60_mdp_vsync_configs)},
	{msm8x60_hdmi_configs, ARRAY_SIZE(msm8x60_hdmi_configs)},
	{msm8x60_pmic_configs, ARRAY_SIZE(msm8x60_pmic_configs)},
//	{msm8x60_common_configs, ARRAY_SIZE(msm8x60_common_configs)},
	{msm8x60_cam_configs, ARRAY_SIZE(msm8x60_cam_configs)},
#if defined (CONFIG_SENSORS_YDA165) || defined (CONFIG_SENSORS_YDA160) || defined (CONFIG_SENSORS_MAX9879)|| defined (CONFIG_WM8994_AMP)
	{msm8x60_amp_configs, ARRAY_SIZE(msm8x60_amp_configs)},
#endif
	{msm8x60_i2s_configs, ARRAY_SIZE(msm8x60_i2s_configs)},
#ifdef CONFIG_SENSORS_K3DH
	{msm8x60_accel_configs, ARRAY_SIZE(msm8x60_accel_configs)},
#endif
#ifdef CONFIG_GYRO_K3G
	{msm8x60_gyro_configs, ARRAY_SIZE(msm8x60_gyro_configs)},
#endif
#ifdef CONFIG_CMC624_P8LTE
	{msm8x60_cmc624_configs, ARRAY_SIZE(msm8x60_cmc624_configs)},
#endif
	{msm8x60_charm_sdc_configs, ARRAY_SIZE(msm8x60_charm_sdc_configs)},
	{msm8x60_charm_configs, ARRAY_SIZE(msm8x60_charm_configs)},
	{msm8x60_mxt768e_configs, ARRAY_SIZE(msm8x60_mxt768e_configs)},	
//	{msm8x60_wlan_configs, ARRAY_SIZE(msm8x60_wlan_configs)},
	{msm8x60_motor_configs, ARRAY_SIZE(msm8x60_motor_configs)},
	{msm8x60_boot_configs, ARRAY_SIZE(msm8x60_boot_configs)},
	{msm8x60_nc_configs, ARRAY_SIZE(msm8x60_nc_configs)},

	{NULL, 0},
};


static DEFINE_SPINLOCK(msm_gpio_proc_lock);

static const char *gpiomux_drv_str[] = {
	"drv_2ma",
	"drv_4ma",
	"drv_6ma",
	"drv_8ma",
	"drv_10ma",
	"drv_12ma",
	"drv_14ma",
	"drv_16ma",
};

static const char *gpiomux_func_str[] = {
	"gpio",
	"func_1",
	"func_2",
	"func_3",
	"func_4",
	"func_5",
	"func_6",
	"func_7",
	"func_8",
	"func_9",
	"func_a",
	"func_b",
	"func_c",
	"func_d",
	"func_e",
	"func_f",
};

static const char *gpiomux_pull_str[] = {
	"pull_none",
	"pull_down",
	"pull_keeper",
	"pull_up",
};

static const char *gpiomux_dir_str[] = {
	"in",
	"out_high",
	"out_low",
};

#define SNPRINTF(buf, size, format, ...) \
	do { \
		if (size > 0) { \
			int ret; \
			ret = snprintf(buf, size, format, ## __VA_ARGS__); \
			if (ret > size) { \
				buf += size; \
				size = 0; \
			} else { \
				buf += ret; \
				size -= ret; \
			} \
		} \
	} while (0)

static unsigned int msm_gpio_proc_cnt;

static int msm_gpio_read_proc(char *page,
		char **start, off_t off, int count, int *eof, void *data)
{
	char *p = page;
	unsigned long flags;
	struct gpiomux_setting set;
	unsigned gpio;
	unsigned begin;

	spin_lock_irqsave(&msm_gpio_proc_lock, flags);

	if (count < 1024) {
		*start = (char *) 0;
		*eof = 0;
		spin_unlock_irqrestore(&msm_gpio_proc_lock, flags);
		return 0;
	}

	msm_gpio_proc_cnt = off ? msm_gpio_proc_cnt : 0;
	begin = msm_gpio_proc_cnt * 70;
	begin = begin ? begin + 1 : 0;

	for (gpio = begin; gpio < NR_GPIO_IRQS; ++gpio) {
		__msm_gpiomux_read(gpio, &set);
		SNPRINTF(p, count,
			"[gpio %u]\t%s\t%s\t%s\t%s\n", gpio,
			gpiomux_func_str[set.func],
			gpiomux_dir_str[set.dir],
			gpiomux_pull_str[set.pull],
			gpiomux_drv_str[set.drv]);
		if ((gpio - begin) > 69) {
			msm_gpio_proc_cnt++;
			break;
		}
	}

	if (gpio > (NR_GPIO_IRQS - 1))
		msm_gpio_proc_cnt++;

	*start = msm_gpio_proc_cnt > 2 ? (char *) 0 : (char *) 1;
	*eof = 1;

	spin_unlock_irqrestore(&msm_gpio_proc_lock, flags);

	return p - page;
}

void __init msm8x60_init_gpiomux(struct msm_gpiomux_configs *cfgs)
{
	int rc;
	struct proc_dir_entry *d_entry;

	rc = msm_gpiomux_init(NR_GPIO_IRQS);
	if (rc) {
		pr_err("%s failure: %d\n", __func__, rc);
		return;
	}

	while (cfgs->cfg) {
		msm_gpiomux_install(cfgs->cfg, cfgs->ncfg);
		++cfgs;
	}

	d_entry = create_proc_entry("msm_gpio_conf",
			S_IRUGO, NULL);
	if (d_entry) {
		d_entry->read_proc = msm_gpio_read_proc;
		d_entry->write_proc = NULL;
		d_entry->data = NULL;
	}

}

static struct msm_gpiomux_config msm8x60_lpm_uart_configs[] __initdata = {
	{ /* UART9DM  RX */
		.gpio	   = 66,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{ /* UART9DM TX */
		.gpio	   = 67,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio	   = 68,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	{
		.gpio	   = 69,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
};

static struct msm_gpiomux_config msm8x60_lpm_configs[] __initdata = {
	/* AP2MDM_WAKEUP */
	{
		.gpio = 135,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* MDM2AP_VFR */
	{
		.gpio = 29,
		.settings = {
			[GPIOMUX_ACTIVE] = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* AP2MDM_STATUS */
	{
		.gpio = 136,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* MDM2AP_STATUS */
	{
		.gpio = 134,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* MDM2AP_WAKEUP */
	{
		.gpio = 40,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* MDM2AP_ERRFATAL */
	{
		.gpio = 133,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* AP2MDM_ERRFATAL */
	{
		.gpio = 93,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* AP2MDM_KPDPWR_N */
	{
		.gpio = 132,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	},
	/* AP2MDM_PMIC_RESET_N */
	{
		.gpio = 131,
		.settings = {
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		}
	}
};

static struct msm_gpiomux_config msm8x60_lpm_sdc_configs[] __initdata = {
	/* SDCC5 cmd */
	{
		.gpio = 95,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC5 data[3]*/
	{
		.gpio = 96,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC5 clk */
	{
		.gpio = 97,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC5 data[2]*/
	{
		.gpio = 98,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC5 data[1]*/
	{
		.gpio = 99,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC5 data[0]*/
	{
		.gpio = 100,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* MDM2AP_SYNC */
	{
		.gpio = 129,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},

	/* MDM2AP_VDDMIN */
	{
		.gpio = 140,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[0] */
	{
		.gpio = 143,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[1] */
	{
		.gpio = 144,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[2] */
	{
		.gpio = 145,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[3] */
	{
		.gpio = 146,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[4] */
	{
		.gpio = 147,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[5] */
	{
		.gpio = 148,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[6] */
	{
		.gpio = 149,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 data[7] */
	{
		.gpio = 150,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
	/* SDCC2 CMD */
	{
		.gpio = 151,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},

	/* SDCC2 CLK */
	{
		.gpio = 152,
		.settings = {
			[GPIOMUX_ACTIVE]    = &nc_cfg,
			[GPIOMUX_SUSPENDED] = &nc_cfg,
		},
	},
};

static struct msm_gpiomux_configs
msm8x60_orig_gpiomux_cfgs_for_lpm[] __initdata = {
	{msm8x60_charm_uart_configs, ARRAY_SIZE(msm8x60_charm_uart_configs)},
	{msm8x60_charm_sdc_configs, ARRAY_SIZE(msm8x60_charm_sdc_configs)},
	{msm8x60_charm_configs, ARRAY_SIZE(msm8x60_charm_configs)},
	{NULL, 0},
};

static struct msm_gpiomux_configs
msm8x60_new_gpiomux_cfgs_for_lpm[] __initdata = {
	{msm8x60_lpm_uart_configs, ARRAY_SIZE(msm8x60_lpm_uart_configs)},
	{msm8x60_lpm_sdc_configs, ARRAY_SIZE(msm8x60_lpm_sdc_configs)},
	{msm8x60_lpm_configs, ARRAY_SIZE(msm8x60_lpm_configs)},
	{NULL, 0},
};

void __init msm8x60_init_gpiomux_cfg_for_lpm(struct msm_gpiomux_configs *cfgs)
{
	struct msm_gpiomux_configs *gpiomux_cfgs = cfgs;
	struct msm_gpiomux_configs *orig_cfgs = msm8x60_orig_gpiomux_cfgs_for_lpm;
	struct msm_gpiomux_configs *new_cfgs = msm8x60_new_gpiomux_cfgs_for_lpm;

	while (cfgs->cfg) {
		if (cfgs->cfg == orig_cfgs->cfg) {
			cfgs->cfg = new_cfgs->cfg;
			cfgs->ncfg = new_cfgs->ncfg;
			orig_cfgs++;
			new_cfgs++;
		}
		cfgs++;
	}

	msm8x60_init_gpiomux(gpiomux_cfgs);
}

