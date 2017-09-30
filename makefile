INC_DIR = include
TARGET = hw2

all: $(TARGET)

$(TARGET): mainNumber.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) mainNumber.o  -lgtest
else
	g++ -o $(TARGET) mainNumber.o  -lgtest -lpthread
endif


# mainAtom.o: mainAtom.cpp utAtom.h atom.h
	# g++ -std=c++11 -c mainAtom.cpp

# mainVariable.o: mainVariable.cpp utVariable.h variable.h
# 		g++ -std=c++11 -c mainVariable.cpp

mainNumber.o: mainNumber.cpp utNumber.h number.h
		g++ -std=c++11 -c mainNumber.cpp
		
clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif