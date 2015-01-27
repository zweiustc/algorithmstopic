#souce file
SRC = HeapSort.cpp
#object file
OBJ = $(SRC:.cpp=.o)
#Output extcution file 
PROGRAM = HeapSort
#Compiler
CC = g++ 
#include
INCLUDE = -I/usr/include/
#Linker Parameter
LINKPARAM = -lpthread
LIBS = -lm 
#Option for development
CFLAGS = -ansi -g -Wall
#Option for release
main: ${OBJ}
	g++ ${SRC} -o ${PROGRAM}  ${LIBS} ${CFLAGS}
clean:
	rm -f ${PROGRAM}
	rm -f ${PROGRAM}.o
