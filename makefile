## #################################################################
## SUPER COMPLICATED BUILD SYSTEM BELOW: BEWARE
## #################################################################

buildDir = bin
srcDir = src
exec = $(buildDir)/multTServer	
mainSource = $(srcDir)/multTServer.c

$(exec): bin $(mainSource) sources
	gcc -lpthread -Wall -o $(exec) $(mainSource)

sources: $(srcDir)/*.c $(srcDir)/*.h

bin: 
	mkdir bin

default: $(exec)

clean:
	rm -rf $(buildDir)
