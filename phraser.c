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
