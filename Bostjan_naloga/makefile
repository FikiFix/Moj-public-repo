C_FLAGS = -g -Wall -Werror -Wextra -Wpedantic

all: build run

build:
	gcc $(C_FLAGS) -o rac racunalnik.c napake.h
	gcc $(C_FLAGS) -o krmilnik krmilnik.c napake.h

run:
	./rac