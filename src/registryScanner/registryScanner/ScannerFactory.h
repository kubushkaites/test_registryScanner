#pragma once

#include "IScannerAbstractFactory.h"

class ScannerFactory : public IScannerAbstractFactory
{
public:
	ScannerFactory();
	virtual IScannerSharedPtr createScannerRingZero(const std::wstring& scanningStartPath, const std::wstring& keyToSearch = L"") override;
	virtual IScannerSharedPtr createScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& keyToSearch = L"") override;
	virtual ~ScannerFactory() {}
};

