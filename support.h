/*******************************************************
Name: support.h
Date: 2/3/2011
Authors: Frank Sup
Comments:  Support file for definitions and function prototypes
*******************************************************/

//defines to improve code clarity
#define PI 3.141592653589
#define SAMP_TIME 1					// sample time in millisec
#define SAMP_T 10000
#define WAIT i=0;while(i<15)i++;

#define GRN_LED _RB12				// RB12
#define YEL_LED _RB13				// RB13
#define RED_LED _RB14				// RB14 
#define SAMPLE_TIME _RB15			// RB15

// Function Prototypes
void init_clock(void);
void init_samptime(void);
void init_pins(void);
