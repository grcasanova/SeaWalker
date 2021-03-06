/**
 * @file    HTTPSyncNode.hpp
 *
 * @brief   Handles retrieval and sending of logs, waypoints and configs between database and server.
 *          Also notifies messagebus when new serverdata arrives.
 *
 */

#ifndef HTTPSYNCNODE_HPP
#define HTTPSYNCNODE_HPP

#include "../Database/DBHandler.hpp"
#include "../MessageBus/ActiveNode.hpp"
#include "../SystemServices/Logger.hpp"

#include <atomic>
#include <chrono>
#include <string>
#include <thread>

class HTTPSyncNode : public ActiveNode {
   public:
    HTTPSyncNode(MessageBus& msgBus, DBHandler& dbhandler);

    virtual ~HTTPSyncNode() {}

    ///----------------------------------------------------------------------------------
    /// Retrieves server settings from database and initialises curl
    ///
    ///----------------------------------------------------------------------------------
    bool init();
    void start();
    void stop();

    ///----------------------------------------------------------------------------------
    /// Pushes waypoints or configurations on new local changes
    ///----------------------------------------------------------------------------------
    void processMessage(const Message* message);
    ///----------------------------------------------------------------------------------
    /// Push functions: sends local data to server using curl
    ///----------------------------------------------------------------------------------
    bool pushDatalogs();
    bool pushWaypoints();
    bool pushConfigs();
    ///----------------------------------------------------------------------------------
    /// Updates local waypoints using new server data if any
    ///----------------------------------------------------------------------------------
    bool getWaypointsFromServer();

    ///----------------------------------------------------------------------------------
    /// Same as above but for configuration data
    ///----------------------------------------------------------------------------------
    bool getConfigsFromServer();

   private:
    ///----------------------------------------------------------------------------------
    /// Sends server request in curl format - used for all syncing functionality
    ///----------------------------------------------------------------------------------
    bool performCURLCall(std::string data, std::string call, std::string& response);

    bool checkIfNewConfigs();
    bool checkIfNewWaypoints();

    ///----------------------------------------------------------------------------------
    /// Node thread: Calls all syncing functions while running
    ///----------------------------------------------------------------------------------
    static void HTTPSyncThread(ActiveNode* nodePtr);

    void updateConfigsFromDB();

    ///----------------------------------------------------------------------------------
    /// Convenience function: creates curl call from argument and returns response (json data)
    ///----------------------------------------------------------------------------------
    std::string getData(std::string call);

    bool m_initialised;

    std::string m_shipID;
    std::string m_shipPWD;
    std::string m_serverURL;
    std::string m_endpoint;

    bool m_reportedConnectError;

    ///----------------------------------------------------------------------------------
    /// Determines whether or not to clear all local logs after a successful push to server
    ///----------------------------------------------------------------------------------
    bool m_removeLogs;
    double m_LoopTime;  // units : seconds (ex : 0.5 s)
    int m_pushOnlyLatestLogs;

    std::atomic<bool> m_Running;
    DBHandler& m_dbHandler;
};

#endif /* HTTPSYNCNODE_HPP */

