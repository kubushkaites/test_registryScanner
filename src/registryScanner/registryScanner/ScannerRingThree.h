#pragma once

#include "IScanner.h"

class ScannerRingThree : public IScanner
{
public:
	ScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& searchPattern = L"");//use default value for making possible just iterate through all the registry also
	virtual void startScanning() override;
	virtual void stopScanning() override;
	virtual void changeScanningStartPath(std::wstring scanningStartPath) override;
	virtual void addScannerObserver(IScanningResultObserverSharedPtr scannerObserver) override;
	virtual void setScanningProgressStrategy(ScannerProgressStrategySharedPtr scannerProgressStrategy) override;
	virtual void notifyOnNewScanningResultReceived() override;
	virtual std::wstring getFoundKey() const;
	virtual std::wstring getFoundKeyPath() const;
	virtual ~ScannerRingThree() {}
protected:
	virtual void scan(HKEY hKey, DWORD regEnumIteratorStartPos, DWORD regEnumIteratorEndPos, bool isInitialCall = false) override;
	virtual void createThreads(HKEY hKey, DWORD cSubKeys) override;
	bool searchForMatching(const std::wstring& key);
private:
	std::mutex mNotifyingMutex;

	std::wstring mScanningStartPath;	
	std::wstring mSearchPattern;
	
	std::wstring mFoundKey;
	std::wstring mFoundPath;

	std::map<std::thread::id, std::wstring> mSubkeysPath;

	ScannerProgressStrategySharedPtr mScannerProgressStrategy;
	std::list<IScanningResultObserverSharedPtr> mScannerObservers;
};