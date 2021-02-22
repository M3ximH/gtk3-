all:
	gcc -g3 -Wall dictionary.c -rdynamic -o dict `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
clean:
