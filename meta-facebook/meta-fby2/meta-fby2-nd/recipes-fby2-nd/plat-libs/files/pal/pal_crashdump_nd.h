/*
 * Copyright 2015-present Facebook. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __PAL_CRASHDUMP_ND_H__
#define __PAL_CRASHDUMP_ND_H__

#include <stdint.h>


#define CRASHDUMP_ND_BIN       "/usr/local/bin/crashdump_amd.sh --event"      
#define MAX_CRASHDUMP_FILE_NAME_LENGTH 128
#define MAX_VAILD_LIST_LENGTH 128
#define NDCRD_CMD_HEADER_LENGTH 4
#define NDCRD_BANK_HEADER_LENGTH 4
#define NDCRD_HEADER_LENGTH (NDCRD_CMD_HEADER_LENGTH+NDCRD_BANK_HEADER_LENGTH)
#define MCA_DECODED_LOG_PATH "/tmp/crashdump_slot%d_mca"
#define CRASHDUMP_PID_PATH "/var/run/autodump%d.pid"
#define CRASHDUMP_TIMESTAMP_FILE "fru%d_crashdump"

#define CPU_WDT_CCM_NUM 8
#define WDT_NBIO_NUM 4

enum NDCRD_DATA_TYPE{
  TYPE_MCA_BANK       = 0x01,
  TYPE_VIRTUAL_BANK   = 0x02,
  TYPE_CPU_WDT_BANK   = 0x03,
  TYPE_WDT_ADDR_BANK  = 0x04,
  TYPE_WDT_DATA_BANK  = 0x05,

  TYPE_CONTROL_PKT    = 0x80,
};

enum NDCRD_CTRL_CMD {
  NDCRD_CTRL_GET_STATE      = 0x01,
  NDCRD_CTRL_DUMP_FINIDHED  = 0x02,
};

enum NDCRD_CTRL_STATE {
  NDCRD_CTRL_BMC_FREE       = 0x01,
  NDCRD_CTRL_BMC_WAIT_DATA  = 0x02,
  NDCRD_CTRL_BMC_PACK       = 0x03,
};


typedef struct {
  uint8_t bank_id;
  uint8_t core_id;
} __attribute__((packed)) ndcrd_bank_core_id_t;

typedef struct {
  uint8_t count;
  ndcrd_bank_core_id_t list[MAX_VAILD_LIST_LENGTH];
} __attribute__((packed)) ndcrd_mca_recv_list_t;

//==============================================================================
// Crashdump Command Header
//==============================================================================
typedef struct {
  uint8_t cmd_ver;
  uint8_t reserved[3];
} __attribute__((packed)) ndcrd_cmd_hdr_t;

//==============================================================================
// Crashdump Bank Header
//==============================================================================
typedef struct {
  uint8_t bank_type;
  uint8_t bank_fmt_ver;
  union { /* bank data */
    struct { /* mca_bank (type 1) */
      uint8_t bank_id;
      uint8_t core_id;
    } __attribute__((packed));

    struct { /* other type */
      uint8_t reserved[2];
    } __attribute__((packed));
  };
} __attribute__((packed)) ndcrd_bank_hdr_t;

//==============================================================================
// Crashdump Header
//==============================================================================
typedef struct {
  ndcrd_cmd_hdr_t cmd_hdr;
  ndcrd_bank_hdr_t bank_hdr;
} __attribute__((packed)) ndcrd_hdr_t;




//==============================================================================
// Type 0x01: MCA Bank
//==============================================================================
typedef struct {
  uint32_t mca_ctrl_lf;
  uint32_t mca_ctrl_hf;
  uint32_t mca_status_lf;
  uint32_t mca_status_hf;
  uint32_t mca_addr_lf;
  uint32_t mca_addr_hf;
  uint32_t mca_misc0_lf;
  uint32_t mca_misc0_hf;
  uint32_t mca_ctrl_mask_lf;
  uint32_t mca_ctrl_mask_hf;
  uint32_t mca_config_lf;
  uint32_t mca_config_hf;
  uint32_t mca_ipid_lf;
  uint32_t mca_ipid_hf;
  uint32_t mca_synd_lf;
  uint32_t mca_synd_hf;
  uint32_t mca_destat_lf;
  uint32_t mca_destat_hf;
  uint32_t mca_deaddr_lf;
  uint32_t mca_deaddr_hf;
  uint32_t mca_misc1_lf;
  uint32_t mca_misc1_hf;
} __attribute__((packed)) ndcrd_mca_bank_t;

