#include <msp.h>

//Must always include our OS header file
#include "fate.h"
#include "BSP.h"

	
int exetime =0;
//No calling other functions
//When execution is finished, must always call "Task_stop" with its name
//NOT return: that would probably crash our kernel
void update_screen(void){
	static int count=0;
	BSP_LCD_SetCursor((uint32_t)10,(uint32_t)6);
	BSP_LCD_OutUDec((int32_t) count,(int16_t) BSP_LCD_Color565((uint8_t)255,(uint8_t)255, (uint8_t)255));
	count++;
	printexetime();
	Task_stop((uint32_t)update_screen);
}
void printexetime(){
	BSP_LCD_SetCursor((uint32_t)10,(uint32_t)7);
	BSP_LCD_OutUDec((int32_t) exetime*10,(int16_t) BSP_LCD_Color565((uint8_t)0,(uint8_t)255, (uint8_t)0));
	exetime=0;
}
int main()
{
	TA1CTL&=(uint16_t)(~((1<<5)|(1<<4))); //stop clock
	TA1CTL&=(uint16_t)(~(1<<9));
	TA1CTL|=(uint16_t)((1<<8));  //A CLK 2 seconds per interupt 
	TA1CCR0=(uint16_t)((0xFFFF-0x01)/200); //divide 2^16-1 by 200 is every 0.01 seconds
	TA1CTL|=(uint16_t)((0<<5)|(1<<4)); //UP MODE
	TA1CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	TA1CTL|=(uint16_t)((1<<1)); //toggle interrupt behavior
	NVIC_SetPriority(TA1_N_IRQn,2);
	NVIC_EnableIRQ(TA1_N_IRQn);
	//Initialize Task list, includes setting up idle task
	//Always the first function that must be called
	Task_list_init();
	
	BSP_LCD_Init();
	//Initialize our periodic tasks, with periods 100 and 200 ticks (1 and 2s), respectively
	//Task_add((uint32_t)LED_toggle,(uint32_t) 100, (uint32_t) 1);
	//Task_event_add((uint32_t)LED_RGB_toggle, SWITCH_P1_4, (uint32_t) 1);
	Task_add((uint32_t)update_screen,(uint32_t)200,(uint32_t)1);
	
	//This will begin scheduling our tasks 
	Task_schedule();
	
	return 0;
}
void TA1_N_IRQHandler(void){
	TA1CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	//Increment count by 1 every 0.01 seconds
	exetime++;
}
