#include "ScannerRingZero.h"
#include "LoggerToFile.h"

ScannerRingZero::ScannerRingZero(std::wstring scanningStartPath)
	: mScanningStartPath(scanningStartPath)
{

}

void ScannerRingZero::startScanning()
{
}

void ScannerRingZero::stopScanning()
{
}

void ScannerRingZero::changeScanningStartPath(std::wstring scanningStartPath)
{
	stopScanning();
	mScanningStartPath = scanningStartPath;
	startScanning();
}

void ScannerRingZero::addScannerObserver(ScanningResultObserverSharedPtr scannerObserver)
{
	mScannerObservers.push_back(scannerObserver);
}

void ScannerRingZero::notifyOnNewScanningResultReceived()
{
	for (auto& observer : mScannerObservers)
	{
		
	}
}
