#pragma once


#include <gtest/gtest.h>

class IScanner;

class scannerTest : public ::testing::Test {
protected:
	virtual void SetUp() override;
	virtual void TearDown() override;
	
	IScanner* mScanner;
};