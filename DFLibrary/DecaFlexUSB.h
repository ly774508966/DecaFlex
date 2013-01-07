
#include "libusbpp.h"
#include "../DecaFlex/DecaFlex/Protocol.h"

// USB identifiers

#define decaflexvendorID 0x04D8
#define decaflexproductID 0xFB93


std::shared_ptr<LibUSB::Device> DecaFlexDeviceFactory(std::shared_ptr<LibUSB::DeviceImpl> pDeviceImpl);


class DecaFlexUSB : public LibUSB::Device
{
public:

	static std::shared_ptr<DecaFlexUSB> GetDevice();

	DecaFlexUSB(std::shared_ptr<LibUSB::DeviceImpl> pInit);
	virtual ~DecaFlexUSB();

	void Connect();

	void Disconnect();


	/// Place the device in RAW Mode
	void SetRAWMode();

	/// Obtain a device update
	bool GetUpdate();

	DECAFLEX_RAWUpdate_EP1_t getLeft() const;


private:

	/// Default interface
	std::shared_ptr<LibUSB::Interface> m_pInterface;

	/// Interrupt IN Endpoint
	std::shared_ptr<LibUSB::Endpoint> m_pInterruptINEndpoint;

	/// Data Transfer Object
	std::shared_ptr<LibUSB::InterruptTransfer> m_pInterruptTransfer;

	/// Data Transfer buffer
	std::shared_ptr<unsigned char> m_pTransferBuffer;

	/// Latest Update data
	DECAFLEX_RAWUpdate_EP1_t m_Update;
};