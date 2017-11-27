#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<time.h>
#include<arpa/inet.h>

typedef enum {false, true} bool;

//global total variable
int total;

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

	struct sockaddr_in r_addr,	//remote address
			   l_addr;	//local address

	struct hostent *serv;		//host server

	if(argc < 4)
	{
		printf("USAGE: ./cli (host name) (port #) (remote IP)\n");
		exit(1);
	}

	//set port number
	p_no = atoi(argv[2]);
	//set IP address
	//r_ip = atoi(argv[3]);

	//create socket
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket");
		exit(1);
	}

        //zero out server addresses
        bzero((char *) &r_addr, sizeof(r_addr));
	bzero((char *) &l_addr, sizeof(l_addr));

        //get host server
        serv = gethostbyname(argv[1]);
        if(serv == NULL)
        {
                perror("host");
                exit(1);
        }

	//set all local server info
	l_addr.sin_family = AF_INET;
	bcopy((char *)serv->h_addr, (char *)&l_addr.sin_addr.s_addr, serv->h_length);
	l_addr.sin_port = htons(p_no);

	//bind local
	if(bind(s_fd, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 1)
	{
		perror("bind");
		exit(1);
	}

        //set all remote server info
        r_addr.sin_family = AF_INET;
	r_addr.sin_addr.s_addr = inet_addr(argv[3]);
	r_addr.sin_port = htons(p_no);

	//connect remote
	if(connect(s_fd, (struct sockaddr *)&r_addr, sizeof(r_addr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	close(s_fd);

	return 0;
}
