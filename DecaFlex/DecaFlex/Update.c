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

uint16_t min[] = {65535,65535,65535,65535,65535,65535,65535,65535,65535,65535};
uint16_t max[] = {0,0,0,0,0,0,0,0,0,0};

uint16_t readings0[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings1[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings2[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings3[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings4[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings5[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings6[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings7[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings8[] = {0,0,0,0,0,0,0,0,0,0};
uint16_t readings9[] = {0,0,0,0,0,0,0,0,0,0};
	
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
		
		state.Thumb_Proximal = filter(currentADC, setRange(ADC, &min[currentADC], &max[currentADC], 0, 128));
	
		currentADC = 1;

		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		
		break;
	case 1:		// Thumb - Distal
		state.Thumb_Distal = filter(currentADC, setRange(ADC, &min[currentADC], &max[currentADC], 0, 128));
		
		currentADC = 4;
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 4:		// Index - Proximal
		
		state.Index_Proximal = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
		
		currentADC = 5;
		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 5:		// Index - Middle
		
		state.Index_Middle = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
		
		currentADC = 6;
		bit_clear(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 6:		// Middle - Proximal
	
		state.Middle_Proximal = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
	
		currentADC = 7;
		bit_set(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_set(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_clear(ADCSRB, BIT(MUX5));
		break;
	case 7:		// Middle - Middle
	
		state.Middle_Middle = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
		
		currentADC = 8;
		bit_clear(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 8:		// Ring - Proximal
	
		state.Ring_Proximal = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
	
		currentADC = 9;
		bit_set(ADMUX, BIT(MUX0));
		bit_clear(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 9:		// Ring - Middle
	
		state.Ring_Middle = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
	
		currentADC = 10;
		bit_clear(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;
	case 10:	// Pinky - Proximal
		
		state.Pinky_Proximal = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
	
		currentADC = 11;
		bit_set(ADMUX, BIT(MUX0));
		bit_set(ADMUX, BIT(MUX1));
		bit_clear(ADMUX, BIT(MUX2));
		bit_clear(ADMUX, BIT(MUX3));
		bit_clear(ADMUX, BIT(MUX4));
		bit_set(ADCSRB, BIT(MUX5));
		break;

	case 11:	// Pinky - Middle (Go back to 0/default)
	
		state.Pinky_Middle = filter(currentADC-2, setRange(ADC, &min[currentADC-2], &max[currentADC-2], 0, 128));
			
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
//	state.Dummy = sizeof(DECAFLEX_RAWUpdate_EP1_t);
	state.Accel_X = sizeof(DECAFLEX_RAWUpdate_EP1_t);
	ready = false;
}


uint16_t setRange(uint16_t input, uint16_t* min, uint16_t* max, uint16_t rangeMin, uint16_t rangeMax)
{
			if (input > *max)
	{
		*max = input;
	}		if (input < *min)	{		*min = input;	}
	return rangeMin + (input-(*min))*(rangeMax-rangeMin)/((*max)-(*min));
	// return (uint16_t)((float)input + slope * (float)input - (float)*min);	
	
}

uint16_t filter(uint8_t filterIndex, uint16_t s)
{
	
	const int numReadings = 10;
	uint16_t* pReading = 0;
	uint16_t total = s;
	
	switch(filterIndex)
	{
		case 0:
			pReading = readings0;
			break;
		case 1:
			pReading = readings1;
			break;
		case 2:
			pReading = readings2;
			break;
		case 3:
			pReading = readings3;
			break;
		case 4:
			pReading = readings4;
			break;
		case 5:
			pReading = readings5;
			break;
		case 6:
			pReading = readings6;
			break;
		case 7:
			pReading = readings7;
			break;
		case 8:
			pReading = readings8;
			break;
		case 9:
			pReading = readings9;
			break;
		default:
			pReading = 0;
	}
	
	// Remove the oldest reading
	for (int i = 0; i < 9; i++)
	{
		pReading[i] = pReading[i+1];
		total += pReading[i];
	}

	// Add the newest reading
	pReading[9] = s;
	
	// Calculate the average
	// Return the average
	return total/numReadings;
	
}