#include <msp.h>
int main(){
		//disable the watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
//Set SEL0 and SEL1 to 0
	P1->SEL0&=(uint8_t)(~((1<<0)|(1<<1)|(1<<4)));
	P1->SEL1&=(uint8_t)(~((1<<0)|(1<<1)|(1<<4)));
	P2->SEL0&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));
	P2->SEL1&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));	
	//Configure the switches P1.1 and P1.4 as inputs using pull-up resistors
	//DIR 0 REN 1 OUT 1
	P1->DIR&=(uint8_t)(~((1<<1)|(1<<4)));
	P1->REN|=(uint8_t)((1<<1)|(1<<4));
	P1->OUT|=(uint8_t)((1<<1)|(1<<4));
	//configure switch interrupts
	P1IES|=(uint8_t)0x12; //00010010 active low switches
	P1IFG&=(uint8_t)~0x12; //clear flags
	P1IE|=(uint8_t)0x12; //enable interupt
	//configure NVIC
	NVIC_SetPriority(PORT1_IRQn,2);
	NVIC->ICPR[1]|=0x00000012;
	NVIC_EnableIRQ(PORT1_IRQn);
	//Globally enable interrupts in CPU
	__ASM("CPSIE I");
	//Configure the LEDs (P1.0 and P2.0, P2.1, P2.2) as outputs.
	//DIR 1
	P1->DIR|=(uint8_t)(1<<0);
	P2->DIR|=(uint8_t)((1<<0)|(1<<1)|(1<<2));
	//Initialize LEDs states (all turned off).
	P1->OUT&=(uint8_t)(~(1<<0));
	P2->OUT&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));
	while(1){
	
	}
	return 0;
}
void PORT1_IRQHandler(void){
	
	static uint8_t toggle=(uint8_t)0x0; //default to red

	
	static int delay=10;
	/*Debouncing
		if((P1IN&0x12)){ //check pin
			P1IFG&=(uint8_t)~0x12; //clear flags if any
			return; //buttons were not actually pressed
		}
		while(delay>0){delay--;}
		if((P1IN&0x12)){ //check pin again
			P1IFG&=(uint8_t)~0x12; //clear flags if any
			return; //buttons were not actually pressed
		}*/
	
	while(1)
	{
		while(delay>0){delay--;}
		delay=10;
		if(!(P1IN&0x10) || !(P1IN&0x02)){ //check pin 
			break;
		}
	}

	if((P1IFG&(uint8_t)0x02)){
		//button 1 was pressed
		P1IFG&=(uint8_t)~0x02; //clear flag
		toggle^=(uint8_t)0x01;
	}else if((P1IFG&(uint8_t)0x10)){
		//button 2 was pressed
		P1IFG&=(uint8_t)~0x10; //clear flag
		if(toggle==0x00){
			P1OUT^=0x01;
		}else if (toggle==0x01){
			switch(P2OUT&0x07){
				case 0x00:	 
					P2OUT&=(uint8_t)~0x7; //clear
					P2OUT|=(uint8_t)0x01; //set
					break; 
				case 0x01:	
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x02; 
					break; 
				case 0x02:	 
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x03; 
					break; 
				case 0x03:	 
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x04; 
					break;
				case 0x04:	 
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x05; 
					break;
				case 0x05:	 
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x06; 
					break; 
				case 0x06:	 
					P2OUT&=(uint8_t)~0x7;
					P2OUT|=(uint8_t)0x07; 
					break; 
				case 0x07:	 
					P2OUT&=(uint8_t)~0x7;
					break; 
				}
			}
		}
		
}