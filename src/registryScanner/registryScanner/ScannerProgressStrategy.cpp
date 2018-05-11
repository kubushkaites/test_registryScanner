#include "ScannerProgressStrategy.h"

ScannerProgressStrategy::ScannerProgressStrategy(const std::list<IScannerProgressSharedPtr> viewersList)
	:mViewersList(viewersList)
{
}

void ScannerProgressStrategy::updateDataToShow(const uint64_t scannedKeys, const uint64_t totalAmountOfKeys)
{
	if (mViewersList.empty() == false)
	{
		for (auto& item : mViewersList)
		{
			item->updateDataToShow(scannedKeys, totalAmountOfKeys);
		}
	}
}

void ScannerProgressStrategy::searchEnded(const uint64_t foundKeys)
{
	if (mViewersList.empty() == false)
	{
		for (auto& item : mViewersList)
		{
			item->searchEnded(foundKeys);
		}
	}
}

void ScannerProgressStrategy::onErrorOccured(const DWORD errorCode)
{
	if (mViewersList.empty() == false)
	{
		for (auto& item : mViewersList)
		{
			item->onErrorOccured(errorCode);
		}
	}
}

void ScannerProgressStrategy::addProgressViewer(const IScannerProgressSharedPtr viewer)
{
	mViewersList.push_back(viewer);
}
