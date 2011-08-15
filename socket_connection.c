#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "socket_connection.h"
#include "phraser.h"

void get_content_webpage(char url[])
{	
	int sock,n,status;
	struct phrased_url location;
	struct status_code response_status;
	
	struct hostent *destination;
	struct sockaddr_in server;

	char msg[1024];
	printf("%s",url);
	location = get_path_and_host(url);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		printf("error opening socket");
	destination = gethostbyname(location.host);
    	if (destination == NULL)
	{
        	printf("ERROR, no such host\n");
      		return;
    	}
	bzero(&server,sizeof(server));
	server.sin_family = AF_INET;
	
	bcopy((char *)destination->h_addr,(char *)&server.sin_addr.s_addr,destination->h_length);
	
	server.sin_port = htons(80);
	bzero(msg,1024);
	strcat(msg,"GET ");
	strcat(msg,location.path);
	strcat(msg," HTTP/1.1\nHost: ");
	strcat(msg,location.host);
	strcat(msg,"\nUser-Agent: Mozilla/5.0 (X11; Linux i686; rv:2.0.1) Gecko/20100101 Firefox/4.0.1\n\n");


	if(connect(sock,(struct sockaddr *) &server, sizeof(server)) < 0)
		printf("error connecting");
	n = write(sock,msg,strlen(msg));
	bzero(msg,1024);
	n = recv(sock,msg,1024,0);

	response_status = process_status_code(msg);
	printf("\n%d\n%s",response_status.status,msg+response_status.header_length);
	if(response_status.status == 302 || response_status.status == 301)
	{
		if(strstr(response_status.values[HEADER_LOCATION],"http://") == NULL)
		{
			bzero(msg,1024);
			strcpy(msg,url);
			strcat(msg,response_status.values[HEADER_LOCATION]);
			strcpy(response_status.values[HEADER_LOCATION],msg);
		}
			
		get_content_webpage(response_status.values[HEADER_LOCATION]);
		return;	
	}
	n = n - response_status.header_length;

	while(n < response_status.content_length)
	{
		bzero(msg,1024);
		n += recv(sock,msg,1024,0);
		printf("%s",msg);
	}		
	close(sock);
	
}
