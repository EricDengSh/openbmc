#ifndef __HAL_GPIO_DEF_H__
#define __HAL_GPIO_DEF_H__

//EVENT
#define FM_UARTSW_LSB_N          "FM_UARTSW_LSB_N"
#define FM_UARTSW_MSB_N          "FM_UARTSW_MSB_N"
#define FM_POST_CARD_PRES_N      "FM_POST_CARD_PRES_N"
#define IRQ_UV_DETECT_N          "UV_ALERT_N"
#define IRQ_OC_DETECT_N          "UV_ALERT_N"
#define IRQ_HSC_FAULT_N          "IRQ_HSC_FAULT_R1_N"
#define IRQ_HSC_ALERT_N          "IRQ_SML1_PMBUS_ALERT_N"
#define FM_CPU_CATERR_N          "H_CPU_CATERR_LVC2_R2_N"
#define FM_CPU0_PROCHOT_N        "FM_CPU0_PROCHOT_R_N_reg"
#define FM_CPU1_PROCHOT_N        "FM_CPU1_PROCHOT_R_N_reg"
#define FM_CPU0_THERMTRIP_N      "CPU0_THERMTRIP_R_N"
#define FM_CPU1_THERMTRIP_N      "CPU1_THERMTRIP_R_N"
#define FM_CPU_ERR0_N            "FM_CPU0_SMERR_N"
#define FM_CPU_ERR1_N            "FM_CPU1_SMERR_N"
#define FM_CPU_ERR2_N            "FM_CPU2_SMERR_N"
#define FM_CPU0_MEM_HOT_N        "H_CPU0_MEMHOT_OUT_LVC1_N"
#define FM_CPU1_MEM_HOT_N        "H_CPU1_MEMHOT_OUT_LVC1_N"
#define FM_CPU0_MEM_THERMTRIP_N  "H_CPU0_MEMTRIP_LVC1_N"
#define FM_CPU1_MEM_THERMTRIP_N  "H_CPU1_MEMTRIP_LVC1_N"
#define FM_PCH_THERMTRIP_N       "FM_PCH_BMC_THERMTRIP_N"
#define FM_SYS_THROTTLE          "FM_THROTTLE_R_N"
#define FM_CPU0_VCCIN_VR_HOT     "IRQ_CPU0_VRHOT_N"
#define FM_CPU1_VCCIN_VR_HOT     "IRQ_CPU1_VRHOT_N"
#define FM_CPU0_VCCD_VR_HOT      "IRQ_PVCCD_CPU0_VRHOT_LVC3_N"
#define FM_CPU1_VCCD_VR_HOT      "IRQ_PVCCD_CPU0_VRHOT_LVC3_N"
#define FM_CPU0_SKTOCC           "FM_PRSNT_CPU0_R_N"
#define FM_CPU1_SKTOCC           "FM_PRSNT_CPU1_R_N"

//Power Control
#define FM_LAST_PWRGD            "FM_PWRGD_CPU1_PWROK"
#define RST_PLTRST_N             "FM_RST_CPU1_RESETL_N"
#define FP_RST_BTN_IN_N          "ID_RST_BTN_BMC_IN"
#define FP_PWR_BTN_IN_N          "SYS_BMC_PWRBTN_IN"
#define FP_PWR_BTN_OUT_N         "SYS_BMC_PWRBTN_OUT"
#define FP_RST_BTN_OUT_N         "RST_BMC_RSTBTN_OUT_R_N"

#define BIC_READY                "FM_SWB_BIC_READY_ISO_R_N"
#define GPU_FPGA_RST_N           "GPU_FPGA_RST_N"

#endif
