#include "ScannerRingThree.h"
#include "LoggerToFile.h"
#include "ScannerProgressStrategy.h"

ScannerRingThree::ScannerRingThree(std::wstring scanningStartPath)
	:IScanner(),
	mScanningStartPath(scanningStartPath)
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

void ScannerRingThree::addScannerObserver(IScanningResultObserverSharedPtr scannerObserver)
{
	mScannerObservers.push_back(scannerObserver);
}

void ScannerRingThree::setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy)
{
	mScannerProgressStrategy = scannerProgressStrategy;
}

void ScannerRingThree::notifyOnNewScanningResultReceived()
{
	for (auto& observer : mScannerObservers)
	{

	}
}
