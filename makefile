INC_DIR = include
SRC = src
TARGET = hw5

all: $(TARGET)

$(TARGET): mainTerm.o number.o variable.o atom.o struct.o term.o list.o scanner.o token.o parser.o builder.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o struct.o term.o list.o scanner.o token.o parser.o builder.o  -lgtest
else
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o struct.o term.o list.o scanner.o token.o parser.o builder.o   -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp
	g++ -std=gnu++0x -c mainTerm.cpp

builder.o: $(INC_DIR)/builder.h $(SRC)/builder.cpp 
	g++ -std=gnu++0x -c $(SRC)/builder.cpp

term.o: $(INC_DIR)/term.h $(SRC)/term.cpp 
	g++ -std=gnu++0x -c $(SRC)/term.cpp

struct.o: $(INC_DIR)/struct.h $(SRC)/struct.cpp $(INC_DIR)/atom.h 
	g++ -std=gnu++0x -c $(SRC)/struct.cpp

atom.o: $(INC_DIR)/atom.h $(SRC)/atom.cpp $(INC_DIR)/variable.h $(INC_DIR)/number.h
	g++ -std=gnu++0x -c $(SRC)/atom.cpp

variable.o: $(INC_DIR)/variable.h $(SRC)/variable.cpp $(INC_DIR)/atom.h $(INC_DIR)/number.h
	g++ -std=gnu++0x -c $(SRC)/variable.cpp

number.o: $(INC_DIR)/number.h $(SRC)/number.cpp $(INC_DIR)/variable.h $(INC_DIR)/atom.h
	g++ -std=gnu++0x -c $(SRC)/number.cpp	

list.o: $(INC_DIR)/list.h $(SRC)/list.cpp
	g++ -std=gnu++0x -c $(SRC)/list.cpp	

scanner.o: $(INC_DIR)/scanner.h $(SRC)/scanner.cpp $(INC_DIR)/token.h $(INC_DIR)/global.h
	g++ -std=gnu++0x -c $(SRC)/scanner.cpp	

token.o: $(INC_DIR)/token.h $(SRC)/token.cpp
	g++ -std=gnu++0x -c $(SRC)/token.cpp

global.o: $(INC_DIR)/global.h 
	g++ -std=gnu++0x -c $(INC_DIR)/global.h 

parser.o: $(INC_DIR)/parser.h $(SRC)/parser.cpp 
	g++ -std=gnu++0x -c $(SRC)/parser.cpp



clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif