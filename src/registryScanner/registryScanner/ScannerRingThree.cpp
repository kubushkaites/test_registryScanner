#include "ScannerRingThree.h"
#include "LoggerToFile.h"
#include "ScannerProgressStrategy.h"

ScannerRingThree::ScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& searchPattern)
	:IScanner(),
	mScanningStartPath(scanningStartPath),
	mSearchPattern(searchPattern),
	mFoundKey(L""),
	mFoundPath(L"")
{
	checkStartScanningPathAndTruncateIfNeeded();
	//auto totalAmountOfKeysFunc = std::bind(&ScannerRingThree::countTotalAmountOfKeys, this);
	//mCountTotalAmountOfKeysTask = std::async(totalAmountOfKeysFunc);
}

void ScannerRingThree::startScanning()
{
	HKEY hKey;

	const int MAX_KEY_LENGTH = 255;
	const int MAX_VALUE_NAME = 16383;
	
	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD retCode;
	DWORD regOpenKeyErrorCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		mScanningStartPath.c_str(),
		0,
		KEY_READ,
		&hKey);
	if (regOpenKeyErrorCode == ERROR_SUCCESS)
	{						   // Get the class name and the value count. 
		retCode = RegQueryInfoKey(
			hKey,                    // key handle 
			achClass,                // buffer for class name 
			&cchClassName,           // size of class string 
			NULL,                    // reserved 
			&cSubKeys,               // number of subkeys 
			&cbMaxSubKey,            // longest subkey size 
			&cchMaxClass,            // longest class string 
			&cValues,                // number of values for this key 
			&cchMaxValue,            // longest value name 
			&cbMaxValueData,         // longest value data 
			&cbSecurityDescriptor,   // security descriptor 
			&ftLastWriteTime);       // last write time 
	}
	std::cout << "subkeys start amount: " << cSubKeys << std::endl;
	if (cSubKeys !=0 )
	{
		createWorkerThreads(hKey, cSubKeys);
	}
	RegCloseKey(hKey);

	mScannerProgressStrategy->searchEnded(mMatchingKeys);
}

