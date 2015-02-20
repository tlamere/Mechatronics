/******************************************************************
Name: main.c
Author: Frank Sup
Date: 1/28/2011
Comments: Walk through for writing a 'C' Program

INCLUDE FILES: p33FJ64MC202.h, p33FJ64MC202.gld (Linker Script),
functions.c, support.h
******************************************************************/
#include "p33FJ64MC202.h" 	//Include p33FJ64MC202 header file
#include "math.h" 			//Include math libary
#include "support.h" 		//Include Defitions and function prototypes
	
// global variable declartions
long int run_time = 0;	// 1 msec increments, resets at 2^16 msec
int wait_flag = 0;	// signal for end of sample time

/////////////////////////////////////////////////////////////////

// Start Main Function
int main()
{

//main local variables
int i = 0;					//general counter
int button = 0;			//digital I/O Button
int buttonCount = 0;
//Initialization Routines
init_clock();			// initialize Clock 80 MHz/40 MIPS
init_pins();			// initialize pins
init_samptime();		// initialize sample time (1ms)

// INSERT SETUP CODE HERE (NEEDS TO RUN JUST ON SETUP)
// INSERT SETUP CODE HERE (NEEDS TO RUN JUST ON SETUP)

// Start of main loop (1 msec sample period)
while(1)
{

	if (PORTBbits.RB6){
		buttonCount++;
		if ( buttonCount > 50){
			i = -5000;
			LATB = 0x1000;
			buttonCount = 0;
			}
		}
	
	if (i < 5000){
		LATB = 0x1000;
	}
	else if (i > 5000 && i < 7000){
		LATB = 0x2000;
	}
	else if (i > 7000 && i < 12000){
		LATB = 0x4000;
	}
	else if (i > 12000){
		i = 0;
	}
	i++;
	// YOUR MAIN LOOP CODE HERE
	// YOUR MAIN LOOP CODE HERE

	// wait for end of sample time
	while(wait_flag == 0) {
		SAMPLE_TIME != SAMPLE_TIME;}		// wait for end of sample time
	
		
	
		wait_flag = 0;					// reset wait flag
}
return 0;
} // end main
