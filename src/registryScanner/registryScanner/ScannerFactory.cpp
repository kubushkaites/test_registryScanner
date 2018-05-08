#include "ScannerFactory.h"

#include "ScannerRingZero.h"
#include "ScannerRingThree.h"

ScannerFactory::ScannerFactory()
	:IScannerAbstractFactory()
{
	std::cout << "ScannerFactory()" << std::endl;
}

IScannerSharedPtr ScannerFactory::createScannerRingZero(std::wstring scanningStartPath)
{
	return IScannerSharedPtr(new ScannerRingZero(scanningStartPath));
}

IScannerSharedPtr ScannerFactory::createScannerRingThree(std::wstring scanningStartPath)
{
	return IScannerSharedPtr(new ScannerRingThree(scanningStartPath));
}