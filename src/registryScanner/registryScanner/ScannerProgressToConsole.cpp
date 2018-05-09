#include "ScannerProgressToConsole.h"

ScannerProgressToConsole::ScannerProgressToConsole()
	:IScannerProgress()
{
	auto func = std::bind(&ScannerProgressToConsole::showProgress, this);
	mShowPercentsThr = std::thread(func);
	mShowPercentsThr.detach();
}

void ScannerProgressToConsole::updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys)
{
	mPercentsVarMutex.lock();
	mPercentOfSuccess = (static_cast<double>(scannedKeys) / totalAmountOfKeys) * 100;
	mPercentsVarMutex.unlock();
}

void ScannerProgressToConsole::searchEnded(uint64_t foundKeys)
{
	mPercentsVarMutex.lock();

	mPercentOfSuccess = 100;
	system("cls");
	std::cout << "Search ended. Amount of keys found : " << foundKeys << std::endl;
	
	mPercentsVarMutex.unlock();
}

void ScannerProgressToConsole::showProgress()
{	
	while (true) 
	{
		mPercentsVarMutex.lock();

		if (mPercentOfSuccess != 100)
		{
			system("cls");
			std::cout << "Current percentage : " << mPercentOfSuccess << " % " << std::endl;
		}
		else
		{
			return;
		}
		mPercentsVarMutex.unlock();
		
		Sleep(50);
	}
}

