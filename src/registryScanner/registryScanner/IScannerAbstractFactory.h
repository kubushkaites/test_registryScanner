#pragma once

#include "stdafx.h"

class IScanner;

typedef std::shared_ptr<IScanner> IScannerSharedPtr;

class IScannerAbstractFactory
{
public:
	IScannerAbstractFactory() { std::cout << "IScannerAbstractFactory()" << std::endl; }
	virtual IScannerSharedPtr createScannerRingZero(std::wstring scanningStartPath) = 0;
	virtual IScannerSharedPtr createScannerRingThree(std::wstring scanningStartPath) = 0;
	virtual ~IScannerAbstractFactory() { std::cout << "~IScannerAbstractFactory()" << std::endl; }
};