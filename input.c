#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int HandleInput(char[256],int*);

int main()
{
	char buffer[256];
	int *totals=malloc(sizeof(int));
	
	totals=0;
	
	strcat(buffer, "500");
	
	if ( HandleInput(buffer,totals) )
		printf("PORT: %i\n",*totals);
	else
		printf("Total: %i\n",*totals);
	
	strcpy(buffer, "500");
	
	if ( HandleInput(buffer,totals) )
		printf("PORT: %i\n",*totals);
	else
		printf("Total: %i\n",*totals);
	
	strcat(buffer, "5");
	
	if ( HandleInput(buffer,totals) )
		printf("PORT: %i\n",*totals);
	else
		printf("Total: %i\n",*totals);
	
	strcat(buffer, "100");
	
	if ( HandleInput(buffer,totals) )
		printf("PORT: %i\n",*totals);
	else
		printf("Total: %i\n",*totals);
	
}

int HandleInput(char b[256],int* max)
{
	
	max += atoi(b);
	
	
	
	if (*max>=1024)
		return 1;
	else 
		return 0;
}