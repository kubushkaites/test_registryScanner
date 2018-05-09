#pragma once

#include "stdafx.h"

class IScanner;

typedef std::shared_ptr<IScanner> IScannerSharedPtr;

class IScannerAbstractFactory
{
public:
	IScannerAbstractFactory() {}
	virtual IScannerSharedPtr createScannerRingZero(const std::wstring& scanningStartPath, const std::wstring& searchPattern = L"") = 0;
	virtual IScannerSharedPtr createScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& searchPattern = L"") = 0;
	virtual ~IScannerAbstractFactory() {}
};