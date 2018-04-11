#include <iostream>
#include "CANMarineSensorReceiver.h"
#include "CAN_Services/CANService.h"
#include "Math/Utility.h"
#include "Messages/MarineSensorDataMsg.h"
#include "SystemServices/Logger.h"


const uint8_t ARD_MIN_PH = 0;
const float MIN_PH = 0;
const uint8_t ARD_MAX_PH = 255;
const float MAX_PH = 14;

const uint8_t ARD_MIN_CON = 0;
const float MIN_CON = 5;
const uint32_t ARD_MAX_CON = 4294967295;
const float MAX_CON = 200000;

const uint16_t ARD_MIN_TEMP = 0;
const float MIN_TEMP = -5;
const uint16_t ARD_MAX_TEMP = 65535;
const float MAX_TEMP = 40;

const uint16_t ARD_MIN_ERROR = 0;
const float MIN_ERROR = -5;
const uint16_t ARD_MAX_ERROR = 65535;
const float MAX_ERROR = 40;

#define SUCCESS 0
#define SYNTAX_ERROR 1
#define NOT_READY 2
#define NO_DATA_TO_SEND 3



CANDatalistener::CANDatalistener(MessageBus& messageBus, CANService& canService) :
CANFrameReceiver(canService, 711), m_msgBus(messageBus)
{
}

//+ calculate salinity from mesaurments
//+ add a MarineSensorDataMsg in the same way as MarineSensorNode
void CANDatalistener::processFrame (CanMsg& msg) {



    //provided that msg frameID is 711 nothing else

    uint8_t rawErrorMessage = (msg.data[0]);
    
    Logger logError;
    logError.init("CANMarineSensorReceiver");
 
    /*switch(rawErrorMessage) {
    case SUCCESS :{
            uint8_t rawPh = (msg.data[1]);
            float   ph  = Utility::mapInterval (rawPh,ARD_MIN_PH,ARD_MAX_PH,MIN_PH,MAX_PH); //extract from CanMsg and convert

            uint32_t rawCon = (msg.data[5] << 24 | msg.data[4] << 16 | msg.data[3] << 8 | msg.data[2] );
            float   conductivety = Utility::mapInterval (rawCon,ARD_MIN_CON,ARD_MAX_CON,MIN_CON,MAX_CON); //extract from CanMsg and convert

            uint16_t rawTemp = (msg.data[7] << 8 | msg.data[6]);
            float   temp = Utility::mapInterval (rawTemp,ARD_MIN_TEMP,ARD_MIN_TEMP,MIN_TEMP,MAX_TEMP); //extract from CanMsg and convert

            float   salinity = Utility::calculateSalinity (temp, conductivety);
            MessagePtr marineSensorDataMsg = std::make_unique<MarineSensorDataMsg>(temp, conductivety, ph, salinity);
            m_msgBus.sendMessage(std::move(marineSensorDataMsg));
             break;}       // and exits the switch
    case SYNTAX_ERROR : 
        logError.warning("Syntax Error in CANMarineSensorReceiver");
             break;

    case NOT_READY : 
        logError.warning("CANMarineSensorReceiver is not ready ");
             break;

    case NO_DATA_TO_SEND : 
        logError.warning("Was not able to read CanMsg ErrorMessage 0 to 3 from CANMarineSensorReceiver ");
             break;
             
    default:            
        logError.warning("Was not able to read CanMsg ErrorMessage 0 to 3 from CANMarineSensorReceiver ");
}*/



    if(static_cast<int>(rawErrorMessage)==SUCCESS){
            uint16_t rawPh = (msg.data[1]);
            float   ph  = Utility::mapInterval (rawPh,ARD_MIN_PH,ARD_MAX_PH,MIN_PH,MAX_PH); //extract from CanMsg and convert

            uint16_t rawCon = (msg.data[5] << 24 | msg.data[4] << 16 | msg.data[3] << 8 | msg.data[2] );
            float   conductivety = Utility::mapInterval (rawCon,ARD_MIN_CON,ARD_MAX_CON,MIN_CON,MAX_CON); //extract from CanMsg and convert

            uint16_t rawTemp = (msg.data[7] << 8 | msg.data[6]);
            float   temp = Utility::mapInterval (rawTemp,ARD_MIN_TEMP,ARD_MIN_TEMP,MIN_TEMP,MAX_TEMP); //extract from CanMsg and convert

            float   salinity = Utility::calculateSalinity (temp, conductivety);
            MessagePtr marineSensorDataMsg = std::make_unique<MarineSensorDataMsg>(temp, conductivety, ph, salinity);
            m_msgBus.sendMessage(std::move(marineSensorDataMsg));
    }
    else {
      
    }
          
}
