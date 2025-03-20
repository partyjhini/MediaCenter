#ifndef USBMAIN_H
#define USBMAIN_H

#include "LPC17xx.h"              /* LPC17xx definitions */
#include "type.h"
#include "Board_Joystick.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"

#ifdef __cplusplus
extern "C" {
#endif


/* External variables */
extern uint8_t  Mute;                 /* Mute State */
extern uint32_t Volume;               /* Volume Level */
extern uint16_t DataOut;              /* Data Out Index */
extern uint16_t DataIn;               /* Data In Index */
extern uint8_t  DataRun;              /* Data Stream Run State */
extern uint16_t PotVal;               /* Potentiometer Value */
extern uint32_t VUM;                  /* VU Meter */
extern uint32_t Tick;                 /* Time Tick */
extern uint32_t joystickState;        /* Joystick State */

/* Function prototypes */
void get_potval(void);                /* Get Potentiometer Value */
void TIMER0_IRQHandler(void);         /* Timer Interrupt Service Routine */
int mp3(void);                        /* Main Function for USB Audio */

#ifdef __cplusplus
}
#endif

#endif /* USBMAIN_H */