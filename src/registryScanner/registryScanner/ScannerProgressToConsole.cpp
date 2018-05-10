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
	mMinutesMutex.lock();
	mApproximateAmountOfMinutes = static_cast<uint64_t>(10 - ((static_cast<double>(scannedKeys) / totalAmountOfKeys) * 10));
	if (mApproximateAmountOfMinutes < 1)
		mApproximateAmountOfMinutes = 1; //not showing seconds so not showing anything less than 1
	mMinutesMutex.unlock();
	//mKeysMutex.lock();
	//mScannedKeys = scannedKeys;
	//mTotalAmountOfKeys = totalAmountOfKeys;
	//mKeysMutex.unlock();
}

void ScannerProgressToConsole::onErrorOccured(DWORD errorCode)
{
	std::lock_guard<std::mutex> guardWriteToConsoleMutex(mWriteToConsoleMutex);
	system("cls");
	std::cout << "Error occured!!! Error code : " << errorCode << std::endl;
}

void ScannerProgressToConsole::searchEnded(uint64_t foundKeys)
{
	std::lock_guard<std::mutex> guardWriteToConsoleMutex(mWriteToConsoleMutex);

	system("cls");
	isFinished = true;
	std::cout << "Search ended. Amount of keys found : " << foundKeys << std::endl;	
	//mWriteToConsoleMutex.lock();
	//system("cls");
	//isFinished = true;
	//std::cout << "Search ended. Amount of matching keys found : " << foundKeys << std::endl;
	//mWriteToConsoleMutex.unlock();
}

void ScannerProgressToConsole::showProgress()
{	
	while (true) 
	{
		mMinutesMutex.lock();
		mWriteToConsoleMutex.lock();

		if (isFinished == false)
		{
			system("cls");
			std::cout << "Approximate amount of time : ";
			std::cout << mApproximateAmountOfMinutes << " min" << std::endl;
		}
		else
		{
			return;
		}
		mWriteToConsoleMutex.unlock();
		mMinutesMutex.unlock();

		Sleep(300);
	}
	//
	//while (true)
	//{
	//	mWriteToConsoleMutex.lock();
	//	if(isFinished == false)	
	//	{ 
	//		system("cls");
	//		std::cout << "Scanned keys : " << mScannedKeys << "; current total amount of keys found : "<< mTotalAmountOfKeys << std::endl;
	//	}
	//	else
	//	{
	//		return;
	//	}
	//	mWriteToConsoleMutex.unlock();
	//	Sleep(3500);
	//}
	
}

