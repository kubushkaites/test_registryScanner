#pragma once

#include "IScanner.h"

class ScannerRingThree : public IScanner
{
public:
	ScannerRingThree(const std::wstring& scanningStartPath, const std::wstring& searchPattern = L"");//use default value for making possible just iterate through all the registry also
	virtual bool startScanning() override;
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
	virtual void createWorkerThreads(HKEY hKey, DWORD cSubKeys) override;
private:
	void tryToNotifyAboutFoundPattern(const std::wstring& keyName);
	bool searchForMatching(const std::wstring& key);
	void makeNextSubkeyPath(const std::wstring& keyName);
	void restorePreviousPathState();
	void checkStartScanningPathAndTruncateIfNeeded();
private:
	std::mutex mNotifyingMutex;
	std::mutex mCountingMutex;

	std::wstring mScanningStartPath;
	std::wstring mSearchPattern;
	
	std::wstring mFoundKey;
	std::wstring mFoundPath;

	std::future<void> mCountTotalAmountOfKeysTask;

	std::map<std::thread::id, std::wstring> mSubkeysPath;
	std::map<std::wstring, DWORD> mScanningErrors;

	uint64_t mScannedAmountOfKeys = 0;
	uint64_t mMatchingKeys = 0;
	uint64_t mTotalAmountOfKeys = 0;
	

	ScannerProgressStrategySharedPtr mScannerProgressStrategy;
	std::list<IScanningResultObserverSharedPtr> mScannerObservers;
};