#pragma once

#include "BaseLogger.h"

class LoggerToFile : public BaseLogger
{
public:
	LoggerToFile(IScannerSharedPtr observedScanner);
	virtual ~LoggerToFile() {}
	virtual void onNewScanningResultReceived();
protected:
	virtual void writeLog(std::wstring log) override;
};