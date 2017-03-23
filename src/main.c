#include <stdio.h>
//#include "coder.h"
#include "command.h"

int main(int argc, char *argv[])
{
	int z = encode_file(argv[2], argv[3]);
	printf("%d\n", z);
	/*int i;
    for (i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }*/

	return 0;
}