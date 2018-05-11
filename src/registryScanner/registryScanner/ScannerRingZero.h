#pragma once

#include "IScanner.h"

class ScannerRingZero : public IScanner
{
public:
	ScannerRingZero(const std::wstring& scanningStartPath, const std::wstring& searchPattern = L"");//use default value for making possible just iterate through all the registry also);
	virtual bool startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(IScanningResultObserverSharedPtr scannerObserver) override;
	virtual void setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual std::wstring getFoundKey() const;
	virtual std::wstring getFoundKeyPath() const;
	virtual ~ScannerRingZero() {}
protected:
	virtual void scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos, bool isInitialCall = false) override;
	virtual void createWorkerThreads(HKEY hKey, DWORD cSubKeys) override;
private:
	std::wstring mScanningStartPath;
	std::wstring mSearchPattern;
	ScannerProgressStrategySharedPtr mScannerProgressStrategy;
	std::list<IScanningResultObserverSharedPtr> mScannerObservers;
};