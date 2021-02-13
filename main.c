#include <fcntl.h>
#include <unistd.h>

#include "./src/hex2base64.h"

#define BYTES 0x400

int main(int argc, char **argv)
{
	int bytes_read;
	char buff[BYTES];

	if (argc == 2)
	{
		to_base64(argv[1]);
		exit(EXIT_SUCCESS);
		return 0;
	}

	while ((bytes_read = read(STDIN_FILENO, buff, BYTES)) > 0)
		to_base64(buff);

	printf("\n");
	return 0;
}
