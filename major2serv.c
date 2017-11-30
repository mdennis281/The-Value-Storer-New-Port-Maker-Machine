#include"functions.h"

int main(int argc, char ** argv)
{
	int total1,		//client 1 total
	    total2;		//client 2 total
	int s_fd,		//af _ inet
	    u_fd;		//af _ unix
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

	struct sockaddr_in s_addr,	//server address AF_INET
			   c_addr1,	//client 1 address
			   c_addr2;	//client 2 address
	struct sockaddr_un u_addr;	//server address AF_UNIX

	//unlink previos socket, if applicable
	unlink(SOCKETNAME);

	if(argc != 2)
	{
		printf("USAGE: ./serv (port #)\n");
		exit(1);
	}

	//create sockets
	//inet
	s_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(s_fd < 0)
	{
		perror("socket inet");
		exit(1);
	}

	//unix
	u_fd = socket(AF_UNIX, SOCK_STREAM, 0);
	if(u_fd < 0)
	{
		perror("socket unix");
		exit(1);
	}

	//zero the server address
	bzero((char *) &s_addr, sizeof(s_addr));
	bzero((char *) &u_addr, sizeof(u_addr));

	//fill in server information AF_INET
	p_no = atoi(argv[1]);
	s_addr.sin_family = AF_INET;
	s_addr.sin_port = htons(p_no);
	s_addr.sin_addr.s_addr = INADDR_ANY;

	//fill in server information AF_UNIX
	u_addr.sun_family = AF_UNIX;
	strcpy(u_addr.sun_path, SOCKETNAME);

	//bind
	//INET
	if(bind(s_fd, (struct sockaddr *) &s_addr, sizeof(s_addr)) < 0)
	{
		perror("bind inet");
		exit(1);
	}
	//UNIX
	if(bind(u_fd, (struct sockaddr *) &u_addr, sizeof(u_addr)) < 0)
	{
		perror("bind unix");
		exit(1);
	}

	//listen
	listen(s_fd, 1);
	listen(u_fd, 1);

	printf("%s", border);

	//accept 1 inet
	c_len1 = sizeof(c_addr1);
	ns1_fd = accept(s_fd, (struct sockaddr *) &c_addr1, &c_len1);
	if(ns1_fd < 0)
	{
		perror("accept client 1");
		exit(1);
	}

	//accept 2 unix
	c_len2 = sizeof(c_addr2);
	ns2_fd = accept(u_fd, (struct sockaddr *) &c_addr2, &c_len2);
	if(ns2_fd < 0)
	{
		perror("accept client 2");
		exit(1);
	}

	printf("%s", border);

	//get max file descriptor
//	m_fd = (ns1_fd > ns2_fd ? ns1_fd : ns2_fd) + 1;

	while(cont)
	{

	}

	return 0;
}
