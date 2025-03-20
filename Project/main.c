/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/

#define osObjectsPublic                     // define objects in main module
#include "osObjects.h"                      // RTOS object definitions
#include "PIN_LPC17xx.h"
#include "GPIO_LPC17xx.h"
#include "Display_Part12.h"

/*
 * main: initialize and start the system
 */
int main (void) {
  osKernelInitialize ();                    // initialize CMSIS-RTOS
	Main_Menu();
  osKernelStart ();                         // start thread execution 
}
