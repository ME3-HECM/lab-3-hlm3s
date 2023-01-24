#include <xc.h>
#include "LEDarray.h"

#define LED1 LATGbits.LATG0
#define LED2 LATGbits.LATG1
#define LED3 LATAbits.LATA2
#define LED4 LATFbits.LATF6
#define LED5 LATAbits.LATA4
#define LED6 LATAbits.LATA5
#define LED7 LATFbits.LATF0
#define LED8 LATBbits.LATB0
#define LED9 LATBbits.LATB1



/************************************
/ LEDarray_init
/ Function used to initialise pins to drive the LEDarray
************************************/
void LEDarray_init(void)
{
    //set up TRIS registers for pins connected to LED array
    TRISHbits.TRISH3=0;
    TRISGbits.TRISG0=0;
    TRISGbits.TRISG1=0;
    TRISAbits.TRISA2=0;
    TRISAbits.TRISA4=0;
    TRISAbits.TRISA5=0;
    TRISFbits.TRISF6=0;
    TRISFbits.TRISF0=0;
    TRISBbits.TRISB0=0;
    TRISBbits.TRISB1=0;
	//set initial output LAT values (they may have random values when powered on)
    LATHbits.LATH3=0; 
    LATGbits.LATG0=0;
    LATGbits.LATG1=0;
    LATAbits.LATA2=0;
    LATAbits.LATA4=0;
    LATAbits.LATA5=0;
    LATFbits.LATF6=0;
    LATFbits.LATF0=0;
    LATBbits.LATB0=0;
    LATBbits.LATB1=0;
}

/************************************
/ LEDarray_disp_bin
/ Function used to display a number on the LED array in binary
************************************/
void LEDarray_disp_bin(unsigned int number)
{
	//some code to turn on/off the pins connected to the LED array
	//if statements and bit masks can be used to determine if a particular pin should be on/off
//    LATHbits.LATH3=0; 
//    LATGbits.LATG0=0;
//    LATGbits.LATG1=0;
//    LATAbits.LATA2=0;
//    LATAbits.LATA4=0;
//    LATAbits.LATA5=0;
//    LATFbits.LATF6=0;
//    LATFbits.LATF0=0;
//    LATBbits.LATB0=0;
//    LATBbits.LATB1=0;
    
    LED1 = (number & 0b000000001);
    LED2 = (number & 0b000000010) >> 1;
    LED3 = (number & 0b000000100) >> 2;
    LED4 = (number & 0b000001000) >> 3;
    LED5 = (number & 0b000010000) >> 4;
    LED6 = (number & 0b000100000) >> 5;
    LED7 = (number & 0b001000000) >> 6;
    LED8 = (number & 0b010000000) >> 7;
    LED9 = (number & 0b100000000) >> 8;
            
    
	//see Readme.md for examples
}

/************************************
/ Function LEDarray_disp_dec
/ Used to display a number on the LEDs
/ where each LED is a value of 10
************************************/
void LEDarray_disp_dec(unsigned int number)
{
	unsigned int disp_val = 0;
    
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
    
    if (number < 10) {
        disp_val = 0;
    }
    if (number >= 10) {
        disp_val = 1;
    }
    if (number >= 20) {
        disp_val = 2;
    }

	LEDarray_disp_bin(disp_val); 	//display value on LED array
}


/************************************
/ Function LEDarray_disp_lev
/ Used to display a light level on the LEDs
/ where each LED is a an increase of 256/8
************************************/
void LEDarray_disp_bar(unsigned int number)
{
    
    unsigned int lev = 0;
    
    while (number > 1){
        number = number >> 1;
        lev ++;   
    }
    
    unsigned int disp_val = 0;
    disp_val = 1 << lev;
    LEDarray_disp_bin(disp_val - 1);
    
    
    
	//some code to manipulate the variable number into the correct
	//format and store in disp_val for display on the LED array
}

/************************************
/ LEDarray_disp_PPM
/ Function used to display a level on the LED array with peak hold
/ cur_val is the current level from the most recent sample, and max is the peak value for the last second
/ these input values need to calculated else where in your code
************************************/
void LEDarray_disp_PPM(unsigned int number, unsigned int max)
{
    unsigned int lev = 0;
    unsigned int maxlev = 0;
    int inc;
    int count = 0;
    
    inc = 255/8;
    
    while (count < number){
        count += inc;
        lev ++;   
    }
    
    count = 0;
    
    while (count < max){
        count += inc;
        maxlev ++;   
    }
    
    unsigned int disp_val = 0;
    unsigned int max_val = 0;
    unsigned int fin_val = 0;
    disp_val = (1 << lev) - 1;
    max_val = 1 << (maxlev - 1);
    fin_val = (disp_val)|(max_val);
    
    LEDarray_disp_bin(fin_val);
	
	// some code to format the variable cur_val and max, store in disp_val for display on the LED array
	// hint: one method is to manipulate the variables separately and then combine them using the bitwise OR operator

}