#target name
TARGET	:= main

#other src files and obj definition
SRC	:= Sensor.cpp Sensor_Management.cpp UDP_Socket.cpp main.cpp
OBJ	:= $(patsubst %.cpp,%.o, $(SRC))

#include directories
#THRIFT_DIR	:= /usr/local/include/THRIFT_DIR
#BOOST_DIR	:= /usr/local/include/boost
#ALL	:= /usr/local/include

#INCLUDE	:= -I$(THRIFT_DIR) -I$(BOOST_DIR) -I$(ALL)

#used libraries
#LIB	:= -L/usr/local/lib/ -L/usr/local/lib/ -lthrift -L/usr/local/lib/ -lthriftnb -L/usr/local/lib/ -lthriftz -L/usr/lib/x86_64-linux-gnu/ -levent

#compiler and flags
#CXX	:= /usr/bin/gcc
#CPPFLAGS	:= -Wall

#default case
all: $(TARGET)

#specify build rule
%.o: %.cpp
	$(CXX) -c $< -o $@

#compile target rule
$(TARGET): $(TARGET).o $(OBJ)
	$(CXX) $^ -o $@

#remove binaries and .o
.PHONY: clean
clean:
	$(RM) *.o $(TARGET)
