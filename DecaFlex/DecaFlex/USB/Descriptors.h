/*
 * Descriptors.h
 *
 * Created: 8/5/2012 3:36:25 PM
 *  Author: Anthony
 */ 
#pragma once

#include <stdint.h>
#include <avr/pgmspace.h>
#include "LUFA/Drivers/USB/USB.h"



const USB_Descriptor_Device_t PROGMEM DeviceDescriptor =
{
	
	.Header					= { .Size = sizeof(USB_Descriptor_Device_t), .Type = DTYPE_Device},
	
	.USBSpecification		= VERSION_BCD(02.00),
	.Class					= 0xFF,
	.SubClass				= 0xAA,
	.Protocol				= 0x00,
	
	.Endpoint0Size			= FIXED_CONTROL_ENDPOINT_SIZE,
	
	.VendorID				= 0x04D8,
	.ProductID				= 0xFB93,
	.ReleaseNumber			= VERSION_BCD(00.01),	// Increment this
	
	.ManufacturerStrIndex	= 0x01,
	.ProductStrIndex		= 0x02,
	.SerialNumStrIndex		= 0x03,
	
	.NumberOfConfigurations	= FIXED_NUM_CONFIGURATIONS
	
};

const USB_Descriptor_String_t PROGMEM LanguageString =
{
	.Header					= {.Size = USB_STRING_LEN(1), .Type = DTYPE_String},
	.UnicodeString			= {LANGUAGE_ID_ENG}
};

const USB_Descriptor_String_t PROGMEM ManufacturerString =
{
	.Header					= {.Size = USB_STRING_LEN(13), .Type = DTYPE_String},
	.UnicodeString			= L"ZarthCode LLC"
};

const USB_Descriptor_String_t PROGMEM ProductString =
{
 .Header                 = {.Size = USB_STRING_LEN(18), .Type = DTYPE_String},
 .UnicodeString          = L"DecaFlex VR Gloves"
};

/// Unique serial number for the device.
const USB_Descriptor_String_t PROGMEM DeviceSerialString =
{
.Header                 = {.Size = USB_STRING_LEN(36), .Type = DTYPE_String},
.UnicodeString          = L"572185B4-F7FD-435D-91B0-F094162B18A6"
};




uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex, const void** const DescriptorAddress);