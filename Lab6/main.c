#include <msp.h>
int main(){
		//disable the watchdog timer
	WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;
//Set SEL0 and SEL1 to 0
	P1->SEL0&=(uint8_t)(~(1<<0));
	P1->SEL1&=(uint8_t)(~(1<<0));
	P2->SEL0&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));
	P2->SEL1&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));	
	//Configure the LEDs (P1.0 and P2.0, P2.1, P2.2) as outputs.
	//DIR 1
	P1->DIR|=(uint8_t)(1<<0);
	P2->DIR|=(uint8_t)((1<<0)|(1<<1)|(1<<2));
	//Initialize LEDs states (all turned off).
	P1->OUT|=(uint8_t)(1<<0);//RED IS ON
	P2->OUT&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));
	//Configure timer A0
	TA0CTL&=(uint16_t)(~((1<<5)|(1<<4))); //stop clock
	TA0CTL&=(uint16_t)(~(1<<9));
	TA0CTL|=(uint16_t)((1<<8));  //A CLK 2 seconds per interupt 
	TA0CCR0=(uint16_t)((0xFFFF-0x01)/2); //divide 2^16-1 by 2
	TA0CTL|=(uint16_t)(1<<4); //UP/MODE
	TA0CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	TA0CTL|=(uint16_t)((1<<1)); //toggle interrupt behavior
	NVIC_SetPriority(TA0_N_IRQn,1);
	NVIC_EnableIRQ(TA0_N_IRQn);
	//configure timer A1
	TA1CTL&=(uint16_t)(~((1<<5)|(1<<4))); //stop clock
	TA1CTL&=(uint16_t)(~(1<<9));
	TA1CTL|=(uint16_t)((1<<8));  //A CLK 2 seconds per interupt 
	TA1CCR0=(uint16_t)((0xFFFF-0x01)/20); //divide 2^16-1 by 10 is every 0.1 seconds
	TA1CTL|=(uint16_t)((1<<5)|(1<<4)); //UP/Down MODE
	TA1CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	TA1CTL|=(uint16_t)((1<<1)); //toggle interrupt behavior
	NVIC_SetPriority(TA1_N_IRQn,2);
	NVIC_EnableIRQ(TA1_N_IRQn);
		__ASM("CPSIE I");
	while(1){
	
	}
	return 0;
}

void TA0_N_IRQHandler(void){
	TA0CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	P1OUT^=(uint8_t)0x01;
}
void TA1_N_IRQHandler(void){
	TA1CTL&=(uint16_t)(~(1<<0)); //clear any existing flags
	if(TA1CCR0==((0xFFFF-0x01)/20)){
			TA1CTL&=(uint16_t)(~((1<<5)|(1<<4))); //stop clock
			TA1CCR0=(uint16_t)((0xFFFF-0x01)/4); //divide 2^16-1 by 10 is every 0.1 seconds
			TA1CTL|=(uint16_t)((1<<5)|(1<<4)); //UP/Down MODE
	}
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