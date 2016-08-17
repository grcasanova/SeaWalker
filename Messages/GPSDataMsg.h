/****************************************************************************************
 *
 * File:
 * 		GPSDataMsg.h
 *
 * Purpose:
 *		Contains GPS Data.
 *
 * Developer Notes:
 *
 ***************************************************************************************/

#pragma once

#include "Message.h"


enum class GPSMode
{
	NoUpdate = 0,	// Indicates that a update hasn't occured yet
	NoFix,			// Indicates that there is no GPS fix
	LatLonOk,		// Indicates that the latitude/longitude data is good
	LatLonAltOk		// Indicates that the latitude/longitude/altitude data is good
};


class GPSDataMsg : public Message {
public:
	GPSDataMsg(	NodeID destinationID, NodeID sourceID, bool hasFix, bool online, double lat,
				double lon, double unixTime, double speed, double heading, int satCount, GPSMode mode)

		:Message(MessageType::GPSData, sourceID, destinationID), m_HasFix(hasFix), m_Online(online),
		 m_Lat(lat), m_Lon(lon), m_UnixTime(unixTime), m_Speed(speed), m_Heading(heading),
		 m_SatCount(satCount), m_Mode(mode)
	{ }

	GPSDataMsg(	bool hasFix, bool online, double lat, double lon, double unixTime, double speed,
				double heading, int satCount, GPSMode mode)

		:Message(MessageType::GPSData, NodeID::None, NodeID::None), m_HasFix(hasFix), m_Online(online),
		 m_Lat(lat), m_Lon(lon), m_UnixTime(unixTime), m_Speed(speed), m_Heading(heading),
		 m_SatCount(satCount), m_Mode(mode)
	{ }


	GPSDataMsg(MessageDeserialiser deserialiser)
		:Message(deserialiser)
	{
		uint8_t mode = 0;
		if(	!deserialiser.readBool(m_HasFix) ||
			!deserialiser.readBool(m_Online) ||
			!deserialiser.readDouble(m_Lat) ||
			!deserialiser.readDouble(m_Lon) ||
			!deserialiser.readDouble(m_UnixTime) ||
			!deserialiser.readDouble(m_Speed) ||
			!deserialiser.readDouble(m_Heading) ||
			!deserialiser.readInt(m_SatCount) ||
			!deserialiser.readUint8_t(mode))
		{
			m_valid = false;
		}

		m_Mode = (GPSMode)mode;
	}


	virtual ~GPSDataMsg() { }

	bool hasFix() { return m_HasFix; }
	bool gpsOnline() { return m_Online; }
	double latitude() { return m_Lat; }
	double longitude() { return m_Lon; }
	double unixTime() { return m_UnixTime; }
	double speed() { return m_Speed; }
	double heading() { return m_Heading; }
	int satelliteCount() { return m_SatCount; }
	GPSMode gpsMode() { return m_Mode; }

	///----------------------------------------------------------------------------------
	/// Serialises the message into a MessageSerialiser
	///----------------------------------------------------------------------------------
	virtual void Serialise(MessageSerialiser& serialiser) const
	{
		Message::Serialise(serialiser);

		serialiser.serialise(m_HasFix);
		serialiser.serialise(m_Online);
		serialiser.serialise(m_Lat);
		serialiser.serialise(m_Lon);
		serialiser.serialise(m_UnixTime);
		serialiser.serialise(m_Speed);
		serialiser.serialise(m_Heading);
		serialiser.serialise(m_SatCount);
		serialiser.serialise((uint8_t)m_Mode);
	}

private:
	bool	m_HasFix;
	bool	m_Online;
	double	m_Lat;
	double	m_Lon;
	double	m_UnixTime;
	double	m_Speed;
	double	m_Heading;
	int		m_SatCount;
	GPSMode	m_Mode;
};