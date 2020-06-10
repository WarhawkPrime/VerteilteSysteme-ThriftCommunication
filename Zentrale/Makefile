#target name
TARGET	:= main

#other src files and obj definition
SRC	:= FileManagement.cpp HTTP_Server.cpp Skynet.cpp UDP_server.cpp main.cpp
THRIFT_SRC	:= SendSensordataService.cpp SendSensordataService_server_skeleton.cpp verbindung_constants.cpp verbindung_types.cpp thriftServer.cpp
OBJ	:= $(patsubst %.cpp,%.o, $(SRC))

#include directories
THRIFT_DIR	:= /usr/local/include/THRIFT_DIR
BOOST_DIR	:= /usr/local/include/boost
ALL	:= /usr/local/include

INCLUDE	:= -I$(THRIFT_DIR) -I$(BOOST_DIR) -I$(ALL)

#used libraries
LIB	:= -L/usr/local/lib/ -L/usr/local/lib/ -lthrift -L/usr/local/lib/ -lthriftnb -L/usr/local/lib/ -lthriftz

#compiler and flags
#CXX	:= /usr/bin/gcc
#CXXFLAGS	:= -ansin -g -Wall

#default case
all: $(TARGET)

#specify build rule
%.o: %.cpp
	$(CXX) $(INCLUDE) $(LIB) -c $< -o $@

#compile target rule
$(TARGET): $(TARGET).o $(OBJ)
	$(CXX) $^ -o $@ $(INCLUDE) $(LIB)

#remove binaries and .o
clean:
	$(RM) *.o $(TARGET)
