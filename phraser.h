#ifndef PHRASER_H_INCLUDED
#define PHRASER_H_INCLUDED
enum header_response{
	HEADER_STATUS_CODE,
	HEADER_LOCATION,
	HEADER_CONTENT_TYPE
};
struct status_code{
	int status,header_length,content_length;
	char values[10][200];
};

struct phrased_url{
	char host[100],path[200];
};


struct phrased_url get_path_and_host(char *);

struct status_code process_status_code(char *);

#endif
