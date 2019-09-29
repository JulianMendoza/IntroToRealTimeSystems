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
	//Configure the LEDs (P1.0 and P2.0, P2.1, P2.2) as outputs.
	//DIR 1
	P1->DIR|=(uint8_t)(1<<0);
	P2->DIR|=(uint8_t)((1<<0)|(1<<1)|(1<<2));
	//Initialize LEDs states (all turned off).
	P1->OUT&=(uint8_t)(~(1<<0));
	P2->OUT&=(uint8_t)(~((1<<0)|(1<<1)|(1<<2)));
	//Create an infinite loop ("while (1)") after your configurations, where the remaining logic should be implemented.
	//Continuously poll the switches (with debouncing)
	//When Button 1 is pressed, the selected LED changes (default, RED LED).
	//When Button 2 is pressed, the current LED changes state.
	
	#define LED1 P1OUT
	#define LED2 P2OUT
	static uint8_t toggle=(uint8_t)0x0; //default to RED LED
			while(1){
				int i =10;
				while((P1IN & 0x2) && (P1IN & 0x10)){} //do nothing

				while(i>0){i--;} //delay loop
				if(((P1IN & 0x2)  && (P1IN & 0x10))){
					//buttons were not pressed
					continue;
				}else{
					if((~(P1IN & 0x2) &&(P1IN & 0x10))){
						//button 1 is pressed
						toggle^=(uint8_t)0x01;
					}else if(((P1IN & 0x2) &&~(P1IN & 0x10))){
						//button 2 is pressed
						if(toggle!=(uint8_t)0x00){
							switch(LED2&(uint8_t)0x07){ //only care about first 3 bits
								case 0x00:	 
									LED2&=(uint8_t)~0x7; //clear
									LED2|=(uint8_t)0x01; //set
									break; 
								case 0x01:	
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x02; 
									break; 
								case 0x02:	 
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x03; 
									break; 
								case 0x03:	 
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x04; 
									break;
								case 0x04:	 
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x05; 
									break;
								case 0x05:	 
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x06; 
									break; 
								case 0x06:	 
									LED2&=(uint8_t)~0x7;
									LED2|=(uint8_t)0x07; 
									break; 
								case 0x07:	 
									LED2&=(uint8_t)~0x7;
									break; 
							}
						}else if(toggle==(uint8_t)0x00){
							LED1^=(uint8_t)0x01;
					}
				}
			}
		}
	
	return 0;
	}
