#pragma once

#include "stdafx.h"

class IScannerProgress
{
protected:
	virtual void showProgress() = 0;
public:
	virtual void updateDataToShow(uint64_t scannedKeys, uint64_t totalAmountOfKeys) = 0;
	virtual void searchEnded(uint64_t foundKeys) = 0;
	virtual ~IScannerProgress(){}

};