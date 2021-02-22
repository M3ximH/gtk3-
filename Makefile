all:
	gcc -g3 -Wall dictionary.c -o dict `pkg-config --cflags --libs gtk+-3.0` -export-dynamic -rdynamic
clean:
