#pragma once

#include "IScanner.h"

class ScannerRingZero : public IScanner
{
public:
	ScannerRingZero(std::wstring scanningStartPath);
	virtual void startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(ScanningResultObserverSharedPtr scannerObserver) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual ~ScannerRingZero() {}
private:
	std::wstring mScanningStartPath;
	std::list<ScanningResultObserverSharedPtr> mScannerObservers;
};