/**
 * @file   ServerConfigsReceivedMsg.hpp
 *
 * @brief  Notify receivers that new config settings have been downloaded from the server
 *
 */

#ifndef SERVERCONFIGSRECEIVEDMSG_HPP
#define SERVERCONFIGSRECEIVEDMSG_HPP

#include "../MessageBus/Message.hpp"

class ServerConfigsReceivedMsg : public Message {
   public:
    ServerConfigsReceivedMsg(NodeID destinationID, NodeID sourceID)
        : Message(MessageType::ServerConfigsReceived, sourceID, destinationID) {}

    ServerConfigsReceivedMsg()
        : Message(MessageType::ServerConfigsReceived, NodeID::None, NodeID::None) {}

    ServerConfigsReceivedMsg(MessageDeserialiser deserialiser) : Message(deserialiser) {}

    virtual ~ServerConfigsReceivedMsg() {}
};

#endif /* SERVERCONFIGSRECEIVEDMSG_HPP */
