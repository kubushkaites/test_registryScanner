#include "ScannerProgressToConsole.h"

ScannerProgressToConsole::ScannerProgressToConsole()
{
}

void ScannerProgressToConsole::updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys)
{
	uint32_t allCountOfKeys = scannedKeys + remainedKeys;
	double percentOfSuccess = (static_cast<double>(scannedKeys) / allCountOfKeys) * 100;
	showProgress(percentOfSuccess);
}

void ScannerProgressToConsole::showSearchResult(uint32_t foundKeys)
{
	std::cout << "Search operation ended, keys found : " << foundKeys << std::endl;
}

void ScannerProgressToConsole::showProgress(double percents)
{
	std::cout << "Current scanning progress : " << percents << std::endl;
}
