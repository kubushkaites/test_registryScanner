#pragma once

#include "stdafx.h"

class IScanningResultObserver;

typedef std::shared_ptr<IScanningResultObserver> ScanningResultObserverSharedPtr;

class IScanner
{
public:
	virtual void startScanning() = 0;
	virtual void stopScanning() = 0;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) = 0;
	virtual void addScannerObserver(ScanningResultObserverSharedPtr scannerObserver) = 0;
	virtual void notifyOnNewScanningResultReceived() = 0;
	virtual ~IScanner() {}
};
