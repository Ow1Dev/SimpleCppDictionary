CC = g++
CFLAGS = 

build:
	$(CC) $(CFLAGS) test.cpp -o bin/program -lpthread -pthread -DBOOST_ERROR_CODE_HEADER_ONLY

run:
	make build
	bin/program
