#pragma once

#include "stdafx.h"

class IScanner;

typedef std::shared_ptr<IScanner> IScannerSharedPtr;

class IScanningResultObserver
{
public:
	virtual void onNewScanningResultReceived() = 0;
	virtual ~IScanningResultObserver() {}
};