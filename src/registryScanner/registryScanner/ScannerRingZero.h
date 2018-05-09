#pragma once

#include "IScanner.h"

class ScannerRingZero : public IScanner
{
public:
	ScannerRingZero(std::wstring scanningStartPath, std::wstring searchPattern = L"");//use default value for making possible just iterate through all the registry also);
	virtual void startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(IScanningResultObserverSharedPtr scannerObserver) override;
	virtual void setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual ~ScannerRingZero() {}
protected:
	virtual void scan(HKEY hKey, DWORD regEnumIterator) override;
private:
	std::wstring mScanningStartPath;
	std::wstring mSearchPattern;
	ScannerProgressStrategySharedPtr mScannerProgressStrategy;
	std::list<IScanningResultObserverSharedPtr> mScannerObservers;
};