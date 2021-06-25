all:
	gcc -g core.c main.c work.c utils.c -o app -lpthread
