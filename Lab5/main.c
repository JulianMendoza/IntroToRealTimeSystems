#include <msp.h>
#include "BSP.h"
int main(){
		//disable the watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
	uint16_t x_pos, y_pos,duty,frequency;
	uint8_t select;
	duty=0x0;
	frequency=0x0;
	BSP_Buzzer_Init(duty);
	BSP_Joystick_Init();
	BSP_Joystick_Input(&x_pos, &y_pos, &select);
	while(1){
			BSP_Joystick_Input(&x_pos, &y_pos, &select);
		if(x_pos<=341&&y_pos<=341){
			BSP_Buzzer_Set(511,1480);
		}else if(x_pos<=682&&y_pos<=341){
			BSP_Buzzer_Set(511,1661);
		}else if(y_pos<=341){
			BSP_Buzzer_Set(511,1760);
		}else if(x_pos<=341&&y_pos<=682){
			BSP_Buzzer_Set(511,1175);
		}else if(x_pos<=682&&y_pos<=682){
			BSP_Buzzer_Set(0,880);
		}else if(y_pos<=682){
			BSP_Buzzer_Set(511,1319);
		}else if(x_pos<=341&&y_pos<=1023){
			BSP_Buzzer_Set(511,880);
		}else if(x_pos<=682&&y_pos<=1023){
			BSP_Buzzer_Set(511,980);
		}else if(y_pos<=1023){
			BSP_Buzzer_Set(511,1109);
		}
	}
}