#include "ScannerRingThree.h"
#include "LoggerToFile.h"
#include "ScannerProgressStrategy.h"

ScannerRingThree::ScannerRingThree(std::wstring scanningStartPath, std::wstring searchPattern)
	:IScanner(),
	mScanningStartPath(scanningStartPath),
	mSearchPattern(searchPattern)

{
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

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		mScanningStartPath.c_str(),
		0,
		KEY_READ,
		&hKey) == ERROR_SUCCESS
		)
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

	if (cSubKeys)
	{
		createThreads(hKey, cSubKeys);
	}
}

void ScannerRingThree::createThreads(HKEY hKey, DWORD cSubKeys)
{
	DWORD enumeratorStep;

	if (cSubKeys / 2)
	{
		enumeratorStep = cSubKeys / 2;
	}
	else if (cSubKeys == 1)
	{
		enumeratorStep = 1;
	}

	DWORD startRegEnumIteratorForSecondThread = 0;
	if (enumeratorStep % 2 != 0)
	{
		startRegEnumIteratorForSecondThread = cSubKeys - enumeratorStep;
	}
	else
	{
		startRegEnumIteratorForSecondThread = enumeratorStep;
	}

	//if only one subkey available on current path process it by one thread, else process in two threads
	
	auto taskOneFunc = std::bind(&ScannerRingThree::scan, this, std::placeholders::_1, std::placeholders::_2);
	auto scanTaskOne = std::async(taskOneFunc, hKey, 0, enumeratorStep);

	if (startRegEnumIteratorForSecondThread != 0)
	{
		auto taskTwoFunc = std::bind(&ScannerRingThree::scan, this, std::placeholders::_1, std::placeholders::_2);
		auto scanTaskTwo = std::async(taskTwoFunc, enumeratorStep, cSubKeys);
	}
	

}

void ScannerRingThree::scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos)
{
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

	}
}
