/*
 * Endpoints.h
 *
 * Created: 8/5/2012 8:59:35 PM
 *  Author: Anthony
 */ 
#pragma once

#include "LUFA/Drivers/USB/USB.h"

// Force-feedback + display
//#define INTERRUPT_OUT_EPSIZE	8
//#define INTERRUPT_OUT_EPNUM		0x02

// HID-mode, vendor-specific endpoint
#define INTERRUPT_IN_EPSIZE		8
#define INTERRUPT_IN_EPNUM		0x01


// DecaFlex Configuration Descriptor Structure

typedef struct
{

	USB_Descriptor_Configuration_Header_t Config;
	USB_Descriptor_Interface_t			Interface;
	USB_Descriptor_Endpoint_t			InterruptInEndpoint;	// Priority messages from the device
//	USB_Descriptor_Endpoint_t			InterruptOutEndpoint;	// Priority messages to the device

} USB_Descriptor_Configuration_t;

