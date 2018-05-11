#pragma once

#include "ScannerProgressToConsole.h"

typedef std::shared_ptr<IScannerProgress> IScannerProgressSharedPtr;

class ScannerProgressStrategy
{
public:
	ScannerProgressStrategy(const std::list<IScannerProgressSharedPtr> viewersList);
	virtual ~ScannerProgressStrategy() {};
	void updateDataToShow(const uint64_t scannedKeys, const uint64_t totalAmountOfKeys);
	void searchEnded(const uint64_t foundKeys = 0);
	void onErrorOccured(const DWORD errorCode);
	void addProgressViewer(const IScannerProgressSharedPtr viewer);
private:
	std::list<IScannerProgressSharedPtr> mViewersList;
};