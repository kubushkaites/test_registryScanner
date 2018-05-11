#include "scannerTest.h"

#include <ScannerRingThree.h>
#include <ScannerProgressStrategy.h>
#include <LoggerToFile.h>

void scannerTest::SetUp()
{
	std::wstring keyToSearch;
	std::cout << "Enter HKLM registry key to search: " << std::endl;
	std::getline(std::wcin, keyToSearch);

	std::wstring searchPath;
	std::cout << "Enter HKLM registry search path(with empty path HKLM key search will be started from HKLM root)" << std::endl;
	std::getline(std::wcin, searchPath);

	mScanner = new ScannerRingThree(searchPath, keyToSearch);
}

void scannerTest::TearDown()
{
	delete mScanner;
}

TEST_F(scannerTest, checkScanner)
{
	ASSERT_TRUE(mScanner->startScanning());
}
