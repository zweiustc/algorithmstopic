SRC = mysqltest.c
OBJ = $(SRC:.c=.o)
PROGRAM = mysqltest
CC = gcc -g
INCLUDE = -I/usr/include \
	-L/usr/lib64/mysql 
#LIBS = -l/usr/lib64/mysql/mysql_config 
LIBS = -lm \
	   -lmysqlclient 
main: ${OBJ}
	  ${CC} -o ${PROGRAM} ${OBJ} ${INCLUDE} ${LIBS}
clean:
	rm -f ${PROGRAM}
	rm -f ${PROGRAM}.o

