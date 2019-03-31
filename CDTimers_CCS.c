////////////////////////////////////////////////////////////////////////////
////        (C) Copyright Dario Cortese                                 ////
//// This source code may only be used by Dario Cortese licensed users  ////
//// This source code may only be distributed to Dario Cortese licensed ////
//// users.  No other use, reproduction  or distribution is permitted   ////
//// without written permission.                                        ////
////                                                                    ////
//// Author: Dario Cortese                                              ////
//// Client: Mongoose srl (Mariano Cerbone)                             ////
//// Created on 26/08/2012                                              ////
//// Modify on 12/05/2018 to be adapted at CCS compiler                 ////
//// File: cdtimers_CCS.c                                               ////
//// Description:                                                       ////
//// THIS FILE HAS ALL IMPLEMENTATION OF FUNCTIONS USED FOR CDTIMERS    ////
////   MANAGING; TIMERS ARE USED WITH CDTHREAD, AND VICEVERSA           ////        
////////////////////////////////////////////////////////////////////////////

#ifndef _CDTIMERS_C_
#define _CDTIMERS_C_

#include "CDThread.h"

//enable this define if you want that will be stored 8 time-stamp in cdtimer_GetTicks
//#define _CDTIMERS_DEBUG_

cdTimerID Absolute_timer;

#ifdef _CDTIMERS_DEBUG_
    unsigned int Tim1idx=0;
    unsigned int8 Tim1Vals[8];
#endif


//typedef union{
//    unsigned int8 u8;
//    struct{
//    int8 TxCKPS:2;       //bits 0-1//0=1:1, 1=1:4, 2=1:16, 3=1:64
//    int8 TMRxON:1;      //bit 2   //0=off, 1=on
//    int8 TxOUTPUTS:4;   //bits 3-6//0=1:1, 1=1:2, .... 15=1:16
//    int8 N_U:1;         //bit 7   //not used
//    } bitfield;
//}SFR_TMR246_t;


//common variable for update_absolute_timer   
uint16_t cmn_update_prev_TMR = 0;

//it uses TIM4 and a global variable u32_SysTicks to increments my system timer
// every one ticks is equal to 1/125KHz= 8us
//calls almost every 2,048ms

/*! \fn void Update_Absolute_Timer()
   \author Dario Cortese
   \date 01-11-2015 modified 08-02-2019
   \brief this function is called by main loop user, or some interrupts, to update Absolute_timer global variable.
   Actually it uses TMR1 as time counter, with external 32768Hz quartz and so a timeout/isr every 2 seconds.
   \n Absolute timer has 131072 seconds as timeout that is 1.517 days, or 1 day and 12 hours 24 minutes 32 seconds
   \n for the reason that a so limited time isn't a good choice for a project that stay operative for many days that
 * \n has been created another timer that count only seconds, the UNIXtimer
   \return none, but update Absolute_timer global variable
   \warning this function must be redefined on different hardware or implementation
   \version 1.00
   \see cdtimer_INIT
*/
void Update_Absolute_Timer()
{
    uint16_t act_TMR;
    uint16_t delta;

    act_TMR = get_timer1();
    delta = act_TMR - cmn_update_prev_TMR; //now is delta ticks
    cmn_update_prev_TMR = act_TMR;
    //add delta to global u32_SysTicks
    Absolute_timer += delta;

#ifdef _CDTIMERS_DEBUG_
    Tim1Vals[Tim1idx]=act_TMR;
    Tim1idx++;
    if (Tim1idx>7)
        Tim1idx=0;
#endif

}


/*! \fn void ISR_TIM1_Update_Absolute_Timer()
   \author Dario Cortese
   \date 16-03-2019 modified 16-03-2019
   \brief this function is called by ISR TIM1 and is a little bit different from naun loop version
   In TIM1 could happen that the read value and prev value are equal, but in this case the difference is 2^16 and not 0
   \return none, but update Absolute_timer global variable
   \warning this function must be redefined on different hardware or implementation
   \version 1.00
   \see cdtimer_INIT
*/
void ISR_TIM1_Update_Absolute_Timer() {
    uint16_t act_TMR;
    uint16_t delta;
    
    act_TMR = get_timer1();
    if (act_TMR == cmn_update_prev_TMR){
        //add delta to global u32_SysTicks
        Absolute_timer += 0x10000 ;
    }else{
        delta = act_TMR - cmn_update_prev_TMR; //now is delta ticks
        //checks if misleading delta could generate eroor in absolute timer calculaction.
        //effectively could happen that a small delay could generate a difference of one clock
        // of timer 1 so delta calc result one but in reality i 0x10001
        //Against previous situation could, correctly, happen that prev_tmr is 0xffff and newer
        //timer value is 0x0000 or 0x0001; in this case one or two of delta is truthful
        if ((delta < 3) && (cmn_update_prev_TMR != 0xFFFF)){
            Absolute_timer += 0x10000 ;
        }
        Absolute_timer += delta;
    }
    cmn_update_prev_TMR = act_TMR;
    //add delta to global u32_SysTicks
}






/*! \fn void cdtimer_INIT()
   \author Dario Cortese
   \date 01-11-2015 modified on 08-02-2019
   \brief this function is called by main setup to initialize the time counter (one of the timers available in the microcontroller) in polling mode (NO ISR)
   Actualy it uses TMR4 with prescaler=/64  and PR4=255, so reset happens every ((Fosc/4)/64)/256=2048us wit 32MHz oscillator.
   \return none
   \warning this function must be redefined on different hardware or implementation
   \version 1.00
   \see cdtimer_GetTicks
*/
void cdTimer_INIT(){
    //intialize timer1 as
    //#use timer(timer=1,tick=1ms,bits=32,NOISR)
    Absolute_timer=0;
    setup_timer_1(T1_SOSC|T1_DIV_BY_1|T1_SYNC);      //2.0 s overflow 
    disable_interrupts(INT_TIMER1);    //no interrupt, only polling
}


#endif //_CDTIMERS_C_

