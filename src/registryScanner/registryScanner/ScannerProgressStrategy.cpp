#include "ScannerProgressStrategy.h"

ScannerProgressStrategy::ScannerProgressStrategy(std::list<IScannerProgressSharedPtr> viewersList)
	:mViewersList(viewersList)
{
}

void ScannerProgressStrategy::updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys)
{
	for (auto& item : mViewersList)
	{
		item->updateDataToShow(scannedKeys, totalAmountOfKeys);
	}
}

void ScannerProgressStrategy::searchEnded(uint64_t foundKeys)
{
	for (auto& item : mViewersList)
	{
		item->searchEnded(foundKeys);
	}
}

void ScannerProgressStrategy::onErrorOccured(DWORD errorCode)
{
}

void ScannerProgressStrategy::addProgressViewer(const IScannerProgressSharedPtr viewer)
{
	mViewersList.push_back(viewer);
}
