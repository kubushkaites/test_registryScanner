#pragma once

#include "IScannerProgress.h"

class ScannerProgressToConsole : public IScannerProgress
{
public:
	ScannerProgressToConsole();
	virtual void updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys) override;
	virtual void searchEnded(uint64_t foundKeys) override;
	virtual ~ScannerProgressToConsole() {}
protected:
	virtual void showProgress() override;
private:
	uint64_t mPercentOfSuccess = 0;
	uint64_t mFoundKeys = 0;
	std::mutex mPercentsVarMutex;
	std::mutex mWriteToConsoleMutex;
	std::thread mShowPercentsThr;
};