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

// Finger ADC sensor pins

// Thumb - Proximal (...best way to measure this?)
#define PORT_THUMB_PROX	PORTE
#define DDR_THUMB_PROX	DDRE
#define PIN_THUMB_PROX	PORTE2

// Thumb - Middle
#define PORT_THUMB_MID	PORTE
#define DDR_THUMB_MID	DDRE
#define PIN_THUMB_MID	PORTE2

// Thumb - Distal
#define PORT_THUMB_DIST	PORTE
#define DDR_THUMB_DIST	DDRE
#define PIN_THUMB_DIST	PORTE2

// Index - Proximal
// Index - Middle
// Index - Distal (estimated)

// Middle - Proximal
// Middle - Middle
// Middle - Distal (estimated)


// Ring - Proximal
// Ring - Middle
// Ring - Distal (estimated)

// Pinky - Proximal
// Pinky - Middle
// Pinky - Distal (estimated)


// Onboard battery level sense (ADC)


// "Mode" button input
#define PORT_MODEBTN	PORTE
#define DDR_MODEBTN		DDRE
#define PIN_MODEBTN		PORTE2

// TWI - 12ch TrimDAC