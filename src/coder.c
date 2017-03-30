#include <stdio.h>
#include <inttypes.h>
#include "command.h"

int encode(uint32_t code_point, CodeUnits *code_units)
{
	//uint32_t test = code_point;
	int code_128 = 128, code_63 = 63;

	//for (code_units->legth = 0; test != 0; code_units->legth++) {
	//	test = test >> 6;
	//}

	if (code_point <= 0x7F) {
		code_units->legth = 1;
		code_units->code[0] = code_point;
		return 0;
	} else if (code_point <= 0x7FF) {
		code_units->legth = 2;
	} else if (code_point <= 0xFFFF) {
		code_units->legth = 3;
	} else if (code_point <= 0x1FFFFF){
		code_units->legth = 4;
	}

	//if (code_units->legth == 1) {
	//	code_units->code[0] = code_point;
	//	return 0;
	//}

	code_units->code[0] = code_128;
	for (size_t i = 1; i < code_units->legth; i++) {
		code_units->code[0] = code_units->code[0] | (code_128 >> i);
	}

	code_units->code[0] = code_units->code[0] | (code_point >> 6 * (code_units->legth - 1));

	for (size_t i = 1; i < code_units->legth; i++) {
		code_units->code[i] = code_128 | ((code_point >> (6 * (code_units->legth - i - 1))) & code_63);
	}

	return 0;
}

/*uint32_t decode(const CodeUnit *code_unit)
{

}

int read_next_code_unit(FILE *in, CodeUnits *code_units)
{

}*/

int write_code_unit(FILE *out, const CodeUnit *code_unit)
{
	fwrite(code_units->code, code_units->legth, sizeof(code_units->code), out);

	return 0;
}