C=gcc
CFLAGS=-g -std=c99 -fmax-errors=1 -Werror
MODULES = gtopoRead.o 
MAINS = gtopoEcho.o gtopoComp.o gtopoReduce.o
TARGETS = gtopoEcho gtopoComp gtopoReduce

all:		${MODULES} ${MAINS} ${TARGETS}

clean:
	rm ${TARGETS} ${MAINS} ${MODULES} *.o

gtopoEcho:		gtopoEcho.o ${MODULES}
	${CC} 		${CCFLAGS} -o gtopoEcho 	gtopoEcho.o		${MODULES}

gtopoComp:		gtopoComp.o ${MODULES}
	${CC} 		${CCFLAGS} -o gtopoComp 	gtopoComp.o		${MODULES}

gtopoReduce:		gtopoReduce.o ${MODULES}
	${CC} 		${CCFLAGS} -o gtopoReduce 	gtopoReduce.o		${MODULES}

gtopoEcho.o: gtopoEcho.c gtopoRead.h 
			gcc -c -g -std=c99 -fmax-errors=1 -Werror -o gtopoEcho.o gtopoEcho.c	

gtopoComp.o: gtopoComp.c gtopoRead.h 
			gcc -c -g -std=c99 -fmax-errors=1 -Werror -o gtopoComp.o gtopoComp.c

gtopoReduce.o: gtopoReduce.c gtopoRead.h 
			gcc -c -g -std=c99 -fmax-errors=1 -Werror -o gtopoReduce.o gtopoReduce.c

gtopoRead.o: gtopoRead.c gtopoRead.h
			gcc -c -g -std=c99 -fmax-errors=1 -Werror -o gtopoRead.o gtopoRead.c
