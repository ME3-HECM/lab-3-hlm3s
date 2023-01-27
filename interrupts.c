#include <xc.h>
#include "interrupts.h"

/************************************
 * Function to turn on interrupts and set if priority is used
 * Note you also need to enable peripheral interrupts in the INTCON register to use CM1IE.
************************************/
void Interrupts_init(void)
{
	// turn on global interrupts, peripheral interrupts and the interrupt source
    INTCONbits.PEIE=1;
    PIE2bits.C1IE=1;
    PIE0bits.TMR0IE = 1;
    INTCONbits.GIE=1;
    
    PIR0bits.TMR0IF=0; // clear interrupt
    
	// It's a good idea to turn on global interrupts last, once all other interrupt configuration is done.
}

/************************************
 * High priority interrupt service routine
 * Make sure all enabled interrupts are checked and flags cleared
************************************/
void __interrupt(high_priority) HighISR()
{
    if(PIR2bits.C1IF){ 					//check the interrupt source
        
	LATHbits.LATH3=1; //LED on
    __delay_ms(100);
    LATHbits.LATH3=0; //Wait, LED off
    
	PIR2bits.C1IF=0; 						//clear the interrupt flag!
	}
    
   if(PIR0bits.TMR0IF){ // check for overflow
       
       LATHbits.LATH3 = !LATHbits.LATH3; //toggle LED
       PIR0bits.TMR0IF=0; // clear interrupt flag
   }
	//add your ISR code here i.e. check the flag, do something (i.e. toggle an LED), clear the flag...
}

