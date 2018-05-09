#pragma once

#include "IScanner.h"

class ScannerRingThree : public IScanner
{
public:
	ScannerRingThree(std::wstring scanningStartPath, std::wstring searchPattern = L"");//use default value for making possible just iterate through all the registry also
	virtual void startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(IScanningResultObserverSharedPtr scannerObserver) override;
	virtual void setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual ~ScannerRingThree() {}
protected:
	virtual void scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos) override;
	virtual void createThreads(HKEY hKey, DWORD cSubKeys) override;
private:
	std::wstring mScanningStartPath;
	std::wstring mSearchPattern;
	ScannerProgressStrategySharedPtr mScannerProgressStrategy;
	std::list<IScanningResultObserverSharedPtr> mScannerObservers;
};