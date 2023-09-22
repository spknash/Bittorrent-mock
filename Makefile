# Usage:
# make        # compile all binary
# make clean  # remove ALL binaries and objects

.PHONY = all clean

CC = clang++ -std=c++17			# compiler to use

LINKERFLAG = -lm

SRCS := mocktorrent.cpp
BINS := app

all: ${BINS}

app: mocktorrent.o bencode.o
	@echo "Checking.."
	${CC} ${LINKERFLAG} bin/mocktorrent.o bin/bencode.o -o app

mocktorrent.o: src/mocktorrent.cpp
	@echo "Creating object.."
	${CC} -c $< -o bin/mocktorrent.o

bencode.o: lib/bencoding.cpp
	@echo "Creating object.."
	${CC} -c $< -o bin/bencode.o

clean:
	@echo "Cleaning up..."
	rm -rvf bin/*.o ${BINS}