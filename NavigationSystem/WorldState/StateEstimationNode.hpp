/**
 * @file    StateEstimationNode.hpp
 *
 * @brief   Estimates the "current" state of the vessel. Collects datas from the GPS and compass
 *          messages. Returns a VesselStateMsg corresponding at the estimated state of the vessel.
 *
 * @details The magnetic variation used to correct the magnetic heading (which yields
 *          true heading) is the one at the next waypoint (setted up into the database)
 *          and not the magnetic variation at the current vessel position. So the
 *          correction won't be perfect when the vessel is far away from the next waypoint.
 */

#ifndef STATEESTIMATIONNODE_HPP
#define STATEESTIMATIONNODE_HPP

#include "../MessageBus/ActiveNode.hpp"
#include "../Messages/CompassDataMsg.h"
#include "../Messages/GPSDataMsg.hpp"
#include "../Messages/StateMessage.h"
#include "../Messages/WaypointDataMsg.hpp"
#include "../SystemServices/Logger.hpp"
#include "../SystemServices/Timer.hpp"

#include <stdint.h>
#include <atomic>
#include <mutex>
#include "../Database/DBHandler.hpp"
#include "../Math/CourseMath.hpp"
#include "../Math/Utility.hpp"

class StateEstimationNode : public ActiveNode {
   public:
    StateEstimationNode(MessageBus& msgBus, DBHandler& dbhandler);
    ~StateEstimationNode();

    bool init();
    void start();
    void stop();
    void processMessage(const Message* msg);

   private:
    ///----------------------------------------------------------------------------------
    /// @brief Updates the values of the parameters from the database.
    ///----------------------------------------------------------------------------------
    void updateConfigsFromDB();

    ///----------------------------------------------------------------------------------
    /// @brief Stores compass data from a CompassDataMsg.
    ///----------------------------------------------------------------------------------
    void processCompassMessage(const CompassDataMsg* msg);

    ///----------------------------------------------------------------------------------
    /// @brief Stores the GPS data from a GPSDataMsg.
    ///----------------------------------------------------------------------------------
    void processGPSMessage(const GPSDataMsg* msg);

    ///----------------------------------------------------------------------------------
    /// @brief Stores the next declination from a WaypointDataMsg.
    ///----------------------------------------------------------------------------------
    void processWaypointMessage(const WaypointDataMsg* msg);

    ///----------------------------------------------------------------------------------
    /// @brief Estimates the vessel state from the sensor datas.
    ///----------------------------------------------------------------------------------
    bool estimateVesselState();

    ///----------------------------------------------------------------------------------
    /// @brief Returns an estimation of the vessel course (angle of the velocity vector).
    /// When the vessel speed is sufficient (higher than m_speed_2), use the course over
    /// ground given by the GPS.
    /// When the vessel speed is not sufficient for the GPS to return good values (lower
    /// than m_speed_2) :
    ///     * speed_1 < VesselSpeed < speed_2 : use a combinaison of vesselHeading and GPSCourse
    ///     * VesselSpeed < speed_1 : use the vesselHeading
    ///----------------------------------------------------------------------------------
    float estimateVesselCourse();

    ///----------------------------------------------------------------------------------
    /// @brief Starts the StateEstimationNode's thread that pumps out VesselStateMsg corresponding
    /// at the estimated state of the vessel.
    ///----------------------------------------------------------------------------------
    static void StateEstimationNodeThreadFunc(ActiveNode* nodePtr);

    DBHandler& m_dbHandler;
    std::mutex m_lock;
    std::atomic<bool> m_Running;

    double m_LoopTime;  // second

    float m_CompassHeading;  // degree [0, 360[ in North-East reference frame (clockwise)
    bool m_GpsOnline;
    double m_GPSLat;
    double m_GPSLon;
    double m_GPSSpeed;            // m/s
    double m_GPSCourse;           // degree [0, 360[ in North-East reference frame (clockwise)
    float m_WaypointDeclination;  // degree

    double m_speed_1;  // m/s
    double m_speed_2;  // m/s

    float m_VesselHeading;  // degree [0, 360[ in North-East reference frame (clockwise)
    double m_VesselLat;
    double m_VesselLon;
    float m_VesselSpeed;   // m/s
    float m_VesselCourse;  // degree [0, 360[ in North-East reference frame (clockwise)
};

#endif /* STATEESTIMATIONNODE_HPP */
