#include <stdio.h>
#include "command.h"
#include <string.h>

int main(int argc, char *argv[])
{
	if (strcmp("encode", argv[1]) == 0) {
		encode_file(argv[2], argv[3]);
	} else { 
		if (strcmp("decode", argv[1]) == 0) {
			decode_file(argv[2], argv[3]);
		} else {
			printf("Неверен первый аргумент\n");
		}
	}

	int z = encode_file(argv[2], argv[3]);
	printf("%d\n", z);
	int i;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

	return 0;
}