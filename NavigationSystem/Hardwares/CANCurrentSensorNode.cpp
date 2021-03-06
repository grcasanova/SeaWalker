/****************************************************************************************
*
* File:
* 		CANCurrentSensorNode.cpp
*
* Purpose:
*		 Process messages from the current sensors via the CAN Services .
*
* Developer Notes:
*		 The CAN frame id numbers that this node subscribes to are:
*			600
*
***************************************************************************************/

#include "CANCurrentSensorNode.h"
#include "CAN_Services/CanBusCommon/CanUtility.h"
#include "../MessageBus/MessageTypes.hpp"
#include "CAN_Services/CanBusCommon/CanMessageHandler.h"

const float DATA_OUT_OF_RANGE = -2000; // as uint16_t, cannot use -2000.

CANCurrentSensorNode::CANCurrentSensorNode(MessageBus& messageBus, DBHandler& dbhandler, CANService& canService) :
ActiveNode(NodeID::CANCurrentSensor, messageBus), CANFrameReceiver(canService, {MSG_ID_CURRENT_SENSOR_DATA,MSG_ID_CURRENT_SENSOR_DATA_POWER_UNIT}), m_LoopTime (0.5), m_db(dbhandler)
{
        m_current = DATA_OUT_OF_RANGE;
        m_voltage = DATA_OUT_OF_RANGE;
        //m_element = "undefined";
	messageBus.registerNode(*this, MessageType::ServerConfigsReceived);

}

CANCurrentSensorNode::~CANCurrentSensorNode(){

}

bool CANCurrentSensorNode::init() {
	updateConfigsFromDB();
	return true;
}

void CANCurrentSensorNode::updateConfigsFromDB()
{
    //m_LoopTime = m_db.retrieveCellAsDouble("config_can_arduino","1","loop_time");
}

void CANCurrentSensorNode::processMessage (const Message* message){
	if(message->messageType() == MessageType::ServerConfigsReceived)
	{
		updateConfigsFromDB();
	}
}

void CANCurrentSensorNode::processFrame (CanMsg& msg) {
    //Logger::info("Received current sensor readings from CanBus");
    Float16Compressor fltCompressor;
	CanMessageHandler messageHandler(msg);
	uint16_t comp_current, comp_voltage;

	if (messageHandler.getMessageId() == MSG_ID_CURRENT_SENSOR_DATA ||
        messageHandler.getMessageId() == MSG_ID_CURRENT_SENSOR_DATA_POWER_UNIT ||
        messageHandler.getMessageId() == MSG_ID_CURRENT_SENSOR_DATA_BOX)
    {
        // Use get data instead(int)? Parse data here or add the routine in another file?
        messageHandler.getData(&comp_current, CURRENT_SENSOR_CURRENT_DATASIZE);
        messageHandler.getData(&comp_voltage, CURRENT_SENSOR_VOLTAGE_DATASIZE);

        m_current = fltCompressor.decompress(comp_current);
        m_voltage = fltCompressor.decompress(comp_voltage);
        
        //m_element = SAILDRIVE;        //TO TRY
        m_element = (SensedElement)((uint8_t)msg.id - (uint8_t)720);        //TO TRY
        MessagePtr currentSensorDataMsg = std::make_unique<CurrentSensorDataMsg>(static_cast<float>(m_current),
     		           static_cast<float>(m_voltage), static_cast<SensedElement>(m_element));//, static_cast<getSensedElementStrm_element.>);
//        m_msgBus.sendMessage(std::move(currentSensorDataMsg));
        Logger::info("Current sensor data: Current: %lf , Voltage: %lf , Sensor: %d \n",m_current,m_voltage,m_element);
    }
}


void CANCurrentSensorNode::start() {
	runThread(CANCurrentSensorNodeThreadFunc);
}

void CANCurrentSensorNode::CANCurrentSensorNodeThreadFunc(ActiveNode* nodePtr) {


	CANCurrentSensorNode* node = dynamic_cast<CANCurrentSensorNode*> (nodePtr);
	Timer timer;
	timer.start();

	while(true) {

		node->m_lock.lock();
                // Don´t forget modifs here
//		if( not (node->m_voltage == DATA_OUT_OF_RANGE &&  node->m_current == DATA_OUT_OF_RANGE))
				// Skipped for now  && node->m_element == "undefined"))
//		{
			MessagePtr currentSensorData = std::make_unique<CurrentSensorDataMsg>( node->m_current, 
				node->m_voltage, node->m_element);
			node->m_MsgBus.sendMessage(std::move(currentSensorData));
//		}
		node->m_lock.unlock();

		timer.sleepUntil(node->m_LoopTime);
		timer.reset();
	}
}
