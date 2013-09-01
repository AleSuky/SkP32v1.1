/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "SD-SPI.h"

#define BLOCK_SIZE	512
/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;
	MEDIA_INFORMATION *inf_sd;
	
	(void)pdrv;	
	MDD_SDSPI_InitIO();
	inf_sd=MDD_SDSPI_MediaInitialize();
	if(inf_sd->errorCode==MEDIA_NO_ERROR){
		stat=RES_OK;
	}else{
		stat=STA_NOINIT;
	}
	
	return stat;
}

/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber (0..) */
)
{
	DSTATUS stat;
	(void)pdrv;	
	if(MDD_SDSPI_MediaDetect()==TRUE){
		stat=RES_OK;
	}else{
		stat=STA_NODISK;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
	DRESULT res=RES_OK;
	BYTE status;
	(void)pdrv;	
	
	while(count--){
		status=MDD_SDSPI_SectorRead(sector,buff);
		if(status!=TRUE){
			res=RES_ERROR;
			break;
		}
		buff+=BLOCK_SIZE;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber (0..) */
	BYTE *buff,			/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	DRESULT res=RES_OK;
	BYTE status;
	(void)pdrv;	
	
	while(count--){
		status=MDD_SDSPI_SectorWrite(sector,buff,TRUE);
		if(status!=TRUE){
			res=RES_ERROR;
			break;
		}
		buff+=BLOCK_SIZE;
	}	
	return res;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	(void)pdrv;	
	(void)cmd;
	(void)buff;		

	return RES_OK;;
}
#endif

/*-----------------------------------------------------------------------*/
/* Get current time                                                      */
/*-----------------------------------------------------------------------*/
DWORD get_fattime(void){
        return 0;
}
