#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<netinet/in.h>
#include<unistd.h>
#include<netdb.h>
#include<time.h>
#include<arpa/inet.h>

typedef enum {false, true} bool;

//define unix socket
#define SOCKETNAME "local"

int main(int argc, char ** argv)
{
	int s_fd,		//server socket
	    r_fd;		//remote socket
	int p_no;		//port number
	int n;			//error check read & write
	int i, j;		//iterators
	int total;		//clients total

	bool inetf,		//dealing with inet
	     unixf;		//dealing with unix

	char c_total[16];	//total as a character
	char buffer[256];	//buffer for read & write

	struct sockaddr_in r_addr,	//remote address
			   i_addr;	//inet server address
	struct sockaddr_un u_addr;	//unix server address


	struct hostent *serv;		//host server

	if(argc != 4)
	{
		printf("USAGE: ./cli (host name) (port #) (remote IP)\n");
		exit(1);
	}

	//set values
	unixf = false;
	inetf = false;

	//set port number
	p_no = atoi(argv[2]);

	//create local socket
/*	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket local");
		exit(1);
	}
*/
	//create remote socket
	r_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(r_fd < 0)
	{
		perror("socket remote");
		exit(1);
	}

        //zero out server addresses
        bzero((char *) &r_addr, sizeof(r_addr));
	bzero((char *) &i_addr, sizeof(i_addr));
	bzero((char *) &u_addr, sizeof(u_addr));

        //get host server
        serv = gethostbyname(argv[1]);
        if(serv == NULL)
        {
                perror("host name resolution");
                exit(1);
        }

	printf("Server IP Address: %s\n", (char *)serv->h_addr);

	//AF_UNIX client
	if(strcmp((char *)serv->h_addr, argv[3]) != 0)
	{
		printf("Detected as AF_UNIX client\n");

		unixf = true;

		s_fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if(s_fd < 0)
		{
			perror("socket unix");
			exit(1);
		}

		//set server info
		u_addr.sun_family = AF_UNIX;
		strcpy(u_addr.sun_path, SOCKETNAME);
	}
	//AF_INET client
	else if(strcmp((char *)serv->h_addr, argv[3]) == 0)
	{
		printf("Detected as AF_INET client\n");

		inetf = true;

		s_fd = socket(AF_INET, SOCK_STREAM, 0);
		if(s_fd < 0)
		{
			perror("socket inet");
			exit(1);
		}

		//set server info now
		i_addr.sin_family = AF_INET;
		bcopy(serv->h_addr, (char *)&i_addr.sin_addr.s_addr, serv->h_length);
		i_addr.sin_port = htons(p_no);
	}
	//IP ADDRESS FAIL
	else
	{
		perror("invalid ip");
		exit(1);
	}

	//set all local server info
/*	s_addr.sin_family = AF_INET;
	bcopy((char *)serv->h_addr, (char *)&s_addr.sin_addr.s_addr, serv->h_length);
	s_addr.sin_port = htons(p_no);
*/
	//bind local
	/*if(bind(s_fd, (struct sockaddr *)&l_addr, sizeof(l_addr)) < 1)
	{
		perror("bind local");
		exit(1);
	}*/

	//connect local
	if(unixf == true)
	{
		if(connect(s_fd, (struct sockaddr *)&u_addr, sizeof(u_addr)) < 0)
		{
			perror("connect server unix");
			exit(1);
		}
	}
	else if(inetf == true)
	{
		if(connect(s_fd, (struct sockaddr *)&i_addr, sizeof(i_addr)) < 0)
		{
			perror("connect server inet");
			exit(1);
		}
	}

        //set all remote server info
        r_addr.sin_family = AF_INET;
	r_addr.sin_addr.s_addr = inet_addr(argv[3]);
	if(inetf == true)
		r_addr.sin_port = htons(15106);
	else if(unixf == true)
		r_addr.sin_port = htons(15129);

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
