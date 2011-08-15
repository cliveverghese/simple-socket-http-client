#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "phraser.h"


struct phrased_url get_path_and_host(char * url1)
{
	struct phrased_url ret;
	char * url;
	url = strstr(url1,"://");
	if(url == NULL)
		url = url1;
	else
		url += 3;
	int i,j,len,p;
	for(len = 0; url[len] != '\0'; len++);
	p = 0;
	for(i=0,j=0; i < len; i++,j++)
	{
		if(p == 0)
		{
			if(url[i] != '/')
				ret.host[j] = url[i];
			else
			{
				ret.host[j] = '\0';
				p = 1;
				j = 0;
				ret.path[j] = url[i];
			}
		}
		else 
			ret.path[j] = url [i];
	}
	ret.path[j] = '\0';
	return ret;
}

struct status_code process_status_code(char * msg)
{
	struct status_code ret;
	int i,j;	
	char num[50];
	char * content_len_string;	

	for(i = 0; msg[i] != ' '; i++);
	i++;
	for(j = 0; msg[i] != ' '; i++,j++)
		num[j] = msg[i];
	num[j] = '\0';

	ret.status = atoi(num);
	
	content_len_string = strstr(msg,"Content-Length:");
	if(content_len_string != NULL)	
	{
		content_len_string += 16;
		for(i = 0,j = 0; content_len_string[i] != '\n'; i++,j++)
			num[j] = content_len_string[i];
		
		num[j] = '\0';
		ret.content_length = atoi(num);
		content_len_string = NULL;
		content_len_string = strstr(msg,"<");
		ret.header_length = content_len_string - msg;	
	}
	else
	{
		ret.content_length = 0;
		ret.header_length = 0;
	}
	content_len_string = strstr(msg,"Location:");
	if(content_len_string != NULL)
	{
		content_len_string += 9;
		for(i = 0; content_len_string[i] != '\n';i++)
		{
			ret.values[HEADER_LOCATION][i] = content_len_string[i];	
		}
		ret.values[HEADER_LOCATION][i] = '\0';
	}
	

	return ret;
}
		
