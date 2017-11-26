#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<time.h>

typedef enum {false, true} bool;

global int total;

int main(int argc, char ** argv)
{
	//working major 2 belongs here

	int s_fd;		//listen socket
	int p_no;		//port number
	int r_ip;		//remote IP
	int n;			//error check read & write
	int i, j;		//iterators

	char c_total[24];	//total as a character
	char buffer[256];	//buffer for read & write

	struct sockaddr_in s_addr;	//server address

	struct hostent *serv;		//host server

	if(argc < 4)
	{
		printf("USAGE: ./cli (host name) (port #) (remote IP)\n");
		exit(1);
	}

	//set port number
	p_no = atoi(argv[2]);
	//set IP address
	r_ip = atoi(argv[3]);

	//create socket
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket");
		exit(1);
	}

	//get host server
	serv = gethostbyname(argv[1]);
	if(serv == NULL)
	{
		perror("host");
		exit(1);
	}

	//zero out server address
	bzero((char *) &s_addr, sizeof(s_addr));

	//set all server info
	s_addr.sin_family = AF_INET;

	return 0;
}
