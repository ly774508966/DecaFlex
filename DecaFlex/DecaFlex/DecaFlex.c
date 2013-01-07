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
#include "util.h"


int main(void)
{
	
	
	bit_set(DDRB, PORTB0);
	bit_clear(PORTB, PORTB0);
	

	// Load Mode from Flash

	// Initialize IO
	init_pins();
	
	// Initialize USB
	USB_Init();

	// Enable global interrupts
	sei();
   
   // Main loop
   while(1)
   {
	   

//		bit_write((USB_DeviceState == DEVICE_STATE_Configured), PORT_USER, BIT(PIN_USER));

		ServiceUSB();
	   
   }
}