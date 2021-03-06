/**
 * @file    MessageSerialiser.hpp
 *
 * @brief   Serialises a message into a block of bytes
 *
 */

#ifndef MESSAGESERIALISER_HPP
#define MESSAGESERIALISER_HPP

#include "MessageTypes.hpp"
#include "NodeIDs.hpp"
#include <stdint.h>
#include <string>

#define MAX_MESSAGE_SIZE 256

class MessageSerialiser {
   public:
    MessageSerialiser() : m_ptr(0) {}

    ///----------------------------------------------------------------------------------
    /// @brief Serialises the data into a byte buffer.
    ///----------------------------------------------------------------------------------
    void serialise(uint8_t data);
    void serialise(uint16_t data);
    void serialise(uint32_t data);
    void serialise(int data);
    void serialise(float data);
    void serialise(double data);
    void serialise(bool data);
    void serialise(MessageType data);
    void serialise(NodeID data);
    void serialise(uint8_t* data, uint8_t size);

    ///----------------------------------------------------------------------------------
    /// @brief Returns a pointer to the data.
    ///----------------------------------------------------------------------------------
    uint8_t* data() { return m_data; }

    ///----------------------------------------------------------------------------------
    /// @brief Returns the number of bytes the data takes up.
    ///----------------------------------------------------------------------------------
    uint8_t size() { return m_ptr; }

   private:
    uint8_t m_data[MAX_MESSAGE_SIZE];
    uint8_t m_ptr;
};

#endif /* MESSAGESERIALISER_HPP */

