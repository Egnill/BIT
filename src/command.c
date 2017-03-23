#include <stdio.h>
#include <inttypes.h>
#include "command.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *o = fopen(in_file_name, "r");
 	FILE *p = fopen(out_file_name, "w");
	
	while (o != EOF) {
		fprintf(p, "%c ", o);
	}

	fclose(o);

	return 0;

}

/*int decode_file(const char *in_file_name, const char *out_file_name)
{

}*/