#pragma once

#include "BaseLogger.h"

class LoggerToFile : public BaseLogger
{
public:
	LoggerToFile(IScannerSharedPtr observedScanner);
	virtual ~LoggerToFile() {}
	virtual void onNewScanningResultReceived();
protected:
	virtual void writeLog(const std::wstring& log) override;
private:
	std::wfstream logFile;
	std::mutex mWriteToFileMutex;
};