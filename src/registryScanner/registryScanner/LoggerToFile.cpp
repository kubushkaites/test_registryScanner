#include "LoggerToFile.h"

LoggerToFile::LoggerToFile(IScannerSharedPtr observedScanner)
	:BaseLogger(observedScanner)
{

}

void LoggerToFile::onNewScanningResultReceived()
{
	
}

void LoggerToFile::writeLog(std::wstring log)
{

}
