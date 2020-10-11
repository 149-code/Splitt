CC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread -framework CoreGraphics -framework CoreFoundation -framework Carbon

main: build/exec.o build/keybinds.o build/listener.o build/logic.o build/utils.o build/main.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf main
	rm -rf build/*
