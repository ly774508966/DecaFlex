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

/// 

/// Pose Data
typedef struct {
	
	uint16_t X;
	uint16_t Y;
	uint16_t Z;

} vector3x16_t;

typedef struct
{

	vector3x16_t accel;
	vector3x16_t gyro;

} imu_t;


// Raw data packet
typedef struct {

	// IMU - 3-Axis Gyro
	imu_t wrist;

	// Fingers
	vector3x16_t thumb;
	vector3x16_t index;
	vector3x16_t middle;
	vector3x16_t ring;
	vector3x16_t pinky;

	imu_t forearm;

} DECAFLEX_HAND_RAW_T;

// Orientation
typedef struct
{

	int16_t pitch;
	int16_t roll;
	int16_t yaw;

	int16_t sway;	// X Axis
	int16_t surge;	// Y axis
	int16_t heave;	// Z axis

} ORIENTATION_T;

/// Finger Orientation (accelerometer)
typedef struct
{

	vector3x16_t proximal;
	vector3x16_t middle;
	vector3x16_t distal;

} FINGER_T;

/// Hand Orientation packet
typedef struct
{
	/// Forearm Orientation
	ORIENTATION_T forearm;
	
	/// Wrist Orientation
	ORIENTATION_T wrist;

	/// Thumb
	FINGER_T thumb;

	/// Index
	FINGER_T index;

	/// Middle
	FINGER_T middle;

	/// Ring
	FINGER_T ring;

	/// Pinky
	FINGER_T pinky;
	

} DECAFLEX_HAND_ORIENTATION_T;



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