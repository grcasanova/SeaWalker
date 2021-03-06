/****************************************************************************************
 *
 * File:
 * 		WindVoter.cpp
 *
 * Purpose:
 *		
 *
 * License:
 *      This file is subject to the terms and conditions defined in the file 
 *      'LICENSE.txt', which is part of this source code package.
 *
 ***************************************************************************************/


#include "WindVoter.h"
#include "../SystemServices/Logger.hpp"
#include "../Math/Utility.hpp"


///----------------------------------------------------------------------------------
WindVoter::WindVoter( int16_t maxVotes, int16_t weight )
    :ASRVoter( maxVotes, weight, "Wind" )
{

}

///----------------------------------------------------------------------------------
const ASRCourseBallot& WindVoter::vote( const BoatState_t& boatState )
{
    const int TACK_ANGLE = 45;
    uint16_t twd = Utility::getTrueWindDirection(boatState.windDir, boatState.windSpeed, 
                boatState.speed, boatState.heading, trueWindBuffer, TW_BUFFER_SIZE);

    // Set everything to 66% of the max vote
    for( int i = 0; i < 360; i+= ASRCourseBallot::COURSE_RESOLUTION )
    {
        courseBallot.set( i, courseBallot.maxVotes() / 1.5 );
    }

    int16_t twdBearingDiff = abs(Utility::headingDifference( boatState.waypointBearing, twd ));
    
    // Encourage tacking if necessary 
    if( twdBearingDiff <= TACK_ANGLE )
    {
        if ( abs( Utility::headingDifference( boatState.heading, twd + TACK_ANGLE ) ) < 
             abs( Utility::headingDifference( boatState.heading, twd - TACK_ANGLE ) ) )
        {
            courseBallot.add( twd + TACK_ANGLE, courseBallot.maxVotes() );
        }
        else
        {
            courseBallot.add( twd - TACK_ANGLE, courseBallot.maxVotes() );
        }
    }

    // Add votes to the direction the boat is facing, less cost to change the vessel.
    for( int i = 0; i < 8; i += ASRCourseBallot::COURSE_RESOLUTION )
    {
        courseBallot.add( boatState.heading + i, (( 8 - i ) / 8) * (courseBallot.maxVotes() / 10) );
        courseBallot.add( boatState.heading - i, (( 8 - i ) / 8) * (courseBallot.maxVotes() / 10) );
    }

    // Set 0 to courses into the no go zone.
    for( int i = 0; i < TACK_ANGLE; i+= ASRCourseBallot::COURSE_RESOLUTION )
    {
        courseBallot.set( twd + i, 0 );
        courseBallot.set( twd - i, 0 );
    }

    return courseBallot;
}
