#include "coder.h"
#include "command.h"
#include <inttypes.h>
#include <stdio.h>

int encode(uint32_t point, CodeUnits *units)
{
	int code_128 = 128, code_63 = 63;

	if (point <= 0x7F) {
		units->length = 1;
		units->code[0] = point;
		return 0;
	} else if (point <= 0x7FF) {
		units->length = 2;
	} else if (point <= 0xFFFF) {
		units->length = 3;
	} else if (point <= 0x1FFFFF){
		units->length = 4;
	} else {
		return -1;
	}

	units->code[0] = code_128;
	for (size_t i = 1; i < units->length; i++) {
		units->code[0] = units->code[0] | (code_128 >> i);
	}
	units->code[0] = units->code[0] | (point >> 6 * (units->length - 1));

	for (size_t i = 1; i < units->length; i++) {
		units->code[i] = code_128 | ((point >> (6 * (units->length - i - 1))) & code_63);
	}

	print_BIT(units);

	return 0;
}

uint32_t decode(const CodeUnits *units)
{
	uint32_t point = 0;

	if (units->length == 1) {
		point = units->code[0];
	} else if (units->length == 2) {
		point = units->code[0] & 0x3f;
	} else if (units->length == 3) {
		point = units->code[0] & 0x1f;
	} else if (units->length == 4) {
		point = units->code[0] & 0x0f;
	} else {
		return -1;
	}

	for (size_t i = 1; i < units->length; i++) {
		point = (point << 6) | (units->code[i] & 0x7f);
	}

	return point;
}

int read_next_code_unit(FILE *in, CodeUnits *units)
{
	uint8_t buffer = 0;
	fread(&buffer, 1, 1, in);
	while(!feof(in)) {
		uint8_t enum_bite = 0;
		while((buffer & (1 << (7 - enum_bite))) != 0) {
			enum_bite++;
		}
		if (enum_bite == 1) {
			fread(&buffer, 1, 1, in);
			continue;
		}
		if (enum_bite == 0) {
			enum_bite = 1;
		}
		if (enum_bite <= MaxCodeLength) {
			units->length = 0;
			for (int i = 1; i <= enum_bite; i++) {
				units->code[i - 1] = buffer;
				units->length++;
				if (i == enum_bite) {
					return 0;
				}
				
				fread(&buffer, 1, 1, in);
				if ((buffer & 0xC0) != 0x80) {
					break;
				}
			}
		}
	}

	return -1;
}

int write_code_unit(FILE *out, const CodeUnits *units)
{
	fwrite(units->code, units->length, sizeof(units->code), out);

	return 0;
}

void print_BIT(const CodeUnits *units)
{
	int code_128 = 128;
	int code_127 = 0;

	for (size_t i = 0; i < units->length; ++i) {
		for (size_t j = 0; j < 8; ++j) {

			code_127 = code_128 & units->code[i];

			if (code_127 == 0) {
				printf("%d", 0);
			} else {
				printf("%d", 1);
			}
			code_128 = code_128 >> 1;
		}
		code_128 = 128;
		printf(" ");
	}

	printf("\n");
}