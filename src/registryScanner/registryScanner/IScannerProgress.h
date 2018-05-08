#pragma once

#include "stdafx.h"

class IScannerProgress
{
protected:
	virtual void showProgress(double percents) = 0;
public:
	virtual void updateDataToShow(uint32_t scannedKeys, uint32_t remainedKeys) = 0;
	virtual void showSearchResult(uint32_t foundKeys) = 0;
	virtual ~IScannerProgress(){}

};