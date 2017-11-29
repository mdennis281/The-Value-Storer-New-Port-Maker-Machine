#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<string.h>
#include<sys/time.h>
#include<netinet/in.h>

typedef enum {false, true} bool;

void connection_handler(void *);

int main(int argc, char ** argv)
{
	int total1,		//client 1 total
	    total2;		//client 2 total
	int s_fd;		//socket file descriptor
    	int c_fd;		//generic client file descriptor, don't need specific ones since we thread them away
    	int len;		//length of client
    	int *new_sock;		//passed to thread 
	int m_fd;		//max fd
	int p_no;		//port number (from command line)
	int n;			//read / write error check

	fd_set fds;		//for polling

	char buffer[256];

	struct sockaddr_in s_addr,	//server address
                        c_addr;		//client address

	if(argc != 2)
	{
		printf("USAGE: ./serv (port #)\n");
		exit(1);
	}

	//create socket
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	//zero the server address
	bzero((char *) &s_addr, sizeof(s_addr));

	//fill in server information
	p_no = atoi(argv[1]);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(p_no);
	s_addr.sin_addr.s_addr = INADDR_ANY;

	//bind
	if(bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0)
	{
		perror("bind");
		exit(1);
	}

	//listen for 2 clients
    	listen(s_fd, 2);

	//accept
    	puts("Waiting for incoming connections..");
    	len = sizeof(struct sockaddr_in);

	// Continuously listen and accept new clients and thread them off once we get one
    	while((c_fd = accept(s_fd, (struct sockaddr *)&c_addr, (socklen_t*)&len)))
    	{
       		puts("[Received a connection from a client.]");

        	pthread_t handler;
        	new_sock = malloc(sizeof new_sock);
        	*new_sock = c_fd;

		// Thread the client away 
        	if(pthread_create(&handler, NULL, connection_handler, (void*)new_sock) < 0)
        	{
            		perror("pthread");
            		exit(1);
       		}

        	puts("[Handler assigned.]");
    	}

	return 0;
}

void connection_handler(void *s_desc)
{
    puts("\n[Inside pthread handler for client.]\n");
    pthread_exit(NULL);

    return;
}
