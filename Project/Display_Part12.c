#include "Kuru0.c"
#include "Kuru1.c"
#include "Kuru2.c"
#include "Kuru3.c"
#include "Kuru4.c"
#include "Kuru5.c"


#include "GLCD.h"
#include "Board_Joystick.h"
#include "Board_LED.h"
#include "Display_Part12.h"
#include <stdio.h>
#include <stdint.h>
#include "usbdmain.h"

#include "gamemain.h"

#define __FI 1


void delay( ) {
    volatile uint32_t i;
		uint32_t ms = 10000;
    while (ms--) {
        for (i = 0; i < 1000; i++) {
            // This loop will run a number of times for each millisecond.
            // Adjust the loop count depending on your clock speed for accurate timing.
        }
    }
}

void Main_Menu() {
void (*functions[])() = { Imagedisplay, MP3_Player, Game };	

int index = 0;
uint32_t joystickState;
	
	LED_Initialize ();
  GLCD_Init();
	Joystick_Initialize();
	
  GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, __FI, "   Media Center     ");

	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(7,0, __FI , " Controls :     ");
	GLCD_DisplayString(8,0, __FI , " UP/DOWN , PRESS");
	
	while(1) {
		
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, __FI, "   Media Center     ");
		
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(7,0, __FI , " Controls :     ");
	GLCD_DisplayString(8,0, __FI , " UP/DOWN , PRESS");
		
		switch (index) { 

			case 0:
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(White);
				GLCD_DisplayString(3,0, __FI , "1. Photo Gallery          ");
                      
  GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
				GLCD_DisplayString(4,0, __FI , "2. MP3 Player             ");
				GLCD_DisplayString(5,0, __FI , "3. Game                   ");
		break;
			
			case 1:	
				//Delay();
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(White);
				GLCD_DisplayString(4,0, __FI , "2. MP3 Player             ");
				
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);		
				GLCD_DisplayString(3,0, __FI , "1. Photo Gallery          ");
				GLCD_DisplayString(5,0, __FI , "3. Game                   ");
		break;
			
			case 2:
				//Delay();
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(White);				
			GLCD_DisplayString(5,0, __FI , "3. Game                     ");
				
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);		
				GLCD_DisplayString(3,0, __FI , "1. Photo Gallery          ");
				GLCD_DisplayString(4,0, __FI , "2. MP3 Player             ");
		break;
	}	
	 joystickState = Joystick_GetState();
	
			if(joystickState & JOYSTICK_DOWN) {
				if (index < 2) {index++;}
				
			}
			
			if(joystickState & JOYSTICK_UP) {
				if (index > 0) {index--;} 
			}
			
			if(joystickState & JOYSTICK_CENTER) {
					functions[index]();
		}
	}
}
/*
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/

void Imagedisplay() {
	GLCD_Clear(White);
		int pic_num =0 ;
		uint32_t joystickState = 0 ;
		unsigned char* photos[] = {KURU0_PIXEL_DATA,KURU1_PIXEL_DATA,KURU2_PIXEL_DATA,KURU3_PIXEL_DATA,KURU4_PIXEL_DATA,KURU5_PIXEL_DATA};
		int heights[] = {KURU0_HEIGHT,KURU1_HEIGHT,KURU2_HEIGHT,KURU3_HEIGHT,KURU4_HEIGHT,KURU5_HEIGHT} ;
		
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, __FI, "   Media Center       ");
	
	GLCD_DisplayString(8, 0, __FI, " UP/DOWN = MOVE       ");
	GLCD_DisplayString(9, 0, __FI, " Select = EXIT        ");
	
	while (!(joystickState & JOYSTICK_CENTER)) {
		//have 5 different images, change up bitmap data
		GLCD_Bitmap (80,50,KURU0_WIDTH,heights[pic_num],photos[pic_num]);
		LED_Off(pic_num);
		
	 joystickState = Joystick_GetState();
	
			if(joystickState & JOYSTICK_DOWN) {
				pic_num++;
				if (pic_num > 5) {pic_num = 0;}
			}
			
			if(joystickState & JOYSTICK_UP) {
				if (pic_num > 0) {pic_num--;} 
			}
			LED_On(pic_num);
	}
		GLCD_Clear(White);
		for (pic_num = 0 ; pic_num < 6 ;pic_num++) {LED_Off(pic_num);}
	
}
		
		
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void MP3_Player() {
	
	GLCD_Clear(White);                         /* Clear graphical LCD display   */
  GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
  GLCD_DisplayString(0, 0, __FI, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, __FI, "   Media Center     ");
	
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Red);
	
	GLCD_DisplayString(5, 0, __FI ," Audio is Playing");
	GLCD_DisplayString(9, 0, __FI, " Press to Return ");
	
LED_On(0);
			mp3();
LED_Off(0);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void Game() {
	
		GameMain();
}