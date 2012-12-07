/*
 * DecaFlex.c
 *
 * Created: 12/2/2012 12:05:14 AM
 *  Author: Anthony
 */ 


#include <avr/io.h>
#include <util/delay.h>

#include "LUFA/Common/Common.h"
#include "LUFA/Drivers/USB/USB.h"

#include "USB/USBImpl.h"

int main(void)
{
	
	// Initialization
	
	
	// Load Mode from Flash
	
	
   // Initialize USB
   USB_Init();

   // Enable global interrupts
   sei();
   
   // Main loop
   while(1)
   {
	   
	   ServiceUSB();
	   
   }
}