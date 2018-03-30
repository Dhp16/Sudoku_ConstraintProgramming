CC=g++
CXXFLAGS= -std=c++1z
INC = 
LIBS = 
CURLLIB=
TARGET=bin
OBJ=src/main.cpp src/Grid.cpp

default: $(TARGET)
all: $(TARGET)

$(TARGET): $(OBJ)
	 $(CC) $(INC) $(OBJ) $(CXXFLAGS) -o $(TARGET) $(LIBS) $(CURLLIB) 

run:$(TARGET)
	./$(TARGET)