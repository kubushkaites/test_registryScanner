// registryScanner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ScannerFactory.h"
#include "ScannerProgressStrategy.h"
#include "ScannerRingZero.h"
#include "ScannerRingThree.h"
#include "LoggerToFile.h"

int main()
{
	std::wstring keyToSearch;
	std::cout << "Enter HKLM registry key to search: " << std::endl;
	std::getline(std::wcin, keyToSearch);

	std::wstring searchPath;
	std::cout << "Enter HKLM registry search path(with empty path HKLM key search will be started from HKLM root)" << std::endl;
	std::getline(std::wcin, searchPath);

	std::shared_ptr<IScannerAbstractFactory> factoryPtr(new ScannerFactory());

	std::shared_ptr<IScanner> scannerRingZeroPtr(factoryPtr->createScannerRingZero(L"sss"));
	std::shared_ptr<IScanner> scannerRingThreePtr(factoryPtr->createScannerRingThree(searchPath, keyToSearch));
		
	std::list<IScannerProgressSharedPtr> scannerProgressList{ IScannerProgressSharedPtr(new ScannerProgressToConsole()) };//scanner progress list contains receivers of information 
																														//about percentage of success of scanning process and info about how many keys were found
	std::shared_ptr<ScannerProgressStrategy> scannerProgressStrategy(new ScannerProgressStrategy(scannerProgressList));

	scannerRingZeroPtr->setScanningProgressStrategy(scannerProgressStrategy);//add to strategy identifiers to know from what class info received;
	scannerRingThreePtr->setScanningProgressStrategy(scannerProgressStrategy);

	std::shared_ptr<IScanningResultObserver> loggerToFileRingZero(new LoggerToFile(scannerRingZeroPtr));//set observed classes for loggers
	std::shared_ptr<IScanningResultObserver> loggerToFileRingThree(new LoggerToFile(scannerRingThreePtr));

	scannerRingZeroPtr->addScannerObserver(loggerToFileRingZero);//set observers for scanners
	scannerRingThreePtr->addScannerObserver(loggerToFileRingThree);

	scannerRingThreePtr->startScanning();

    return 0;
}

