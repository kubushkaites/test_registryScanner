#pragma once

#include "IScannerProgress.h"

class ScannerProgressToConsole : public IScannerProgress
{
public:
	ScannerProgressToConsole();
	virtual void updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys) override;
	virtual void onErrorOccured(DWORD errorCode) override;
	virtual void searchEnded(uint64_t foundKeys) override;
	virtual ~ScannerProgressToConsole() {}
protected:
	virtual void showProgress() override;
private:
	uint64_t mApproximateAmountOfMinutes = 0;
	uint64_t mScannedKeys = 0;
	uint64_t mTotalAmountOfKeys = 0;
	uint64_t mFoundKeys = 0;

	bool isFinished = false;

	std::mutex mMinutesMutex;
	std::mutex mWriteToConsoleMutex;
	std::thread mShowPercentsThr;
};