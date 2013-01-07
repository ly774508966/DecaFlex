/*
 * Update.c
 *
 * Created: 12/7/2012 6:29:41 PM
 *  Author: Anthony
 */ 
#include "Update.h"
#include "Pinout.h"
#include "util.h"
#include <avr/interrupt.h>

uint8_t currentADC = 0;
bool ready = false;
DECAFLEX_RAWUpdate_EP1_t state;

 void init_pins()
 {
	
	// Configure output pins
	
		// User LED
		bit_set(DDR_USER, BIT(PIN_USER));
	
	// Configure input pins
	
		// Mode button
		bit_clear(DDR_MODEBTN, BIT(PIN_MODEBTN));
		
	// Configure ADC input pins
	
		bit_set(DIDR_THUMB_MID, BIT(PIN_THUMB_MID));
		bit_set(DIDR_THUMB_DIST, BIT(PIN_THUMB_DIST));
		
 		bit_set(DIDR_INDEX_MID, PIN_INDEX_MID);
 		bit_set(DIDR_INDEX_PROX, PIN_INDEX_PROX);
 		
 		bit_set(DIDR_MIDDLE_MID, PIN_MIDDLE_MID);
 		bit_set(DIDR_MIDDLE_PROX, PIN_MIDDLE_PROX);
 		
 		bit_set(DIDR_RING_MID, PIN_RING_MID);
 		bit_set(DIDR_RING_PROX, PIN_RING_PROX);
		
		bit_set(DIDR_PINKY_MID, BIT(PIN_PINKY_MID));
		bit_set(DIDR_PINKY_PROX, BIT(PIN_PINKY_PROX));
	
	/// Initialize ADC
	
		bit_set(ADCSRA, BIT(ADPS2)|BIT(ADPS1)|BIT(ADPS0));		// Set prescaler to 128 (125kHz)
		bit_set(ADMUX, BIT(REFS0));		// Set Reference voltage to AVcc
		
	//	bit_set(ADCSRA, BIT(ADATE));	// enable auto-triggering
										// Leave ADTS in free-running mode.
		
		currentADC = 0;					// ADC0 is the default
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		
		
		bit_set(ADCSRA, BIT(ADIE));	// Enable ADC Interrupt Flag
		
		
		bit_set(ADCSRA, BIT(ADEN));	// Enable the ADC
		
		bit_set(ADCSRA, BIT(ADSC));	// Start the first measurement
		
		
}

ISR(ADC_vect)
{
	/// Evolutionary Prototype 1 - Read ADC0-10
	
	/// 1.) Store value
	/// 2.) Change MUX5..0 to next ADC pin
	/// 3.) Start next conversion
	
	switch (currentADC)
	{
	case 0:		// Thumb - Middle
		
		state.Thumb_Middle = ADC;
	
		currentADC = 1;

		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		
		break;
	case 1:		// Thumb - Distal
		state.Thumb_Distal = 2;
		
		currentADC = 4;
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 4:		// Index - Proximal
		
		state.Index_Proximal = ADC;
		
		currentADC = 5;
		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 5:		// Index - Middle
		
		state.Index_Middle = ADC;
		
		currentADC = 6;
		bit_clear(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 6:		// Middle - Proximal
	
		state.Middle_Proximal = ADC;
	
		currentADC = 7;
		bit_set(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 7:		// Middle - Middle
	
		state.Middle_Middle = ADC;
		
		currentADC = 8;
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 8:		// Ring - Proximal
	
		state.Ring_Proximal = ADC;
	
		currentADC = 9;
		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 9:		// Ring - Middle
	
		state.Ring_Middle = ADC;
	
		currentADC = 10;
		bit_clear(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 10:	// Pinky - Proximal
		
		state.Pinky_Proximal = ADC;
	
		currentADC = 11;
		bit_set(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;

	case 11:	// Pinky - Middle (Go back to 0/default)
	
		state.Pinky_Middle = ADC;
		
	default:
		currentADC = 0;
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		
		/// Increment sequence #
		state.SequenceID = state.SequenceID + 1;
		state.BatteryStatus = 0;
		ready = true;
		break;
	}
	
	
	/// Manually start next capture
	bit_set(ADCSRA, BIT(ADSC));	// Start the next measurement
	
}

bool updateReady()
{
	
	/// Always true, for now
	return ready;
	
}


void performUpdate(DECAFLEX_RAWUpdate_EP1_t* pState)
{
	
	*pState	= state;	
	ready = false;
}

