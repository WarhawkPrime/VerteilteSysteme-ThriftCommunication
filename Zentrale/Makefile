#target name
TARGET	:= main

#other src files and obj definition
SRC	:= FileManagement.cpp HTTP_Server.cpp Skynet.cpp UDP_server.cpp main.cpp SendSensordataService.cpp SendSensordataService_server.skeleton.cpp verbindung_constants.cpp verbindung_types.cpp thriftServer.cpp MQTT_Server.cpp
OBJ	:= $(patsubst %.cpp,%.o, $(SRC))

#include directories
THRIFT_DIR	:= /usr/local/include/THRIFT_DIR
BOOST_DIR	:= /usr/local/include/boost
MQTT_DIR	:= /usr/local/include/mqtt
ALL		:= /usr/local/include

INCLUDE	:= -I$(THRIFT_DIR) -I$(BOOST_DIR) -I$(MQTT_DIR) -I$(ALL)

#used libraries
LIB	:= -L/usr/local/lib/ -L/usr/local/lib/ -lthrift -L/usr/local/lib/ -lthriftnb -L/usr/local/lib/ -lthriftz  -L/usr/lib/x86_64-linux-gnu/ -levent -L/usr/local/lib/ -lpaho-mqtt3a -L/usr/local/lib/ -lpaho-mqtt3as -L/usr/local/lib/ -lpaho-mqtt3c -L/usr/local/lib/ -lpaho-mqtt3cs -L/usr/local/lib/ -lpaho-mqttpp3 

#compiler and flags
#CXX	:= /usr/bin/gcc
#CPPFLAGS	:= -std=c++14 

#default case
all: $(TARGET)

#specify build rule
%.o: %.cpp
	$(CXX) $(INCLUDE) $(LIB) -c $< -o $@

#compile target rule
$(TARGET): $(TARGET).o $(OBJ)
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB)

#remove binaries and .o
.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
