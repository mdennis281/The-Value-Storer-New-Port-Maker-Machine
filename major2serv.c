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

	bool cont = true;	//continue loop?

	fd_set fds;		//for polling

	char c_total1[16],	//client 1 total as char
	     c_total2[16];	//client 2 total as char
	char buffer[256];	//buffer for info
	char * border = "*******************************\n";

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
	listen(s_fd, 5);

	printf("%s", border);

	//accept 1
	c_len1 = sizeof(c_addr1);
	ns1_fd = accept(s_fd, (struct sockaddr *) &c_addr1, &c_len1);
	if(ns1_fd < 0)
	{
		perror("accept client 1");
		exit(1);
	}

	//accept 2
	c_len2 = sizeof(c_addr2);
	ns2_fd = accept(s_fd, (struct sockaddr *) &c_addr2, &c_len2);
	if(ns2_fd < 0)
	{
		perror("accept client 2");
		exit(1);
	}

	printf("%s", border);

	//get max file descriptor
	m_fd = (ns1_fd > ns2_fd ? ns1_fd : ns2_fd) + 1;

	while(cont)
	{

	}

	return 0;
}
