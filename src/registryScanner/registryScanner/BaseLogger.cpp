#include "BaseLogger.h"

BaseLogger::BaseLogger(IScannerSharedPtr observedScanner)
	:mObservedScanner(observedScanner)
{
}

IScannerSharedPtr BaseLogger::getScanner() const
{
	return mObservedScanner;
}
