CC = g++
CFLAGS = -lpthread -pthread -DBOOST_ERROR_CODE_HEADER_ONLY

build:
	mkdir bin
	$(CC) main.cpp -o bin/program $(CFLAGS)

run:
	make build
	bin/program
