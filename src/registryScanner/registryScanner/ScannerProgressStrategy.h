#pragma once

#include "ScannerProgressToConsole.h"

typedef std::shared_ptr<IScannerProgress> IScannerProgressSharedPtr;

class ScannerProgressStrategy
{
public:
	ScannerProgressStrategy(std::list<IScannerProgressSharedPtr> viewersList);
	virtual ~ScannerProgressStrategy() {};
	void updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys);
	void showSearchResult(uint32_t foundKeys = 0);
	void addProgressViewer(const IScannerProgressSharedPtr viewer);
private:
	std::list<IScannerProgressSharedPtr> mViewersList;
};