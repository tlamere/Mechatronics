/*******************************************************
Name: functions.c
Date: 2/3/2011
Authors: Frank Sup
Comments:  Support file for functions
*******************************************************/
#include "p33FJ64MC202.h" 	//Include p33FJ64MC202 header file
#include "math.h" 			//Include math libary
#include "support.h" 		//Include Defitions and function prototypes

extern long int run_time;	// run time in milliseconds
extern int wait_flag;		// signals end of 1 millisecond sample period
extern int button;
//////////////////////////////////////////////////////////
// Initialize of Clock Frequency

//Configuration Bits for Clock Initialization Parameters
_FOSCSEL(FNOSC_FRC);				// Select Internal FRC at POR
_FOSC(FCKSM_CSECMD & OSCIOFNC_OFF);	// Enable Clock Switching and Output Clock to OSC2
_FWDT(FWDTEN_OFF); 					// Turn off Watchdog Timer
_FICD(JTAGEN_OFF & ICS_PGD1);		// Turn off JTAG and communicate on PGC1/EMUC1 and PGD1/EMUD1

void init_clock(void)
{
// Configure PLL prescaler, PLL postscaler, PLL divisor 
// 7.37 MHz * 43 / 2 / 2 = 79.227 MHz
PLLFBD = 41;			// M = 43
CLKDIVbits.PLLPOST=0;	// N2 = 2
CLKDIVbits.PLLPRE=0;	// N1 = 2

// Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
__builtin_write_OSCCONH(0x01);
__builtin_write_OSCCONL(0x01);

// Wait for Clock switch to occur
while (OSCCONbits.COSC != 0b001);

// Wait for PLL to lock
while(OSCCONbits.LOCK!=1) {};
} //end init_clock

//////////////////////////////////////////////////////////
// Timer1 interupt service routine
// Used to enforce Sample Time
void _ISR _T1Interrupt(void)
{
	
	IFS0bits.T1IF = 0;
	run_time++;
	wait_flag = 1;		//Signal end of sample time
} // end T1Interupt


//////////////////////////////////////////////////////////
// Intialize Sample Time (1 msec)
void init_samptime(void)
{
	TMR1 = 0;
	PR1 = 4952 - 1; 	// Set the period register - 1 msec
	T1CON = 0x8010;		// TMR1 on, prescalar set to 1:8 Tclk/2
	_T1IF = 0; 			// Clear Flag
	_T1IE = 1;			// Enable Source
} //end init_samptime


//////////////////////////////////////////////////////////
//Initialize Pins
void init_pins(void)
/* Pin Overview Map
//		RB0						RA0 - RESERVED
//		RB1						RA1 - RESERVED
//		RB2	- RESERVED			RA2	
//		RB3	- RESERVED			RA3
//		RB4	- RESERVED			RA4
//		RB5 - RESERVED			RA5
//		RB6 - BUTTON
//		RB7 - RESERVED
//		RB8 - RESERVED
//		RB9
//		RB10 - OSC2 (clock output)
//		RB11
//		RB12 - GRN LED
//		RB13 - YEL LED
//		RB14 - RED LED
//		RB15 - Sample Time Output
*/ 

{
	AD1PCFGL = 0xfffc; 	// RA0/AN0 analog, rest digital

	TRISA = 0x0001; 	// RA0 input, rest output
	ODCA = 0;			// all pins set NOT open drain
	LATA = 0x0000;		// all pins set to zero

	TRISB = 0x0040; 	// 	RB6 input,rest PORTB pins set to output
	ODCB = 0x0000;		//	no open drain pins
	LATB = 0x0000;		//	all pins set to zero

} // end init_pins



