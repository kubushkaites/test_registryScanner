#include "ScannerProgressStrategy.h"

ScannerProgressStrategy::ScannerProgressStrategy(std::list<IScannerProgress> viewersList)
	:mViewersList(viewersList)
{
}

void ScannerProgressStrategy::updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys)
{
	for (auto& item : mViewersList)
	{
		item.updateDataToShow(scannedKeys, remainedKeys);
	}
}

void ScannerProgressStrategy::showSearchResult(uint32_t foundKeys)
{
	for (auto& item : mViewersList)
	{
		item.showSearchResult(foundKeys);
	}
}

void ScannerProgressStrategy::addProgressViewer(const IScannerProgress & viewer)
{
	mViewersList.push_back(viewer);
}
