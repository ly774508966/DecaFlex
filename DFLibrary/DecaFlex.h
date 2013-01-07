#include <memory>
#include "DecaFlexUSB.h"

// DecaFlex API

class DecaFlex
{
public:

	DecaFlex();
	virtual ~DecaFlex();

	// Attempts to find a USB device
	
	// Attempts to find a Bluetooth device


	// Sets the device into RAW packet mode.
	void SetRAWMode();

	/// Obtains an update
	bool Update();

	/// Returns Left Glove Data
	DECAFLEX_RAWUpdate_EP1_t LeftGlove();
	/// Returns Right Glove Data


protected:
private:

	/// USB (Direct) Implementation
	std::shared_ptr<DecaFlexUSB> USBDevice;

	/// Bluetooth HID Implementation
};