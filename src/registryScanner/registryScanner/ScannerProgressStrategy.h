#pragma once

#include "ScannerProgressToConsole.h"


class ScannerProgressStrategy
{
public:
	ScannerProgressStrategy(std::list<IScannerProgress> viewersList);
	virtual ~ScannerProgressStrategy() {};
	void updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys);
	void showSearchResult(uint32_t foundKeys = 0);
	void addProgressViewer(const IScannerProgress& viewer);
private:
	std::list<IScannerProgress> mViewersList;
};