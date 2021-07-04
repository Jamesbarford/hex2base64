#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

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

int main(int argc, char **argv) {
	int bytes_read;
	char buff[BUFSIZ];

	if (argc == 2) {
		hexToBase64(argv[1]);
		exit(EXIT_SUCCESS);
		return 0;
	}

	while ((bytes_read = read(STDIN_FILENO, buff, BUFSIZ)) > 0)
		hexToBase64(buff);

	return 1;
}
