#pragma once

#include "Protocol.h"


void ServiceUSB(void);

void ProcessVendorControlRequest(void);

void GetVersionInformation(VersionInfo_t* Buffer);