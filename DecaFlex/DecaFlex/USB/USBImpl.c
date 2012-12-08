/*
 * USBImpl.c
 *
 * Created: 8/7/2012 8:50:32 PM
 *  Author: Anthony
 */ 
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include "USBImpl.h"
#include "Protocol.h"
#include "Endpoints.h"
#include "Update.h"
#include "util.h"
#include <stddef.h>


OperatingModes_t operatingMode = MODE_RAW;

/// Performs USB endpoint tasks.
void ServiceUSB(void)
{
	
	if (USB_DeviceState != DEVICE_STATE_Configured)
		return;
	
	// Save endpoint
	uint8_t PrevEndpoint = Endpoint_GetCurrentEndpoint();
	
	// Check for interrupts
	/*
	Endpoint_SelectEndpoint(INTERRUPT_OUT_EPNUM);
		
	if(Endpoint_IsOUTReceived())
	{
				
		
			unsigned char interruptData[16];
			memset(interruptData, '\0', 16);
			
			// Process incoming interrupt packet.
			Endpoint_Read_Stream_LE(interruptData, 16, NULL);
			
			// Acknowledge the packet
			if (!Endpoint_IsReadWriteAllowed())
			{
				// ACK
				Endpoint_ClearOUT();
			}
			
			avrslcd_MoveCursor(2,1);
			printf("%s", interruptData);
			
			returnFire = true;
				
	}
	
	*/

	
	Endpoint_SelectEndpoint(INTERRUPT_IN_EPNUM);
	
	// Test interrupt function
	if(Endpoint_IsConfigured() && Endpoint_IsEnabled())
	{	
	
		// Send return interrupt.
		// if (Endpoint_WaitUntilReady() == ENDPOINT_READYWAIT_NoError)		// Causes a spin-wait!
		if (Endpoint_IsINReady())
		{			
			
			if (operatingMode == MODE_RAW)
			{
				
				// No data ready to go.
				if (!updateReady())
				{				
					// No interrupt pending
					//	Endpoint_ClearIN();		// Omitting this could lead to a timeout, eventually.
					Endpoint_AbortPendingIN();	// NAK a few times, just to prove that it's okay.
				}					
				else
				{	
				
					// Prepare an update message
					DECAFLEX_RAWUpdate_EP1_t Update;
				
					performUpdate(&Update);
				
					// Send update/state data to the host.
					Endpoint_Write_Stream_LE(&Update, sizeof(DECAFLEX_RAWUpdate_EP1_t), NULL);
				
					// Acknowledge the packet
					Endpoint_ClearIN();
				}				
				
			}
		}
		
	}			
	// Restore endpoint
	Endpoint_SelectEndpoint(PrevEndpoint);
}

void GetVersionInformation( VersionInfo_t* Buffer ) 
{
	
	Buffer->FirmwareMajor = 0;
	Buffer->FirmwareMinor = 1;
	
	Buffer->HardwareMajor = 0;
	Buffer->HardwareMinor = 0;
	
}

void ProcessVendorControlRequest()
{
	
	// Process incoming vendor control request
	switch(USB_ControlRequest.bRequest)
	{
		
		case VER_INFO:
		{
			
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			
			// Prepare Version Packet
			VersionInfo_t Buffer;
			GetVersionInformation(&Buffer);
			
			// Send version data to host
			Endpoint_Write_Control_Stream_LE(&Buffer, sizeof(VersionInfo_t));
			Endpoint_ClearOUT();
			
			
		}
		break;
		
		
		case RAW_MODE:
		{
			// Switch to RAW Mode
			
			
			// Acknowledge the operation.
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			Endpoint_ClearStatusStage();	
			
		}			
		break;
			
		case HID_MODE:
		{
			// Switch to HID mode
			
			
			// Acknowledge the operation.
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			Endpoint_ClearStatusStage();
			
		}
		break;
		
	/*	Temporairly leaving in this commented code so that I don't have to dig through LUFA documentation to re-figure all this out.		
		case COMMAND_JTAG:
		{
			
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			
			// Enter JTAG mode
			ESTOP_Set();
			JTAGChain_t* pDeviceChain = JTAG_Mode();
			
			if (pDeviceChain == NULL)
			{
				// Error STALL/NAK?
			} 
			else
			{
				
				// Provide the device chain details to the host
				Endpoint_Write_Control_Stream_LE(pDeviceChain, sizeof(JTAGChain_t) + (pDeviceChain->length * sizeof(JTAGDevice_t)));
				Endpoint_ClearOUT();
				
			}
			
				
		}		
		break;
		
		case COMMAND_Config:
		{
			
			Endpoint_ClearSETUP();	// ACK SETUP Packet
			
			// Receive the configuration command
			unsigned char ConfigurationCommandBuffer[32];
			Endpoint_Read_Control_Stream_LE(ConfigurationCommandBuffer, USB_ControlRequest.wValue);
			Endpoint_ClearIN();
			
			// Dispatch the configuration command.
			avrslcd_MoveCursor(2,1);
			printf("%s", Buffer);
			
		}
		break;
			
		case COMMAND_Reset:
		{	
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			unsigned char Buffer[16];
			Endpoint_Read_Control_Stream_LE(Buffer, 8);
			Endpoint_ClearIN();
			avrslcd_MoveCursor(2,1);
			printf("%s", Buffer);
		}
		break;
					
		case COMMAND_SAFE:
		{
			Endpoint_ClearSETUP();	// ACK SETUP Packet.
			wchar_t Buffer[8] = L"WHASUP?";
			Endpoint_Write_Control_Stream_LE(Buffer, 16);
			Endpoint_ClearOUT();
			avrslcd_MoveCursor(2,1);
			printf("4");
		}			
		break;
					
		case COMMAND_STOP:
			avrslcd_MoveCursor(2,1);
			printf("\"STOP\"");
		break;
					
		case COMMAND_START:
			avrslcd_MoveCursor(2,1);
			printf("\"START\"");
		break;
	*/
		default:
			
		break;
	}
	
}

