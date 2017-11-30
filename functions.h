//*****************************//
// GENERAL FUNCTIONS AND MISC  //
//*****************************//

#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<sys/time.h>
#include<unistd.h>

#define SOCKETNAME "local"

typedef enum {false, true} bool;

char * return_IP(struct hostent * s)
{
printf("BEGIN return_IP(serv)\n");
	char * ip;

	struct in_addr i;

	memcpy(&i, s->h_addr_list[0], sizeof(struct in_addr));
	strcpy(ip, inet_ntoa(i));

	return ip;
printf("END return_IP(serv)\n");
}
