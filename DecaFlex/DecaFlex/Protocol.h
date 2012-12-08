/*
 * Protocol.h
 * DecaFlex Protocol Structures
 * Created: 12/7/2012 1:47:51 PM
 *  Author: Anthony
 */ 


#ifndef PROTOCOL_H_
#define PROTOCOL_H_

#include <stdint.h>



/// RAW Sensor data
typedef struct 
	{
		
		uint8_t SequenceID;				// Indicates change in data.
		uint8_t BatteryStatus;			// Battery level
										// AUX buttons
			
		// IMU - 3-Axis Accelerometer
		uint16_t Accel_X;
		uint16_t Accel_Y;
		uint16_t Accel_Z;
		
		// IMU - 3-Axis Gyro
		uint16_t Gyro_X;
		uint16_t Gyro_Y;
		uint16_t Gyro_Z;
		
		// Flex Sensors - Phalanges 
		uint16_t Thumb_Proximal;	// Later prototypes will provide more proximal data.
		uint16_t Thumb_Middle;
		uint16_t Thumb_Distal;		// Distal is estimated in this prototype
		
		uint16_t Index_Proximal;
		uint16_t Index_Middle;
		uint16_t Index_Distal;		// Distal is estimated in this prototype
		
		uint16_t Middle_Proximal;
		uint16_t Middle_Middle;
		uint16_t Middle_Distal;		// Distal is estimated in this prototype
		
		uint16_t Ring_Proximal;
		uint16_t Ring_Middle;
		uint16_t Ring_Distal;		// Distal is estimated in this prototype
		
		uint16_t Pinky_Proximal;
		uint16_t Pinky_Middle;
		uint16_t Pinky_Distal;		// Distal is estimated in this prototype
	
	} DECAFLEX_RAWUpdate_EP1_t;

/// USB Commands

typedef enum
	{
	
		HID_MODE,	// Interpret programmed/stored gestures (default)
		RAW_MODE,	// Return raw data packets
		VER_INFO	// Return device version information
	
	} USBCommand_t;
	
typedef enum
	{
		
		MODE_HID,
		MODE_RAW	
			
	} OperatingModes_t;
	
typedef struct  
	{
		
		uint8_t HardwareMajor;
		uint8_t HardwareMinor;
		uint8_t FirmwareMajor;
		uint8_t FirmwareMinor;
		
	}VersionInfo_t;
		
#endif /* PROTOCOL_H_ */