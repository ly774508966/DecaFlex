/*
 * Pinout.h
 *
 * Created: 9/12/2012 1:04:09 AM
 *  Author: Anthony
 */ 

#pragma once


/// "User" LED on PE6
#define PORT_USER	PORTE
#define DDR_USER	DDRE
#define PIN_USER	PORTE6

// Phalanx ADC sensor pins

// Thumb - Proximal (...best way to measure this?)
#define PORT_THUMB_PROX	PORTF
#define DDR_THUMB_PROX	DDRF
#define PIN_THUMB_PROX	PORTF0

// Thumb - Middle
#define PORT_THUMB_MID	PORTF
#define DDR_THUMB_MID	DDRF
#define PIN_THUMB_MID	PORTF1

// Thumb - Distal
#define PORT_THUMB_DIST	PORTF
#define DDR_THUMB_DIST	DDRF
#define PIN_THUMB_DIST	PORTF4

// Index - Proximal
#define PORT_INDEX_PROX	PORTF
#define DDR_INDEX_PROX DDRF
#define PIN_INDEX_PROX PORTF5

// Index - Middle
#define PORT_INDEX_MID	PORTF
#define DDR_INDEX_MID	DDRF
#define PIN_INDEX_MID	PORTF6

// Index - Distal (estimated)

// Middle - Proximal
#define PORT_MIDDLE_PROX	PORTF
#define DDR_MIDDLE_PROX DDRF
#define PIN_MIDDLE_PROX PORTF7

// Middle - Middle
#define PORT_MIDDLE_MID	PORTD
#define DDR_MIDDLE_MID	DDRD
#define PIN_MIDDLE_MID	PORTD4

// Middle - Distal (estimated)


// Ring - Proximal
#define PORT_RING_PROX	PORTD
#define DDR_RING_PROX DDRD
#define PIN_RING_PROX PORTD6

// Ring - Middle
#define PORT_RING_MID	PORTD
#define DDR_RING_MID	DDRD
#define PIN_RING_MID	PORTD7

// Ring - Distal (estimated)

// Pinky - Proximal
#define PORT_PINKY_PROX	PORTB
#define DDR_PINKY_PROX DDRB
#define PIN_PINKY_PROX PORTB4

// Pinky - Middle
#define PORT_PINKY_MID	PORTB
#define DDR_PINKY_MID	DDRB
#define PIN_PINKY_MID	PORTB5

// Pinky - Distal (estimated)


// Onboard battery level sense (ADC)


// "Mode" button input
#define PORT_MODEBTN	PORTE
#define DDR_MODEBTN		DDRE
#define PIN_MODEBTN		PORTE2

// TWI - 12ch TrimDAC