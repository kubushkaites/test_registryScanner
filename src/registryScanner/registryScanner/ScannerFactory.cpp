#include "ScannerFactory.h"

#include "ScannerRingZero.h"
#include "ScannerRingThree.h"

ScannerFactory::ScannerFactory()
	:IScannerAbstractFactory()
{
}

IScannerSharedPtr ScannerFactory::createScannerRingZero(const std::wstring& scanningStartPath, const std::wstring& searchPattern)
{
	return IScannerSharedPtr(new ScannerRingZero(scanningStartPath, searchPattern));
}

IScannerSharedPtr ScannerFactory::createScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& searchPattern)
{
	return IScannerSharedPtr(new ScannerRingThree(scanningStartPath, searchPattern));
}