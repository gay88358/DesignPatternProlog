INC_DIR = include
TARGET = hw2

all: $(TARGET)

$(TARGET): mainTerm.o number.o variable.o atom.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o -lgtest
else
	g++ -o $(TARGET) mainTerm.o atom.o variable.o number.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=c++11 -c mainTerm.cpp

atom.o: atom.h atom.cpp variable.h number.h
	g++ -std=c++11 -c atom.cpp

variable.o: variable.h variable.cpp atom.h number.h
	g++ -std=c++11 -c variable.cpp

number.o: number.h number.cpp variable.h atom.h
	g++ -std=c++11 -c number.cpp	

clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif