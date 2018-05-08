// registryScanner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ScannerFactory.h"

int main()
{
	std::shared_ptr<IScannerAbstractFactory> factoryPtr(new ScannerFactory);
	std::shared_ptr<IScanner> scanner0Ptr(factoryPtr->createScannerRingZero(L"sss"));
	std::shared_ptr<IScanner> scanner3Ptr(factoryPtr->createScannerRingThree(L"sss"));
    return 0;
}

