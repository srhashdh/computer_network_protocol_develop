
CC=gcc
CFLAGS= -std=c99 -g
LIBS= -lpthread
TARGET=simpletorrent
SOURCES=src/util.c \
        src/bencode.c \
				src/sha1.c \
				src/shutdown.c \
				src/make_tracker_request.c \
				src/parse_announce_url.c \
        src/parsetorretnfile.c \
				src/process_tracker_response.c \
				src/btdata.c \
				src/simpletorrent.c 

OBJS=src/util.o \
     src/bencode.o \
		 src/sha1.o\
		 src/shutdown.o \
		 src/make_tracker_request.o \
		 src/parse_announce_url.o \
     src/parsetorrentfile.o \
		 src/process_tracker_response.o \
		 src/btdata.o \
		 src/simpletorrent.o

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} ${CFLAGS} -o bin/${TARGET} ${LIBS} ${OBJS}

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf src/*.o
	rm -rf bin/${TARGET}
	rm -rf src/*.core
	rm -rf *.o
	rm -rf ${TARGET}
	rm -rf *.core

.PHONY: all clean
