#pragma once

#include "ScannerProgressToConsole.h"

typedef std::shared_ptr<IScannerProgress> IScannerProgressSharedPtr;

class ScannerProgressStrategy
{
public:
	ScannerProgressStrategy(std::list<IScannerProgressSharedPtr> viewersList);
	virtual ~ScannerProgressStrategy() {};
	void updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys);
	void searchEnded(uint64_t foundKeys = 0);
	void addProgressViewer(const IScannerProgressSharedPtr viewer);
private:
	std::list<IScannerProgressSharedPtr> mViewersList;
};