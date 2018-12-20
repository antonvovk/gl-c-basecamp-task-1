.PHONY: app clean client server

all: app client server
	
app:
	mkdir -p Build
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/client.o client.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/server.o server.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/system_api.o system_api.c
	gcc -c -pipe -g -Wall -W -fPIC  -o Build/unix_network.o unix_network.c

client:
	gcc -o Build/client Build/client.o Build/system_api.o Build/unix_network.o

server:
	gcc -o Build/server Build/server.o Build/system_api.o Build/unix_network.o

clean:
	@echo "Cleaning up..."
	rm -f Build/client.o Build/server.o Build/system_api.o Build/unix_network.o


