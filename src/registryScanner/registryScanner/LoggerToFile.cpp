#include "LoggerToFile.h"
#include "ScannerRingZero.h"
#include "ScannerRingThree.h"

LoggerToFile::LoggerToFile(IScannerSharedPtr observedScanner)
	:BaseLogger(observedScanner)
{
	logFile.open("..\\PathsAndKeys.txt", std::fstream::app);
}

void LoggerToFile::onNewScanningResultReceived()
{
	mWriteToFileMutex.lock();

	std::cout << "LoggerToFile::NEW SCANNING RESULT RECEIVED!!!" << std::endl;

	std::wcout<<"Found Key: "<<getScanner()->getFoundKey()<<std::endl;
	std::wcout << "Found Key registry path: " << getScanner()->getFoundKeyPath() << std::endl;

	std::wstring writeToFile = getScanner()->getFoundKeyPath() + L" | " + getScanner()->getFoundKey();

	writeLog(writeToFile);
}

void LoggerToFile::writeLog(const std::wstring& log)
{
	logFile << log << std::endl;

	mWriteToFileMutex.unlock();
}
