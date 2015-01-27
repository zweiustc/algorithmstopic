SRC = quicksort.c
OBJ = quicksort.o
PROGRAM = quicksort
CC = gcc -g
INCLUDE = -I/usr/include
LIBS = -lm
main: ${OBJ}
	${CC} -o ${PROGRAM} ${OBJ} ${LIBS}
clean:
	rm -f ${PROGRAM}
	rm -f ${PROGRAM}.o

