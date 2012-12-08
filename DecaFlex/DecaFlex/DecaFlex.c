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

#include "Pinout.h"
#include "Update.h"

int main(void)
{
	
	// Enable global interrupts
	sei();

	// Load Mode from Flash

	// Initialize IO
	init_pins();
	
	// Initialize USB
	USB_Init();

   
   // Main loop
   while(1)
   {
	   
	   ServiceUSB();
	   
   }
}