#include "ScannerRingZero.h"
#include "LoggerToFile.h"
#include "ScannerProgressStrategy.h"

ScannerRingZero::ScannerRingZero(std::wstring scanningStartPath, std::wstring searchPattern)
	:IScanner(),
	mScanningStartPath(scanningStartPath),
	mSearchPattern(searchPattern)
{

}

void ScannerRingZero::startScanning()
{
}


void ScannerRingZero::scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos)
{
}

void ScannerRingZero::createThreads(HKEY hKey, DWORD cSubKeys)
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

void ScannerRingZero::addScannerObserver(IScanningResultObserverSharedPtr scannerObserver)
{
	mScannerObservers.push_back(scannerObserver);
}

void ScannerRingZero::setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy)
{
	mScannerProgressStrategy = scannerProgressStrategy;
}

void ScannerRingZero::notifyOnNewScanningResultReceived()
{
	for (auto& observer : mScannerObservers)
	{
		
	}
}