CC = gcc
CFLAGS = -framework ApplicationServices -framework CoreFoundation -framework CoreGraphics -framework Carbon

all:
	cp ../../src/exec.c .
	cp ../../src/exec.h .
	$(CC) $(CFLAGS) main.c exec.c -o main
