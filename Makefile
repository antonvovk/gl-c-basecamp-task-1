.PHONY: app clean client server

all: app

PLATFORM := $(shell uname)

ifeq ($(PLATFORM),Linux)
	
app:
	mkdir Build
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/client.o client.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/server.o server.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/system_api.o system_api.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/unix_network.o unix_network.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/windows_network.o windows_network.c

client:
	gcc -o Build/client Build/client.o Build/system_api.o Build/unix_network.o Build/windows_network.o 

server:
	gcc -o Build/server Build/server.o Build/system_api.o Build/unix_network.o Build/windows_network.o 

clean:
	@echo "Cleaning up..."
	rm -f Build/client.o Build/server.o Build/system_api.o Build/unix_network.o Build/windows_network.o

else
		
app:
	mkdir Build
	cl.exe /c -o Build/client.o client.c
	cl.exe /c -o Build/server.o server.c
	cl.exe /c -o Build/system_api.o system_api.c
	cl.exe /c -o Build/unix_network.o unix_network.c
	cl.exe /c -o Build/windows_network.o windows_network.c
	cl.exe -o Build/client Build/client.o Build/server.o Build/system_api.o Build/unix_network.o Build/windows_network.o 

clean:
	del Build/client.o Build/server.o Build/system_api.o Build/unix_network.o Build/windows_network.o
endif


