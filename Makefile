all:
	gcc -g core.c work.c utils.c main.c -o app -lpthread
