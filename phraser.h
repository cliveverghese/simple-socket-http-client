#ifdef PHRASER_H_INCLUDED
#define PHRASER_H_INCLUDED

struct phrased_url{
	char host[100];
	char path[200];
};


struct phrased_url get_path_and_host(char *);

#endif
