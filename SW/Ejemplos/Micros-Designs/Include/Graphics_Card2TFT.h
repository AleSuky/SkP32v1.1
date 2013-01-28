/**
   \version: 1.1


   \author Suky
   \web www.micros-designs.com.ar
   \date 22/11/11


///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////                                                                   ////
////        (C) Copyright 2011 www.micros-designs.com.ar               ////
//// Este código puede ser usado, modificado y distribuido libremente  ////
//// sin eliminar esta cabecera y  sin garantía de ningún tipo.        ////
////                                                                   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////

 *- Version Log --------------------------------------------------------------*
 *   Fecha       Autor                Comentarios                             *
 *----------------------------------------------------------------------------*
 * 22/11/11      Suky               Original (Rev 1.0)                        *
 * 29/11/11		 Suky				Se agrega vCreateFileBMP24bits(...)		  *
 *----------------------------------------------------------------------------* */
#include "LCDTFT.h"
#include "MDD File System/FSIO.h"

#define JUST_IZQ		0
#define JUST_DER		1
#define JUST_CENTRADO 	2

void vDrawImageSDBMP24Bits(const CHAR8 *NameImagen);
void vDrawReloj(void);
void vCreateFileBMP24bits(const CHAR8 *Name);
