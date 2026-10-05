// #include "ff.h"
#include "usb_utils.h"
#include "usart_init.h"

USBH_HandleTypeDef hUsb_Host;

static ApplicationTypeDef Appli_state = APPLICATION_IDLE;
static volatile uint8_t usb_ready = 0;
static BYTE g_lun = 0;

// static FATFS fs;
// static FIL fil;

static void USBH_UserProcess(USBH_HandleTypeDef *phost, uint8_t id) {
  switch (id) {
  case HOST_USER_CONNECTION:
    hprintf("\r\n[USB] Device connected\r\n");
    usb_ready = 0;
    Appli_state = APPLICATION_IDLE;
    break;

  case HOST_USER_DISCONNECTION:
    hprintf("\r\n[USB] Device disconnected\r\n");
    usb_ready = 0;
    (void)f_mount(NULL, "", 0); /* invalidate volume */
    Appli_state = APPLICATION_DISCONNECT;
    break;

  case HOST_USER_CLASS_ACTIVE:
    hprintf("[USB] MSC class active\r\n");
    usb_ready = 1; /* LUN is fully initialized: capacity known, unit MSC_IDLE */
    break;

  default:
    break;
  }
}

// static void usb_read_demo(void) {
//   DIR dir;
//   FRESULT res;
//   FRESULT fr;
//   FILINFO finfo;
//   UINT br;
//   FIL fil;
//
//   hprintf("[FS] Mounting volume...\r\n");
//   res = f_mount(&fs, "", 1); /* mount immediately */
//   if (res != FR_OK) {
//     hprintf_formatted("[FS] Mount failed: %d\r\n", (int)res);
//     return;
//   }
//   hprintf("[FS] Mounted\r\n");
//
//   res = f_opendir(&dir, "0:/");
//
//   if (res != FR_OK) {
//     hprintf("[FS] dir read error\r\n");
//     return;
//   }
//
//   while (1) {
//     res = f_readdir(&dir, &finfo);
//     if (res != FR_OK || finfo.fname[0] == 0)
//       break;
//
//     hprintf_formatted("file name %s\r\n", finfo.fname);
//   }
//
//   f_closedir(&dir);
//
//   char *filename = "11.wav";
//
//   fr = f_open(&fil, filename, FA_READ);
//
//   uint8_t header_buffer[256];
//
//   f_read(&fil, header_buffer, 256, &br);
//
//   hprintf_formatted("%s\r\n", header_buffer);
//
//   f_close(&fil);
// }

void (*handle_usb_ready)(void) = &handle_usb_ready_dummy;
void (*handle_usb_user_disconnected)(void) =
    &handle_usb_user_disconnected_dummy;

HAL_StatusTypeDef usb_init(void (*new_handle_usb_ready)(void),
                           void (*new_handle_usb_user_disconnected)(void)) {
  if (USBH_Init(&hUsb_Host, USBH_UserProcess, 0) != USBH_OK) {
    return HAL_ERROR;
  }

  USBH_RegisterClass(&hUsb_Host, USBH_MSC_CLASS);
  USBH_Start(&hUsb_Host);

  handle_usb_ready = new_handle_usb_ready;
  handle_usb_user_disconnected = new_handle_usb_user_disconnected;

  return HAL_OK;
}

void usb_process() {
  USBH_Process(&hUsb_Host);

  if (usb_ready && (Appli_state == APPLICATION_IDLE)) {
    handle_usb_ready();
    Appli_state = APPLICATION_READY;
  }

  if (!usb_ready && (Appli_state == APPLICATION_DISCONNECT)) {
    // TODO: unmount fs
    // check this
  }
}

// =============================================================== FatFs hooks
// ===========================================================================

DSTATUS USBH_MSC_status(BYTE pdrv) {
  DSTATUS stat = STA_NOINIT;

  if (USBH_MSC_UnitIsReady(&hUsb_Host, g_lun) == 1) {
    stat &= ~STA_NOINIT;
  }

  return stat;
}

DSTATUS USBH_MSC_initialize(BYTE pdrv) {
  DSTATUS stat;

  stat = USBH_MSC_status(pdrv);

  return stat;
}

DRESULT USBH_MSC_read(BYTE pdrv, BYTE *buff, LBA_t sector, UINT count) {
  DRESULT res = RES_ERROR;
  USBH_StatusTypeDef status = USBH_OK;
  MSC_LUNTypeDef info;

  status = USBH_MSC_Read(&hUsb_Host, g_lun, sector, buff, count);

  if (status == USBH_OK) {
    res = RES_OK;
  } else {
    USBH_MSC_GetLUNInfo(&hUsb_Host, g_lun, &info);

    switch (info.sense.asc) {
    case SCSI_ASC_LOGICAL_UNIT_NOT_READY:
    case SCSI_ASC_MEDIUM_NOT_PRESENT:
    case SCSI_ASC_NOT_READY_TO_READY_CHANGE:
      res = RES_NOTRDY;
      break;

    default:
      res = RES_ERROR;
      break;
    }
  }

  return res;
}

DRESULT USBH_MSC_ioctl(BYTE pdrv, BYTE cmd, void *buff) {
  DRESULT res = RES_ERROR;
  MSC_LUNTypeDef info;

  switch (cmd) {
  /* Make sure that no pending write process */
  case CTRL_SYNC:
    res = RES_OK;
    break;

  /* Get number of sectors on the disk (DWORD) */
  case GET_SECTOR_COUNT:
    if (USBH_MSC_GetLUNInfo(&hUsb_Host, g_lun, &info) == USBH_OK) {
      *(DWORD *)buff = info.capacity.block_nbr;
      res = RES_OK;
    }
    break;

  /* Get R/W sector size (WORD) */
  case GET_SECTOR_SIZE:
    if (USBH_MSC_GetLUNInfo(&hUsb_Host, g_lun, &info) == USBH_OK) {
      *(WORD *)buff = info.capacity.block_size;
      res = RES_OK;
    }
    break;

  /* Get erase block size in unit of sector (DWORD) */
  case GET_BLOCK_SIZE:
    if (USBH_MSC_GetLUNInfo(&hUsb_Host, g_lun, &info) == USBH_OK) {
      *(DWORD *)buff = info.capacity.block_size / 512U;
      res = RES_OK;
    }
    break;

  default:
    res = RES_PARERR;
    break;
  }

  return res;
}

// ===========================================================================
// =============================================================== FatFs hooks
