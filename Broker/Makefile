#target name
TARGET	:= main

#other src files and obj definition
SRC	:= main.cpp
OBJ	:= $(patsubst %.cpp,%.o, $(SRC))

#include directories
MQTT_DIR	:= /home/root/projects/mqtt_server/mqtt_cpp/include
ALL		:= /usr/local/include

INCLUDE	:= -I$(MQTT_DIR) -I$(ALL)

#used libraries
LIB	:= -L/usr/local/lib/ -lpthread -lboost_system

#compiler and flags
#CXX	:= /usr/bin/gcc
CPPFLAGS	:= -std=c++14 

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
