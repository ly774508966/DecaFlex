#include "DecaFlex.h"


DecaFlex::DecaFlex()
{

	// Find a USB Implementation
	USBDevice = DecaFlexUSB::GetDevice();

	if (USBDevice)
	{
		USBDevice->Connect();
	}
}

DecaFlex::~DecaFlex()
{
	
	if (USBDevice)
	{
		USBDevice->Disconnect();
	}
}

void DecaFlex::SetRAWMode()
{
	
	USBDevice->SetRAWMode();

}

bool DecaFlex::Update()
{
	
	if (USBDevice)
	{
		return USBDevice->GetUpdate();
	}

}

DECAFLEX_RAWUpdate_EP1_t DecaFlex::LeftGlove()
{
	if (USBDevice)
	{
		return USBDevice->getLeft();
	}

	DECAFLEX_RAWUpdate_EP1_t update;

	return update;
}
