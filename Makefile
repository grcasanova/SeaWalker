#######################################################
#
#    Aland Sailing Robot
#    ===========================================
#    sailingrobot
#    -------------------------------------------
#
#######################################################

CC = g++
FLAGS = -Wall -pedantic -Werror
LIBS = -lsqlite3 -lgps -lrt -lwiringPi -lcurl

COURSE = coursecalculation/CourseCalculation.o 
DB = dbhandler/DBHandler.o  dbhandler/JSON.o
COMMAND = ruddercommand/RudderCommand.o sailcommand/SailCommand.o 
MAESTRO = servocontroller/MaestroController.o servocontroller/ServoObject.o servocontroller/SensorObject.o 
CV7 = windsensor/WindSensorController.o windsensor/AdapterWaleswind.o windsensor/AdapterCV7.o
GPS = gps/GPSReader.o gps/MockGPSReader.o
HTTP = httpsync/HTTPSync.o

OBJECTS = $(COURSE) $(DB) $(COMMAND) $(MAESTRO) $(CV7) $(GPS) $(HTTP)
SOURCES = SailingRobot.cpp example.cpp
HEADERS = SailingRobot.h
FILE = sr



all : coursecalculation dbhandler ruddercommand sailcommand servocontroller windsensor gps httpsync $(FILE)

coursecalculation :
	cd coursecalculation && $(MAKE)

dbhandler :
	cd dbhandler && $(MAKE)

ruddercommand :
	cd ruddercommand && $(MAKE)

sailcommand :
	cd sailcommand && $(MAKE)

servocontroller :
	cd servocontroller && $(MAKE)

windsensor :
	cd windsensor && $(MAKE)

gps :
	cd gps && $(MAKE)

httpsync :
	cd httpsync && $(MAKE)

$(FILE) : $(SOURCES) $(HEADERS) $(OBJECTS)
	$(CC) $(SOURCES) $(OBJECTS) $(FLAGS) $(LIBS) -o $(FILE)
