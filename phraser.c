#include<stdio.h>
#include<stdlib.h>
#include "phraser.h"


struct phrased_url get_path_and_host(char * url)
{
	struct phrased_url ret;
	
	printf("%s",url);
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

int process_status_code(char * msg)
{
	int ret;
	int i,j;	
	char num[4];
	for(i = 0; msg[i] != ' '; i++);
	i++;
	for(j = 0; msg[i] != ' '; i++,j++)
		num[j] = msg[i];
	num[j] = '\0';
	printf("\n%s",num);
	ret = atoi(num);
	return ret;
}
		
