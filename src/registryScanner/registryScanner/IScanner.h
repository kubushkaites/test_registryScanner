#pragma once

#include "stdafx.h"

class IScanningResultObserver;

class ScannerProgressStrategy;

typedef std::shared_ptr<IScanningResultObserver> IScanningResultObserverSharedPtr;
typedef std::shared_ptr<ScannerProgressStrategy> ScannerProgressStrategySharedPtr;

class IScanner
{
public:
	virtual void startScanning() = 0;
	virtual void stopScanning() = 0;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) = 0;
	virtual void addScannerObserver(IScanningResultObserverSharedPtr scannerObserver) = 0;
	virtual void setScanningProgressStrategy(ScannerProgressStrategySharedPtr) = 0;
	virtual void notifyOnNewScanningResultReceived() = 0;
	virtual ~IScanner() {}
protected:
	virtual void scan(HKEY hKey,DWORD regEnumIterator) = 0;
};
