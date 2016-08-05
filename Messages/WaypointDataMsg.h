/****************************************************************************************
 *
 * File:
 * 		WaypointDataMsg.h
 *
 * Purpose:
 *		A WaypointDataMsg contains waypoint data such as id, longitude, latitude, declination and radius
 *
 * Developer Notes:
 *
 *
 ***************************************************************************************/

#pragma once

#include "Message.h"


class WaypointDataMsg : public Message {
public:
	WaypointDataMsg(NodeID destinationID, NodeID sourceID, int nextId, double nextLongitude, double nextLatitude, int nextDeclination, int nextRadius,
                        int prevId, double prevLongitude, double prevLatitude, int prevDeclination, int prevRadius)
		:Message(MessageType::WaypointData, sourceID, destinationID), m_nextId(nextId), m_nextLongitude(nextLongitude), m_nextLatitude(nextLatitude),
                         m_nextDeclination(nextDeclination), m_nextRadius(nextRadius), m_prevId(prevId), m_prevLongitude(prevLongitude), m_prevLatitude(prevLatitude),
                         m_prevDeclination(prevDeclination), m_prevRadius(prevRadius)
	{ }

	WaypointDataMsg(int nextId, double nextLongitude, double nextLatitude, int nextDeclination, int nextRadius,
                        int prevId, double prevLongitude, double prevLatitude, int prevDeclination, int prevRadius)
		:Message(MessageType::WaypointData, NodeID::None, NodeID::None), m_nextId(nextId), m_nextLongitude(nextLongitude), m_nextLatitude(nextLatitude),
                         m_nextDeclination(nextDeclination), m_nextRadius(nextRadius), m_prevId(prevId), m_prevLongitude(prevLongitude), m_prevLatitude(prevLatitude),
                         m_prevDeclination(prevDeclination), m_prevRadius(prevRadius)

	{ }

	WaypointDataMsg(MessageDeserialiser deserialiser)
	:Message(deserialiser)
	{
		if(	!deserialiser.readInt(m_nextId) ||
			!deserialiser.readDouble(m_nextLongitude) ||
			!deserialiser.readDouble(m_nextLatitude) ||
			!deserialiser.readInt(m_nextDeclination) ||
			!deserialiser.readInt(m_nextRadius) ||
			!deserialiser.readInt(m_prevId) ||
			!deserialiser.readDouble(m_prevLongitude) ||
			!deserialiser.readDouble(m_prevLatitude) ||
			!deserialiser.readInt(m_prevDeclination) ||
			!deserialiser.readInt(m_prevRadius))
		{
			m_valid = false;
		}
	}

	virtual ~WaypointDataMsg() { }


    int     nextId()            { return m_nextId; }
    double  nextLongitude()     { return m_nextLongitude; }
    double  nextLatitude()      { return m_nextLatitude; }
    int     nextDeclination()   { return m_nextDeclination; }
    int     nextRadius()        { return m_nextRadius; }

    int     prevId()            { return m_prevId; }
    double  prevLongitude()     { return m_prevLongitude; }
    double  prevLatitude()      { return m_prevLatitude; }
    int     prevDeclination()   { return m_prevDeclination; }
    int     prevRadius()        { return m_prevRadius; }

    ///----------------------------------------------------------------------------------
	/// Serialises the message into a MessageSerialiser
	///----------------------------------------------------------------------------------
	virtual void Serialise(MessageSerialiser& serialiser) const
	{
		Message::Serialise(serialiser);

		serialiser.serialise(m_nextId);
		serialiser.serialise(m_nextLongitude);
		serialiser.serialise(m_nextLatitude);
		serialiser.serialise(m_nextDeclination);
		serialiser.serialise(m_nextRadius);
		serialiser.serialise(m_prevId);
		serialiser.serialise(m_prevLongitude);
		serialiser.serialise(m_prevLongitude);
		serialiser.serialise(m_prevDeclination);
		serialiser.serialise(m_prevRadius);
	}

private:

    int     m_nextId;
    double  m_nextLongitude;
    double  m_nextLatitude;
    int     m_nextDeclination;
    int     m_nextRadius;

    int     m_prevId;
    double  m_prevLongitude;
    double  m_prevLatitude;
    int     m_prevDeclination;
    int     m_prevRadius;
};
