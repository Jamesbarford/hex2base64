#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

static const char *base64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static void printBase64(int hex, int padding) {
	for (int i = padding; i < 4; ++i)
		printf("%c", base64chars[(hex >> (6 * (3 + padding - i))) & 63]);

	if (padding != 0)
		for (int i = 0; i < padding; ++i)
			printf("=");
}

static int charToHex(char c) {
	char lower_char = tolower(c);
	if (lower_char >= 48 && lower_char <= 57)
		return lower_char - 48;

	else if (lower_char >= 97 && lower_char <= 122)
		return (lower_char - 'a') + 10;

	printf("'%d' is not a valid hex value\n", c);
	exit(EXIT_FAILURE);
	return 0;
}

static void hexToBase64(char *hexstr) {
	char *ptr = hexstr;
	int hex = 0;
	int window = 0;

	while (*ptr != '\0') {
		if (iscntrl(*ptr))
			break;
		window++;
		hex |= charToHex(*ptr) << (24 - (window << 2));
		if (window == 6) {
			printBase64(hex, 0);
			hex = 0;
			window = 0;
		}
		ptr++;
	}

	if (hex != 0)
		printBase64(hex, window % 3);
}

static char *readAll(int fd) {
  char *buf;
	char tmp[BUFSIZ] = {'\0'};
	int iter = 1;
	int bytes = 0;

	if ((buf = (char *)calloc(sizeof(char *), BUFSIZ)) == NULL)
		return NULL;

	while (1) {
		iter++;
		bytes = read(fd, tmp, BUFSIZ - 1);
		if (bytes <= 0) break;
		else {
			tmp[bytes] = '\0';
			strcat(buf, tmp);
			char *new_buf = realloc(buf, sizeof(char *) * (iter * BUFSIZ));
			if (new_buf == NULL)
				return NULL;
			buf = new_buf;
		}
	}

	buf[iter * BUFSIZ] = '\0';

	return buf;
}

int main(int argc, char **argv) {
	if (argc == 2) {
		hexToBase64(argv[1]);
		exit(EXIT_SUCCESS);
		return 0;
	}

	char *bytes;
	if ((bytes = readAll(STDIN_FILENO)) == NULL) {
		fprintf(stderr, "Failed to convert hex to base64");
		exit(EXIT_FAILURE);
	}

	hexToBase64(bytes);
	free(bytes);

	return 0;
}
