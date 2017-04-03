/****************************************************************************************
 *
 * File:
 * 		HardwareGPSDSuite.h
 *
 * Purpose:
 *		A set of unit tests for checking whether the GPS Node is functioning correctly
 *		These set of tests will only work if the GPS is physically attached
 *
 * Developer Notes:
 *
 *
 ***************************************************************************************/

 #pragma once

 #include "../cxxtest/cxxtest/TestSuite.h"
#include "Nodes/GPSDNode.h"
#include "../../MessageBus/MessageBus.h"
#include "SystemServices/Logger.h"
#include "TestMocks/MessageLogger.h"
#include <stdint.h>
#include <thread>

// For std::this_thread
#include <chrono>
#include <thread>

#define WAIT_FOR_MESSAGE		300
#define GPS_TEST_COUNT			2


class HardwareGPSDSuite : public CxxTest::TestSuite {
public:
	GPSDNode* gps;
	std::thread* thr;
	MessageLogger* logger;
	int testCount = 0;

	// Cheeky method for declaring and initialising a static in a header file
	static MessageBus& msgBus()
	{
		static MessageBus* mbus = new MessageBus();
		return *mbus;
	}

	static void runMessageLoop()
	{
		msgBus().run();
	}

	void setUp()
	{
		// Only want to setup them up once in this test, only going to delete them when the program closes and the OS destroys
		// the process's memory
		if(gps == 0)
		{
			Logger::DisableLogging();
			logger = new MessageLogger(msgBus());
			gps = new GPSDNode(msgBus());
			thr = new std::thread(runMessageLoop);
		}
		testCount++;
		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_MESSAGE));
	}

	void tearDown()
	{
		if(testCount == GPS_TEST_COUNT)
		{
			delete gps;
			delete logger;
		}
	}

	void test_GPSInit()
	{
		TS_ASSERT(gps->init());
	}

	void test_GPSThread()
	{
		gps->start();

		std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_FOR_MESSAGE));

		TS_ASSERT(logger->gpsDataReceived())
	}
};