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

int main(int argc, char ** argv)
{
	int total1,		//client 1 total
	    total2;		//client 2 total
	int s_fd;		//socket file descriptor
	int ns1_fd,		//client 1 fd
	    ns2_fd;		//client 2 fd
	int m_fd;		//max fd
	int c_len1,		//client length 1
	    c_len2;		//client length 2
	int p_no;		//port number (from command line)
	int n;			//read / write error check

	fd_set fds;		//for polling

	char buffer[256];

	struct sockaddr_in s_addr,	//server address
			   c_addr1,	//client 1 address
			   c_addr2;	//client 2 address

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

	//listen

	//accept

	return 0;
}