//==============================================================================
// Type 0x02: Virtual/Global Bank
//==============================================================================
typedef struct {
  uint32_t bank_s5_reset_status;
  uint32_t bank_breakevent;
  uint16_t valid_mca_count;
  ndcrd_bank_core_id_t valid_mca_list[1];
} __attribute__((packed)) ndcrd_virtual_bank_t;

//==============================================================================
// Type 0x02 (ver 2): Virtual/Global Bank v2
//==============================================================================
typedef struct {
  uint32_t bank_s5_reset_status;
  uint32_t bank_breakevent;
  uint16_t valid_mca_count;

  // version 2 specific data
  uint16_t process_num;
  uint32_t apic_id;
  uint32_t eax;
  uint32_t ebx;
  uint32_t ecx;
  uint32_t edx;

  ndcrd_bank_core_id_t valid_mca_list[1];
} __attribute__((packed)) ndcrd_virtual_bank_v2_t;

//==============================================================================
// Type 0x03: CPU/Data Fabric Watchdog Timer bank
//==============================================================================
typedef struct {
  uint32_t hw_assert_sts_hi[CPU_WDT_CCM_NUM];
  uint32_t hw_assert_sts_low[CPU_WDT_CCM_NUM];
  uint32_t rspq_wdt_io_trans_log_hi[CPU_WDT_CCM_NUM];
  uint32_t rspq_wdt_io_trans_log_low[CPU_WDT_CCM_NUM];
} __attribute__((packed)) ndcrd_cpu_wdt_bank_t;

//==============================================================================
// Type 0x04: SMU/PSP/PTDMA Watchdog Timers address bank
//------------------------------------------------------------------------------
// SHUB_MPX_LAST_XXREQ_LOG_ADDR [XX] [YY]
//------------------------------------------------------------------------------
// XX:  NBIO0 - NBIO3
// YY:  0-> ShubMp0WrTimeoutDetected
//      1-> ShubMp0RdTimeoutDetected
//      2-> ShubMp1WrTimeoutDetected
//      3-> ShubMp1RdTimeoutDetected
//==============================================================================
typedef struct {
  uint32_t addr[WDT_NBIO_NUM][4];
} __attribute__((packed)) ndcrd_wdt_addr_bank_t;

//==============================================================================
// Type 0x05: SMU/PSP/PTDMA Watchdog Timers data bank
//------------------------------------------------------------------------------
// SHUB_MPX_LAST_XXREQ_LOG_DATA [XX] [YY] [ZZ]
//------------------------------------------------------------------------------
// XX:  NBIO0 - NBIO3
// YY:  0-> ShubMp0WrTimeoutDetected
//      1-> ShubMp0RdTimeoutDetected
//      2-> ShubMp1WrTimeoutDetected
//      3-> ShubMp1RdTimeoutDetected
// ZZ:  Data0 - Data2
//==============================================================================
typedef struct {
  uint32_t data[WDT_NBIO_NUM][4][3];
} __attribute__((packed)) ndcrd_wdt_data_bank_t;

//==============================================================================
// Type 0x80: Control Packet
//==============================================================================
typedef struct {
  uint8_t cmd;
} __attribute__((packed)) ndcrd_ctrl_pkt_t;


uint8_t crashdump_initial(uint8_t slot);
uint8_t pal_ndcrd_save_mca_to_file(uint8_t slot, uint8_t* req_data, uint8_t req_len, uint8_t* res_data, uint8_t* res_len);

#endif /* __PAL_CRASHDUMP_ND_H__ */