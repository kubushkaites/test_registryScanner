#pragma once

#include "IScannerProgress.h"

class ScannerProgressToConsole : public IScannerProgress
{
public:
	ScannerProgressToConsole();
	virtual void updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys) override;
	virtual void showSearchResult(uint32_t foundKeys) override;
	virtual ~ScannerProgressToConsole() {}
protected:
	virtual void showProgress(double percents) override;
};