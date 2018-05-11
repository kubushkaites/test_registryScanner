#pragma once

#include "stdafx.h"


class IScannerProgress
{
protected:
	virtual void showProgress() = 0;
public:
	virtual void updateDataToShow(const uint64_t scannedKeys, const uint64_t totalAmountOfKeys) = 0;
	virtual void onErrorOccured(const DWORD errorCode) = 0;
	virtual void searchEnded(const uint64_t foundKeys) = 0;
	virtual ~IScannerProgress(){}

};