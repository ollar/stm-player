#pragma once

#include "diskio.h"
#include "ff.h"
#include "usbh_core.h"
#include "usbh_msc.h"

#define APP_FILE_DUMP_LIMIT 512U /* bytes of file content to dump */

typedef enum {
  APPLICATION_IDLE,
  APPLICATION_READY,
  APPLICATION_DISCONNECT
} ApplicationTypeDef;

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id);

static void usb_read_demo(void);
HAL_StatusTypeDef usb_init(void);
void usb_process(void);

DSTATUS USBH_MSC_status(BYTE pdrv);
DSTATUS USBH_MSC_initialize(BYTE pdrv);
DRESULT USBH_MSC_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count);
DRESULT USBH_MSC_ioctl(BYTE pdrv, BYTE cmd, void *buff);
