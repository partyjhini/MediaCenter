#include "LPC17xx.h"                   	/* LPC17xx definitions */
#include "type.h"
#include "Board_Joystick.h"
#include "Board_LED.h"
#include "GLCD.h"
#include <stdio.h>
#include <stdlib.h>
#include "gamemain.h"

#include "Up.c"
#include "Down.c"
#include "Notes.c"
#include "ClearNotes.c"

//--------------------------------------------------------------------------------------------------------------------------------------------// Initializing Variables
#define MAX_WIDTH 240
#define	MAX_HEIGHT 300
#define RANGE_PERFECT	10
#define	GAME_NOT_OVER 0
#define GAME_OVER 1

extern uint32_t SystemCoreClock;
	
volatile int currentCombo = 0;
char text1[20];
typedef struct {
	int x;
	int y;
	int active;
} Notes;

#define MAX_NOTES 10
Notes notes[MAX_NOTES];

const int noteColumns[] = {70, 160};	// position of the two place that needs columns
volatile uint8_t note_timer = 0;
volatile uint8_t note_index = 0;
volatile uint32_t joystickState_;
volatile int state = GAME_OVER;
//--------------------------------------------------------------------------------------------------------------------------------------------// Functions

void delay_() {
	int x,y;
	for (x =0; x < 100 ; x++){
		for (y = 0; y < 100; y++) {
		}
}
}

void setup_Timer(void) {
	// Enable power to TIMER1 
	LPC_SC->PCONP |= (1 << 2);  // Power to TIMER1

	// Timer configuration for TIMER1
	LPC_TIM1->MR0 = SystemCoreClock / 15;  // Set match register value 
	LPC_TIM1->MCR |= (1 << 0) | (1 << 1);  // Interrupt on match, Reset on match
	LPC_TIM1->TCR = 1;  // Enable timer

	// Enable TIMER1 interrupt
	NVIC_EnableIRQ(TIMER1_IRQn);  // Enable TIMER1 interrupt handler
	LED_On(7);
}


void init_game(void) {
	int i =0;
	GLCD_Clear(White);
	currentCombo = 0;
	for (i = 0; i < MAX_NOTES; i++) {
    	notes[i].x = 0;
    	notes[i].y = 0;
    	notes[i].active = 0;
	}
    create_background();
}

void create_background (void) {
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0, 0, 1, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, 1, "     Media Center       	  ");
	GLCD_SetBackColor(White);
  GLCD_SetTextColor(Blue);
	sprintf(text1, 							"   Combo : %d   ",currentCombo);
	GLCD_DisplayString(2, 0, 1, text1);
		
	GLCD_Bitmap(10, noteColumns[0],  NOTESBAR_WIDTH, NOTESBAR_HEIGHT, NOTESBAR_PIXEL_DATA);
	GLCD_Bitmap(10, noteColumns[1],  NOTESBAR_WIDTH, NOTESBAR_HEIGHT,	NOTESBAR_PIXEL_DATA);

}


void spawn_notes (void) {
    	int i =0;
    	for (i = 0; i < MAX_NOTES ; i++)
	{
        	if (!notes[i].active) {
            	notes[i].y = noteColumns[rand() %2];
          	notes[i].x = 250;
            	notes[i].active = 1;
        	break;
        	}
    	}
}

void move_notes(void) {
	int i =0;
	for (i = 0; i < MAX_NOTES ; i++) {
	if (notes[i].active) {
    	notes[i].x -= 10;

    	}
	}    
}

void check_input (void) {
int i = 0;
	for (i = 0; i<MAX_NOTES; i++) {
    	if (notes[i].active && notes[i].x < 50 + RANGE_PERFECT) {
            	if ((Joystick_GetState() & JOYSTICK_UP) && notes[i].y == noteColumns[0]) {
							notes[i].active = 0;
            	currentCombo++;
							GLCD_Clear(White);
							}
							
            	if ((Joystick_GetState() & JOYSTICK_DOWN) && notes[i].y == noteColumns[1]) {	
            	notes[i].active = 0;
            	currentCombo++;
							GLCD_Clear(White);
            	}  
				}	
    	}       	 
	}


void TIMER1_IRQHandler(void)					// 
{
    	if (LPC_TIM1 -> IR & 1)
    	{ LPC_TIM1->IR = 1;
        	note_timer++;
            	if (note_timer >= 10) { //number represents the frequency of new notes
                	spawn_notes();
                	note_timer = 0;
            	}
            	move_notes();
            	check_input();
           	 
        	create_background();
                	for (int i = 0; i< MAX_NOTES; i++) {
                    	if (notes[i].active) {    
												GLCD_Bitmap(((notes[i].x)-35),notes[i].y,NOTES_WIDTH,NOTES_HEIGHT,NOTES_PIXEL_DATA);
											if (notes[i].active && notes[i].x == 0) {
												NVIC_DisableIRQ(TIMER1_IRQn);
												init_game();
												GLCD_Clear(Blue);
												GLCD_SetBackColor(Blue);
												GLCD_SetTextColor(Red);
					  GLCD_DisplayString(2, 0, 1, "     Game  Over    ");
						GLCD_DisplayString(5, 0, 1, " MOVE RIGHT to Menu ");
						GLCD_DisplayString(6, 0, 1, "   PRESS to Retry  ");
						state = GAME_OVER;
						delay();
                	}
            	}
    	}
}
}


void GameMain (void) {
	
  GLCD_Clear(White);
	GLCD_SetBackColor(Blue);
  GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(0, 0, 1, " COE718 Lab Project   ");
	GLCD_DisplayString(1, 0, 1, "     Media Center       ");
    
	GLCD_SetBackColor(White);
	GLCD_SetTextColor(Blue);
	GLCD_DisplayString(3, 0, 1 ,"Move Joystick Up/Down");
	GLCD_DisplayString(4, 0, 1 ,"  to hit the notes  ");	
	GLCD_DisplayString(5, 0, 1 ," Game Over When Missed	");	
	
	GLCD_DisplayString(8, 0, 1, " Press to Start Game	");
	GLCD_DisplayString(9, 0, 1, " RIGHT to Main Menu  ");
  state = GAME_OVER;  
	while (1) {
    	 joystickState_ = Joystick_GetState();
        	if((joystickState_ & JOYSTICK_CENTER) && state == GAME_OVER) {
            GLCD_Clear(White);    		
						setup_Timer();			
						init_game ();
						state = GAME_NOT_OVER;
					} if ((joystickState_ & JOYSTICK_RIGHT) && state == GAME_OVER) {
						NVIC_DisableIRQ(TIMER1_IRQn);
						GLCD_Clear(White);
					break;
					}						
				}
	}

