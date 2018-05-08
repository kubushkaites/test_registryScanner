#pragma once

#include "IScanningResultObserver.h"

class BaseLogger : public IScanningResultObserver
{
public:
	BaseLogger(IScannerSharedPtr observedScanner);
	virtual ~BaseLogger() {}
protected:
	virtual void writeLog(std::wstring key) = 0;
	IScannerSharedPtr getScanner() const;
private:
	IScannerSharedPtr mObservedScanner;
};
