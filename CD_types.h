////////////////////////////////////////////////////////////////////////////
////        (C) Copyright Dario Cortese                                 ////
//// This source code may only be used by Dario Cortese licensed users  ////
//// This source code may only be distributed to Dario Cortese licensed ////
//// users.  No other use, reproduction  or distribution is permitted   ////
//// without written permission.                                        ////
////                                                                    ////
//// Author: Dario Cortese                                              ////
//// Client: myself                                                     ////
//// User: Dario Cortese                                                ////
//// Created on 26/01/2012  upodated 01/11/2015                         ////
//// File: CD_types.h                                                   ////
//// Description:                                                       ////
////    This file has the generic variable type, structure definition   ////
////      used in my developed code.                                    ////
////    I use this types to isolate my code from processor specific     ////
////      data size                                                     ////
////////////////////////////////////////////////////////////////////////////


#ifndef _CD_TYPES_H_
#define _CD_TYPES_H_

#ifdef DOXYGEN
    #define section( YY )
#endif

//PLEASE INDICATE THE COMPILER
#define  COMPILER_CCS
//#define  COMPILER_MICROCHIP
//#define COMPILER_VISUALDSP

//PLEASE INDICATE PLATFORM OR PROCESSOR FAMILY
//#define PLATFORM_PIC32
//#define PLATFORM_PIC24
#define PLATFORM_PICxx


#ifdef PLATFORM_PICxx
   //#define TRUE   TRUE
   //#define FALSE  FALSE
   #define NULL   0
   #ifdef COMPILER_CCS
      typedef unsigned int8   uint8_t;
      typedef signed int8     sint8_t;
      typedef unsigned int16  uint16_t;
      typedef signed int16    sint16_t;
      typedef unsigned int32  uint32_t;
      typedef signed int32    sint32_t;
      typedef float32         float32_t;
      typedef signed int8     sint_t;
      typedef unsigned int8   uint_t;
   #endif //COMPILER_CCS
#endif //PLATFORM_PICxx



//little-endian bytes ordering
typedef union uniInt8{
   uint8_t i8;
   struct{
      uint8_t Nibble0:4;
      uint8_t Nibble1:4;
   }i4log;
   struct{
      uint8_t bit0:1;
      uint8_t bit1:1;
      uint8_t bit2:1;
      uint8_t bit3:1;
      uint8_t bit4:1;
      uint8_t bit5:1;
      uint8_t bit6:1;
      uint8_t bit7:1;
   }bits;
}TuniInt8_t; //union uniInt8


//little-endian bytes ordering
typedef union uniInt16{
   uint16_t i16;
   uint8_t i8[2];
   struct{
      uint8_t low;
      uint8_t high;
   }i8log;
   struct{
      uint16_t bit0:1;
      uint16_t bit1:1;
      uint16_t bit2:1;
      uint16_t bit3:1;
      uint16_t bit4:1;
      uint16_t bit5:1;
      uint16_t bit6:1;
      uint16_t bit7:1;
      uint16_t bit8:1;
      uint16_t bit9:1;
      uint16_t bit10:1;
      uint16_t bit11:1;
      uint16_t bit12:1;
      uint16_t bit13:1;
      uint16_t bit14:1;
      uint16_t bit15:1;
   }bits;
}TuniInt16_t; //end union uniInt16


//little-endian bytes ordering
typedef union uniInt32{
   uint32_t i32;
   struct{
      uint16_t i16low;
      uint16_t i16high;   
   }i16log;      //logical
   uint16_t i16[2];

   struct{
      uint8_t lower;
      uint8_t low;
      uint8_t high;
      uint8_t higher;
   }i8log;      //logical 
   uint8_t i8[4];

   struct{
      uint32_t bit0:1;
      uint32_t bit1:1;
      uint32_t bit2:1;
      uint32_t bit3:1;
      uint32_t bit4:1;
      uint32_t bit5:1;
      uint32_t bit6:1;
      uint32_t bit7:1;
      uint32_t bit8:1;
      uint32_t bit9:1;
      uint32_t bit10:1;
      uint32_t bit11:1;
      uint32_t bit12:1;
      uint32_t bit13:1;
      uint32_t bit14:1;
      uint32_t bit15:1;
      uint32_t bit16:1;
      uint32_t bit17:1;
      uint32_t bit18:1;
      uint32_t bit19:1;
      uint32_t bit20:1;
      uint32_t bit21:1;
      uint32_t bit22:1;
      uint32_t bit23:1;
      uint32_t bit24:1;
      uint32_t bit25:1;
      uint32_t bit26:1;
      uint32_t bit27:1;
      uint32_t bit28:1;
      uint32_t bit29:1;
      uint32_t bit30:1;
      uint32_t bit31:1;
   }bits;
}TuniInt32_t; //end union uniInt32


#endif //_CD_TYPES_H_
