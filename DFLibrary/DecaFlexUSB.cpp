#include "DecaFlexUSB.h"



std::shared_ptr<LibUSB::Device> DecaFlexDeviceFactory( std::shared_ptr<LibUSB::DeviceImpl> pDeviceImpl )
{

	std::shared_ptr<LibUSB::Device> DecaFlexUSBDevice;

	DecaFlexUSBDevice.reset(new DecaFlexUSB(pDeviceImpl));


	return DecaFlexUSBDevice;

}

DecaFlexUSB::DecaFlexUSB( std::shared_ptr<LibUSB::DeviceImpl> pInit ): LibUSB::Device(pInit)
{



}

DecaFlexUSB::~DecaFlexUSB()
{

	Disconnect();
	
}

std::shared_ptr<DecaFlexUSB> DecaFlexUSB::GetDevice()
{

	// Locate DecaFlex device

	std::list<std::shared_ptr<LibUSB::Device>> deviceList = LibUSB::LibUSB::FindDevice(decaflexvendorID, decaflexproductID, DecaFlexDeviceFactory);

	if (deviceList.empty())
	{
		return nullptr;
	}

	std::shared_ptr<DecaFlexUSB> pDevice = std::static_pointer_cast<DecaFlexUSB,LibUSB::Device>(*deviceList.begin());

	return pDevice;
	
}

void DecaFlexUSB::Connect()
{

	// Open device
	Open();

	// Claim interface
	m_pInterface = getActiveConfiguration()->getInterface(0);
	m_pInterface->Claim();

	// Obtain endpoint(s)
	m_pInterruptINEndpoint = m_pInterface->getEndpoint(1);

	// Create transfer object
	m_pInterruptTransfer = std::static_pointer_cast<LibUSB::InterruptTransfer, LibUSB::Transfer>(m_pInterruptINEndpoint->CreateTransfer());

	// Create a transfer buffer
	m_pTransferBuffer.reset(new unsigned char[sizeof(DECAFLEX_RAWUpdate_EP1_t)], [](unsigned char *ptr){ delete [] ptr; });

	m_pInterruptTransfer->setTransferBuffer(m_pTransferBuffer, sizeof(DECAFLEX_RAWUpdate_EP1_t));

	// Start first transfer
	m_pInterruptTransfer->Start();

}

void DecaFlexUSB::Disconnect()
{
	// Stop transfers
	if (m_pInterruptTransfer)
	{
		m_pInterruptTransfer->WaitForCompletion();
	}

	// Release endpoints
	m_pInterruptINEndpoint.reset();

	// Release interfaces
	if(m_pInterface && m_pInterface->isClaimed())
		m_pInterface->Release();


}

void DecaFlexUSB::SetRAWMode()
{
	
	std::shared_ptr<LibUSB::ControlTransfer> pTransfer = std::static_pointer_cast<LibUSB::ControlTransfer, LibUSB::Transfer>(getControlEndpoint()->CreateTransfer());

	pTransfer->SetupPacket(USBCommand_t::RAW_MODE, 0, 0);

	pTransfer->Start();

	if (pTransfer->isComplete() && pTransfer->isSuccessful())
	{
		// RAW Mode set!
	}
	else
	{
		// RAW Mode not set!
		throw std::exception("RAW Mode not set.");
	}

}

bool DecaFlexUSB::GetUpdate()
{

	bool Result = false;
	
	if (m_pInterruptTransfer->isComplete())
	{

		if(m_pInterruptTransfer->isSuccessful())
		{

			// copy results
			m_Update = *(DECAFLEX_RAWUpdate_EP1_t*)(m_pInterruptTransfer->getTransferBuffer().get());
			
			Result = true;
		}

		// Get ready for another transfer
		m_pInterruptTransfer->Reset();
		m_pInterruptTransfer->setTransferBuffer(m_pTransferBuffer, sizeof(DECAFLEX_RAWUpdate_EP1_t));

		// Start transfer
		m_pInterruptTransfer->AsyncStart();

	}

	return Result;

}

DECAFLEX_RAWUpdate_EP1_t DecaFlexUSB::getLeft() const
{

	return m_Update;
	
}
