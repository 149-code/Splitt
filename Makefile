all:
	gcc -o main src/listener.c src/exec.c src/keybinds.c src/main.c src/utils.c -pthread -framework CoreGraphics -framework CoreFoundation -framework Carbon
