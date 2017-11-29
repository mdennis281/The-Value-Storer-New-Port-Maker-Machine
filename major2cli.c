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

int main(int argc, char ** argv)
{
	int s_fd,		//server socket
	    r_fd;		//remote socket
	int p_no;		//port number
	int n;			//error check read & write
	int i, j;		//iterators
	int total;		//clients total

	char c_total[16];	//total as a character
	char buffer[256];	//buffer for read & write

	struct sockaddr_in r_addr,	//remote address
			   s_addr;	//server address

	struct hostent *serv;		//host server

	if(argc != 4)
	{
		printf("USAGE: ./cli (host name) (port #) (remote IP)\n");
		exit(1);
	}

	//set port number
	p_no = atoi(argv[2]);

	//create local socket
//	if(
//	{
		s_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(s_fd < 0)
		{
			perror("socket local");
			exit(1);
		}
//	}

	//create remote socket
	r_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket remote");
		exit(1);
	}

        //zero out server addresses
        bzero((char *) &r_addr, sizeof(r_addr));
	bzero((char *) &s_addr, sizeof(s_addr));

        //get host server
        serv = gethostbyname(argv[1]);
        if(serv == NULL)
        {
                perror("host name resolution");
                exit(1);
        }

	//set all local server info
	s_addr.sin_family = AF_INET;
	bcopy((char *)serv->h_addr, (char *)&s_addr.sin_addr.s_addr, serv->h_length);
	s_addr.sin_port = htons(p_no);

	//bind local
	/*if(bind(s_fd, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 1)
	{
		perror("bind local");
		exit(1);
	}*/

	//connect local
	if(connect(s_fd, (struct sockaddr *)&s_addr, sizeof(s_addr)) < 0)
	{
		perror("connect server");
		exit(1);
	}

        //set all remote server info
        r_addr.sin_family = AF_INET;
	r_addr.sin_addr.s_addr = inet_addr(argv[3]);
	r_addr.sin_port = htons(p_no);

	//bind remote
	/*if(bind(r_fd, (struct sockaddr *)&r_addr, sizeof(r_addr)) < 1)
	{
		perror("bind remote");
		exit(1);
	}*/

	//connect remote
	if(connect(r_fd, (struct sockaddr *)&r_addr, sizeof(r_addr)) < 0)
	{
		perror("connect remote");
		exit(1);
	}

	//close sockets
	close(s_fd);
	close(r_fd);

	return 0;
}
