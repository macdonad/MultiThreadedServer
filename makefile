multTServer: multTServer.c
	gcc -lpthread -Wall -o multTServer multTServer.c

default: multTServer
