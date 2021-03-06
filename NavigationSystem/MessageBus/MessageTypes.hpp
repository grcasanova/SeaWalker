/**
 * @file    MessageTypes.hpp
 *
 * @brief   Message types expressed as numberic ID and string
 *
 * @details     Provides a enum containing all the message types. Used in the base message class
 *              so that when a message pointer is passed around you know what type of message to
 *              cast it to.
 *
 */

#ifndef MESSAGETYPES_HPP
#define MESSAGETYPES_HPP

#include <string>

// REFACTOR
enum class MessageType {
    DataRequest = 0,
    WindData,
    CompassData,
    GPSData,
    PowerTrackMsg,
    ServerConfigsReceived,
    ServerWaypointsReceived,
    LocalConfigChange,
    LocalWaypointChange,
    ArduinoData,
    VesselState,
    WaypointData,
    ObstacleVector,
    LidarData,
    CourseData,
    ExternalControl,
    RequestCourse,
    StateMessage,
    WindState,
    LocalNavigation,
    ASPireActuatorFeedback,
    MarineSensorData,
    AISData,
    WingSailCommand,
    RudderCommand,
    SailCommand,
    DataCollectionStart,
    DataCollectionStop,
    CurrentSensorData,
    PowerOffCommand
};

inline std::string msgToString(MessageType msgType) {
    switch (msgType) {
        case MessageType::PowerOffCommand:
            return "PowerOffCommand";
        case MessageType::DataRequest:
            return "DataRequest";
        case MessageType::WindData:
            return "WindData";
        case MessageType::CompassData:
            return "CompassData";
        case MessageType::GPSData:
            return "GPSData";
        case MessageType::ServerConfigsReceived:
            return "ServerConfigReceived";
        case MessageType::ServerWaypointsReceived:
            return "ServerWaypointsReceived";
        case MessageType::LocalConfigChange:
            return "LocalConfigChange";
        case MessageType::LocalWaypointChange:
            return "LocalWaypointChange";
        case MessageType::ArduinoData:
            return "ArduinoData";
        case MessageType::VesselState:
            return "VesselState";
        case MessageType::WaypointData:
            return "WaypointData";
        case MessageType::ObstacleVector:
            return "ObstacleVector";
        case MessageType::LidarData:
            return "LidarData";
        case MessageType::CourseData:
            return "CourseData";
        case MessageType::ExternalControl:
            return "ExternalControl";
        case MessageType::RequestCourse:
            return "RequestCourse";
        case MessageType::StateMessage:
            return "StateMessage";
        case MessageType::WindState:
            return "WindState";
        case MessageType::LocalNavigation:
            return "LocalNavigation";
        case MessageType::ASPireActuatorFeedback:
            return "ASPireActuatorFeedback";
        case MessageType::MarineSensorData:
            return "MarineSensorData";
        case MessageType::AISData:
            return "AISData";
        case MessageType::WingSailCommand:
            return "WingSailCommand";
        case MessageType::RudderCommand:
            return "RudderCommand";
        case MessageType::SailCommand:
            return "SailCommand";
        case MessageType::DataCollectionStart:
            return "DataCollectionStart";
        case MessageType::DataCollectionStop:
            return "DataCollectionStop";
        case MessageType::CurrentSensorData:
            return "CurrentSensorData";
        case MessageType::PowerTrackMsg:
            return "PowerTrackMsg";
            break;
    }
    return "";
}

#endif /* MESSAGETYPES_HPP */
