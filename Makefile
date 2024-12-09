PROG = seven_segment

CC = clang
CFLAGS := $(shell pkg-config --cflags gtk+-3.0)
LIBS := $(shell pkg-config --libs gtk+-3.0)

${PROG}: seven_segment.c
	${CC} ${CFLAGS} -o ${PROG} ${PROG}.c ${LIBS} 

clean:
	rm -f seven_segment

# target: prequisites
# 	actions