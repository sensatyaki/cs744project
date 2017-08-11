#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <pthread.h>
#include <signal.h>
#include <errno.h>
#include <time.h>


void *accept_clients(void *args);

int main(int argc, char const *argv[])
{
	pthread_t server_thread;

	if(pthread_create(&server_thread,NULL,accept_clients,NULL) < 0)
	{
		perror("Could not create server thread");
        exit(-1);
	}

	pthread_join(server_thread,NULL);

	pthread_exit(NULL);

	return 0;
}


void *accept_clients(void *args)
{
	int serverSocket;
	int clientSocket;
	pthread_t worker_thread;
	struct addinfo hints,*res,*p;
	struct sockaddr_storage *clientAddr;
	socklen_t sinSize = sizeof(struct sockaddr_storage);
    struct workerArgs *wa;
	int yes = 1;
}