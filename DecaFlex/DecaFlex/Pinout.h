/*
 * Pinout.h
 *
 * Created: 9/12/2012 1:04:09 AM
 *  Author: Anthony
 */ 

#pragma once

#include <avr/io.h>


/// "User" LED on PE6
#define PORT_USER	PORTE
#define DDR_USER	DDRE
#define PIN_USER	PORTE6

// Phalanx ADC sensor pins

// Thumb - Proximal (...best way to measure this? ...using a flex sensor??)
// #define DIDR_THUMB_PROX	DIDR0
// #define PIN_THUMB_PROX	ADC0D

// Thumb - Middle
#define DIDR_THUMB_MID	DIDR0
#define PIN_THUMB_MID	ADC0D

// Thumb - Distal
#define DIDR_THUMB_DIST	DIDR0
#define PIN_THUMB_DIST	ADC1D

// Index - Proximal
#define DIDR_INDEX_PROX DIDR0
#define PIN_INDEX_PROX ADC4D

// Index - Middle
#define DIDR_INDEX_MID	DIDR0
#define PIN_INDEX_MID	ADC5D

// Index - Distal (estimated)

// Middle - Proximal
#define DIDR_MIDDLE_PROX DIDR0
#define PIN_MIDDLE_PROX ADC6D

// Middle - Middle
#define DIDR_MIDDLE_MID	DIDR0
#define PIN_MIDDLE_MID	ADC7D

// Middle - Distal (estimated)


// Ring - Proximal
#define DIDR_RING_PROX DIDR2
#define PIN_RING_PROX ADC8D

// Ring - Middle
#define DIDR_RING_MID	DIDR2
#define PIN_RING_MID	ADC9D

// Ring - Distal (estimated)

// Pinky - Proximal
#define DIDR_PINKY_PROX DIDR2
#define PIN_PINKY_PROX ADC10D

// Pinky - Middle
#define DIDR_PINKY_MID	DIDR2
#define PIN_PINKY_MID	ADC11D

// Pinky - Distal (estimated)


// Onboard battery level sense (ADC)


// "Mode" button input
#define PORT_MODEBTN	PORTE
#define DDR_MODEBTN		DDRE
#define PIN_MODEBTN		PORTE2

// TWI - 12ch TrimDAC

/// Initialization Function
void init_pins();

/// Output normalization (EP1 specific)
uint16_t setRange(uint16_t input, uint16_t* min, uint16_t* max, uint16_t rangeMin, uint16_t rangeMax);

uint16_t filter(uint8_t filterIndex, uint16_t s);

