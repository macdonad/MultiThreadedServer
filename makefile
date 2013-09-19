## #################################################################
## SUPER COMPLICATED BUILD SYSTEM BELOW: BEWARE
## #################################################################

multTServer: multTServer.c multTServer.h
	gcc -lpthread -Wall -o multTServer multTServer.c

default: multTServer
