all: build run
C_FLAGS = -g -Wall -Wextra -Werror -Wpedantic -o
build:
	gcc $(C_FLAGS) server server.c errors.h
	gcc $(C_FLAGS) client client.c errors.h
run:
	./server
	./client 