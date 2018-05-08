#pragma once

#include "IScannerAbstractFactory.h"

class ScannerFactory : public IScannerAbstractFactory
{
public:
	ScannerFactory();
	virtual IScannerSharedPtr createScannerRingZero(std::wstring scanningStartPath) override;
	virtual IScannerSharedPtr createScannerRingThree(std::wstring scanningStartPath) override;
	virtual ~ScannerFactory() { std::cout << "~ScannerFactory()" << std::endl; }
};

