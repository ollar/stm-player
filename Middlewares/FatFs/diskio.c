/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2025        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"

#include "ff.h" /* Basic definitions of FatFs */

#include "diskio.h" /* Declarations FatFs MAI */
#include "sd_card_spi.h"

static DSTATUS disk_status_flag = STA_NOINIT; // 0x01 = не инициализирован

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status(BYTE pdrv /* Physical drive nmuber to identify the drive */
) {
  if (pdrv != 0)
    return STA_NOINIT;

  return disk_status_flag;
}

/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS
disk_initialize(BYTE pdrv /* Physical drive nmuber to identify the drive */
) {
  if (pdrv != 0)
    return STA_NOINIT;

  if (SD_init() == HAL_OK) {
    disk_status_flag &= ~STA_NOINIT;

    return disk_status_flag;
  }

  disk_status_flag |= STA_NOINIT;

  return disk_status_flag;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read(BYTE pdrv,  /* Physical drive nmuber to identify the drive */
                  BYTE *buff, /* Data buffer to store read data */
                  LBA_t sector, /* Start sector in LBA */
                  UINT count    /* Number of sectors to read */
) {
  if (pdrv != 0 || buff == NULL || count == 0) {
    return RES_PARERR; // Параметры неверные
  }

  // Проверяем, инициализирован ли диск
  if (disk_status_flag & STA_NOINIT) {
    return RES_NOTRDY; // Диск не готов
  }

  if (SD_ReadBlocks_DMA(sector, buff, count) == HAL_OK) {
    // if (SD_ReadBlocks_CPU(sector, buff, count) == HAL_OK) {
    return RES_OK; // Успешно
  } else {
    return RES_ERROR; // Ошибка чтения
  }
}

/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write(BYTE pdrv, /* Physical drive nmuber to identify the drive */
                   const BYTE *buff, /* Data to be written */
                   LBA_t sector,     /* Start sector in LBA */
                   UINT count        /* Number of sectors to write */
) {
  DRESULT res;
  int result;

  switch (pdrv) {
  case DEV_RAM:
    // translate the arguments here

    result = RAM_disk_write(buff, sector, count);

    // translate the reslut code here

    return res;

  case DEV_MMC:
    // translate the arguments here

    result = MMC_disk_write(buff, sector, count);

    // translate the reslut code here

    return res;

  case DEV_USB:
    // translate the arguments here

    result = USB_disk_write(buff, sector, count);

    // translate the reslut code here

    return res;
  }

  return RES_PARERR;
}

#endif

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl(BYTE pdrv, /* Physical drive nmuber (0..) */
                   BYTE cmd,  /* Control code */
                   void *buff /* Buffer to send/receive control data */
) {
  switch (cmd) {
  case GET_SECTOR_COUNT:
    // Возвращаем общее количество секторов на карте
    *(DWORD *)buff = SD_GetSectorCount();
    break;
  case GET_SECTOR_SIZE:
    // Возвращаем размер сектора (обычно 512 байт)
    *(WORD *)buff = 512;
    break;
  case GET_BLOCK_SIZE:
    // Возвращаем размер блока для операций стирания (обычно 1)
    *(DWORD *)buff = 1;
    break;
  case CTRL_SYNC:
    // Синхронизация кэша (для записи)
    // При чтении ничего не делаем
    break;
  default:
    return RES_PARERR;
  }
  return RES_OK;
}
