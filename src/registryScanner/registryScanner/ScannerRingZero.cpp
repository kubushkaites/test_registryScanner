#include "ScannerRingZero.h"
#include "LoggerToFile.h"
#include "ScannerProgressStrategy.h"

ScannerRingZero::ScannerRingZero(const std::wstring& scanningStartPath, const std::wstring& searchPattern)
	:IScanner(),
	mScanningStartPath(scanningStartPath),
	mSearchPattern(searchPattern)
{

}

void ScannerRingZero::startScanning()
{
}


void ScannerRingZero::scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos, bool isInitialCall)
{
}

void ScannerRingZero::createWorkerThreads(HKEY hKey, DWORD cSubKeys)
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

std::wstring ScannerRingZero::getFoundKey() const
{
	return std::wstring();
}

std::wstring ScannerRingZero::getFoundKeyPath() const
{
	return std::wstring();
}