void ScannerRingThree::createWorkerThreads(HKEY hKey, DWORD cSubKeys)
{
	DWORD enumeratorStep;
	bool useTwoThreads;

	if (cSubKeys / 2)
	{
		enumeratorStep = cSubKeys / 2;
		useTwoThreads = true;
	}
	else if (cSubKeys == 1)
	{
		enumeratorStep = 1;
		useTwoThreads = false;
	}
	
	//if only one subkey available on current path process it by one thread, else process in two threads
	
	auto taskOneFunc = std::bind(&ScannerRingThree::scan, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
	auto scanTaskOne = std::thread(taskOneFunc, hKey, 0, enumeratorStep, true);
	
	mSubkeysPath[scanTaskOne.get_id()] = mScanningStartPath;
	
	if (useTwoThreads == false)
	{
		scanTaskOne.join();
	}
	else 
	{
		DWORD startRegEnumIteratorPosForSecondThread = 0;

		if (enumeratorStep % 2 != 0)
		{
			startRegEnumIteratorPosForSecondThread = cSubKeys - enumeratorStep;
		}
		else
		{
			startRegEnumIteratorPosForSecondThread = enumeratorStep;
		}

		auto taskTwoFunc = std::bind(&ScannerRingThree::scan, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
		auto scanTaskTwo = std::thread(taskTwoFunc, hKey, startRegEnumIteratorPosForSecondThread, cSubKeys, true);

		mSubkeysPath[scanTaskTwo.get_id()] = mScanningStartPath;

		scanTaskOne.join();
		scanTaskTwo.join();
	}
}


void ScannerRingThree::scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos, bool isInitialCall)
{

	const int MAX_KEY_LENGTH = 255;
	const int MAX_VALUE_NAME = 16383;

	TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	DWORD    cbName;                   // size of name string 
	TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name 
	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 
	
	DWORD retCode;

	retCode = RegQueryInfoKey(
		hKey,                    // key handle 
		achClass,                // buffer for class name 
		&cchClassName,           // size of class string 
		NULL,                    // reserved 
		&cSubKeys,               // number of subkeys 
		&cbMaxSubKey,            // longest subkey size 
		&cchMaxClass,            // longest class string 
		&cValues,                // number of values for this key 
		&cchMaxValue,            // longest value name 
		&cbMaxValueData,         // longest value data 
		&cbSecurityDescriptor,   // security descriptor 
		&ftLastWriteTime);       // last write time 

	DWORD enumIteratorStartPos = 0;
	DWORD enumIteratorEndPos = 0;
	//std::cout << "cSubKeys : " <<cSubKeys<< std::endl;
	if (isInitialCall)
	{
		enumIteratorStartPos = regEnumIteratorStartPos;
		enumIteratorEndPos = regEnumIteratorEndPos;

		mCountingMutex.lock();
		if (mTotalAmountOfKeys == 0)//to avoid adding the same value two times
		{
			mTotalAmountOfKeys += cSubKeys;
		}
		mCountingMutex.unlock();
	}
	else if (isInitialCall == false)
	{
		enumIteratorStartPos = 0;
		enumIteratorEndPos = cSubKeys;

		mCountingMutex.lock();
		mTotalAmountOfKeys += cSubKeys;
		mCountingMutex.unlock();
	}
	//std::cout << "enumIteratorStartPos : " << enumIteratorStartPos << std::endl;
	//std::cout << "enumIteratorEndPos : " << enumIteratorEndPos << std::endl;
	if (cSubKeys)
	{
		for (;enumIteratorStartPos < enumIteratorEndPos; enumIteratorStartPos++)
		{

			cbName = MAX_KEY_LENGTH;
			retCode = RegEnumKeyEx(hKey, enumIteratorStartPos,
				achKey,
				&cbName,
				NULL,
				NULL,
				NULL,
				&ftLastWriteTime);

			std::wstring keyName(achKey);

			if (bool isMatching = searchForMatching(keyName) || mSearchPattern.empty())
			{
				mNotifyingMutex.lock();

				mFoundKey = keyName;
				mFoundPath = mSubkeysPath[std::this_thread::get_id()];

				notifyOnNewScanningResultReceived();

				++mMatchingKeys;

				mNotifyingMutex.unlock();
			}

			mCountingMutex.lock();
				++mScannedAmountOfKeys;
			mCountingMutex.unlock();

			//update percentage of progress
			mScannerProgressStrategy->updateDataToShow(mScannedAmountOfKeys, mTotalAmountOfKeys);

			if (mSubkeysPath[std::this_thread::get_id()].empty() == true)
			{
				mSubkeysPath[std::this_thread::get_id()] = keyName;
			}
			else
			{
				mSubkeysPath[std::this_thread::get_id()] += L"\\" + keyName;
			}			
			/*_tprintf(TEXT("(%d) %s\n"), enumIteratorStartPos + 1, mSubkeysPath[std::this_thread::get_id()].c_str());
			if (retCode == ERROR_SUCCESS)		*/
			{
			/*	std::cout << "retCode : ERROR_SUCCESS" << std::endl;*/
				HKEY additionalKey;

				DWORD regOpenKeyErrorCode = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
					mSubkeysPath[std::this_thread::get_id()].c_str(),
					0,
					KEY_READ,
					&additionalKey);
				if (regOpenKeyErrorCode == ERROR_SUCCESS)
				{
					/*std::cout << "RegOpenKeyEx : ERROR_SUCCESS" << std::endl;*/
					/*_tprintf(TEXT("(%d) %s\n"), enumIteratorStartPos + 1, mSubkeysPath[std::this_thread::get_id()].c_str());*/
					
					scan(additionalKey, enumIteratorStartPos, enumIteratorEndPos);
					RegCloseKey(additionalKey);
					
					restorePreviousPathState();//restore after recurse
				}
				else if (regOpenKeyErrorCode == ERROR_PATH_NOT_FOUND || regOpenKeyErrorCode == ERROR_FILE_NOT_FOUND)
				{
					//system("cls");
					/*std::wcout << mSubkeysPath[std::this_thread::get_id()] <<"  ERROR_PATH_NOT_FOUND || ERROR_FILE_NOT_FOUND" << std::endl;
					std::terminate();*/
				}
				else if(regOpenKeyErrorCode == ERROR_ACCESS_DENIED)
				{
					//skip
					/*std::wcout << mSubkeysPath[std::this_thread::get_id()] << L" ERROR_ACCESS_DENIED" << std::endl;*/

					restorePreviousPathState();
				}
			}
		}
	}
}

bool ScannerRingThree::searchForMatching(const std::wstring& key)
{
	std::size_t found = key.find(mSearchPattern);
	if (found != std::string::npos)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ScannerRingThree::restorePreviousPathState()
{
	std::size_t found = mSubkeysPath[std::this_thread::get_id()].rfind(L"\\");
	if (found != std::string::npos)//restore string
	{
		mSubkeysPath[std::this_thread::get_id()].erase(found, mSubkeysPath[std::this_thread::get_id()].length() - found + 1);
	}
	else
	{
		std::wcout << "RESETTING!!!" << mSubkeysPath[std::this_thread::get_id()] << std::endl;
		mSubkeysPath[std::this_thread::get_id()].clear();
	}
}

void ScannerRingThree::checkStartScanningPathAndTruncateIfNeeded()
{
	std::size_t found = mScanningStartPath.find(L"HKLM\\");
	if (found != std::string::npos)
	{
		mScanningStartPath.erase(found, found + 5);
		std::wcout << mScanningStartPath;
	}
}

void ScannerRingThree::stopScanning()
{
}

void ScannerRingThree::changeScanningStartPath(std::wstring scanningStartPath)
{
	stopScanning();
	mScanningStartPath = scanningStartPath;
	startScanning();
}

void ScannerRingThree::addScannerObserver(IScanningResultObserverSharedPtr scannerObserver)
{
	mScannerObservers.push_back(scannerObserver);
}

void ScannerRingThree::setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy)
{
	mScannerProgressStrategy = scannerProgressStrategy;
}

void ScannerRingThree::notifyOnNewScanningResultReceived()
{
	for (auto& observer : mScannerObservers)
	{
		observer->onNewScanningResultReceived();
	}
}

std::wstring ScannerRingThree::getFoundKey() const
{
	return mFoundKey;
}

std::wstring ScannerRingThree::getFoundKeyPath() const
{
	return mFoundPath;
}
