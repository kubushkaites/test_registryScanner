#pragma once

#include "IScanner.h"

class ScannerRingThree : public IScanner
{
public:
	ScannerRingThree(std::wstring scanningStartPath);
	virtual void startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(ScanningResultObserverSharedPtr scannerObserver) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual ~ScannerRingThree() {}
private:
	std::wstring mScanningStartPath;
	std::list<ScanningResultObserverSharedPtr> mScannerObservers;
};