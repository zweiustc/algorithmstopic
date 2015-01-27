#souce file
SRC = test.cpp
#object file
OBJ = $(SRC:.cpp=.o)
#Output extcution file 
PROGRAM = test
#Compiler
CC = g++
#include
INCLUDE = -I/usr/include/
#Linker Parameter
LINKPARAM = -lpthread
LIBS = -lm
#Option for development
#CFLAGS = -ansi -g -Wall
#Option for release
main: ${OBJ}
	g++ -o ${PROGRAM} ${OBJ} ${LIBS}
clean:
	rm -f ${PROGRAM}
	rm -f ${PROGRAM}.o
    

