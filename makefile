INC_DIR = include
SRC = src
TARGET = hw4

all: $(TARGET)

$(TARGET): mainTerm.o number.o variable.o atom.o struct.o term.o list.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o struct.o term.o list.o -lgtest
else
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o struct.o term.o list.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utStruct.h utVariable.h 
	g++ -std=gnu++0x -c mainTerm.cpp

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



clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif