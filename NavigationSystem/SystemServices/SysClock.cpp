/**
 * @file   SysClock.cpp
 * @version 1.0.0
 * @author SailingRobots team
 * @date   2017
 * @brief  Provides a number of time keeping functions. Can use the GPS to ensure a accurate
 *         time. The Sysclock will use the system time if a GPS time has not been provided.
 *
 */

#include "SysClock.hpp"
#include <stdio.h>
#include <ctime>
#include <sys/time.h>

#define GET_UNIX_TIME() static_cast<long int>(std::time(nullptr))

unsigned long	SysClock::m_LastUpdated = NEVER_UPDATED;
unsigned long 	SysClock::m_LastTimeStamp = 0;
unsigned long 	SysClock::m_LastClockTime = 0;


void SysClock::setTime(unsigned long unixTime)
{
	m_LastUpdated = unixTime;
	m_LastTimeStamp = unixTime;
	m_LastClockTime = GET_UNIX_TIME();
    
    struct timeval tv;
    tv.tv_sec = unixTime; //seconds since 1 jan 1970;
    tv.tv_usec = 0; /* microseconds */
    
    settimeofday(&tv, NULL);
    
    /**
     @todo  check
     if(settimeofday(&tv, NULL) != 0)
        throw std::runtime_error{"failed to update system clock"};
     */
}

// NOTE: Review time!
unsigned long SysClock::unixTime()
{
	if(m_LastUpdated != NEVER_UPDATED)
	{
		m_LastTimeStamp = m_LastTimeStamp + (GET_UNIX_TIME() - m_LastClockTime);
		return m_LastTimeStamp;
	}
	else
	{
		return GET_UNIX_TIME();
	}
}

unsigned int SysClock::millis()
{
	// Get Milliseconds
    timeval curTime;
    
    gettimeofday(&curTime, NULL);
    
    /**
     *  @todo check
    if(gettimeofday(&curTime, NULL) != 0)
        throw std::runtime_error{"failed to get system time"};
     */
    
	return curTime.tv_usec / 1000;
}

std::string SysClock::timeStampStr()
{
	char buff[24]; // Just enough room, see function header yyyy-mm-dd hh:mm:ss.fff

	unsigned long seconds = unixTime();

	time_t unix_time = (time_t)seconds;
	strftime(buff, sizeof(buff), "%F %T", gmtime(&unix_time));

	return std::string(buff);
}

TimeStamp SysClock::timeStamp()
{
	return TimeStamp(unixTime(), millis());
}

std::string SysClock::hh_mm_ss()
{
	char buff[9]; // Just enough room, see function header

	time_t unix_time = (time_t)unixTime();
	strftime(buff, sizeof(buff), "%H%M%S", gmtime(&unix_time));

	return std::string(buff);
}

std::string SysClock::hh_mm_ss_ms()
{
	char buff[9]; // Just enough room, see function header
	char final[13];

	time_t unix_time = (time_t)unixTime();
	strftime(buff, sizeof(buff), "%H:%M:%S", gmtime(&unix_time));
	snprintf(final, sizeof(final), "%s.%03d", buff, millis());

	return std::string(final);
}

std::string SysClock::hh_mm_ss_ms(TimeStamp timeStamp)
{
	char buff[9]; // Just enough room, see function header
	char final[13];

	time_t unix_time = (time_t)timeStamp.unixTime;
	strftime(buff, sizeof(buff), "%H:%M:%S", gmtime(&unix_time));
	snprintf(final, sizeof(final), "%s.%03d", buff, timeStamp.milliseconds);

	return std::string(final);
}

int SysClock::day()
{
	time_t unix_time = (time_t)unixTime();
	tm* time = gmtime(&unix_time); // Statically allocated struct, DO NOT DELETE!
	return time->tm_mday;
}

int SysClock::month()
{
	time_t unix_time = (time_t)unixTime();
	tm* time = gmtime(&unix_time); // Statically allocated struct, DO NOT DELETE!
	return time->tm_mon + 1;
}

int SysClock::year()
{
	time_t unix_time = (time_t)unixTime();
	tm* time = gmtime(&unix_time); // Statically allocated struct, DO NOT DELETE!
	return 1900 + time->tm_year;		
}

 unsigned long SysClock::lastUpdated()
 {
	 return unixTime() - m_LastUpdated;
 }




