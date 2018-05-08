#include "ScannerRingThree.h"
#include "LoggerToFile.h"

ScannerRingThree::ScannerRingThree(std::wstring scanningStartPath)
	:mScanningStartPath(scanningStartPath)
{
}

void ScannerRingThree::startScanning()
{
}

void ScannerRingThree::stopScanning()
{
}

void ScannerRingThree::changeScanningStartPath(std::wstring scanningStartPath)
{
	stopScanning();
	mScanningStartPath = scanningStartPath;
	startScanning();
}

void ScannerRingThree::addScannerObserver(ScanningResultObserverSharedPtr scannerObserver)
{
	mScannerObservers.push_back(scannerObserver);
}

void ScannerRingThree::notifyOnNewScanningResultReceived()
{
	for (auto& observer : mScannerObservers)
	{

	}
}
