#include <stdio.h>
#include <inttypes.h>
#include "command.h"
#include "coder.h"

int encode_file(const char *in_file_name, const char *out_file_name)
{
	FILE *in, *out;
	uint32_t code_point;
	CodeUnits code_units;

	in = fopen(in_file_name, "r");
	fscanf(in, "%" SCNx32, &code_point);
	fclose(in);

	encode(code_point, &code_units);

	for (size_t i = 0; i < code_units.legth; i++) {
		printf("%" "x", code_units.code[i]);
	}
	//printf("%zu", code_units.legth);

	out = fopen(out_file_name, "wb");

	write_code_unit(out, &code_units);

	fclose(out);

	return 0;

}

/*int decode_file(const char *in_file_name, const char *out_file_name)
{

}*/