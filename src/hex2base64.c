/**
 * Converts a hexidecimal string to a base64 string.
 * */
#include "hex2base64.h"

static uint8_t char_to_hex(char c);
static void print_base64(uint32_t hex, uint8_t padding);
static const char *base64chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void to_base64(char *hexstr)
{	
	char c;
	uint64_t len = 0;
	uint32_t hex = 0;
	int8_t window = 0;

	while ((c = hexstr[len++]) != '\0')
	{
		if (iscntrl(c))
			break;
		window++;
		hex |= char_to_hex(c) << (0x18 - (window << 2));
		if (window == 6)
		{
			print_base64(hex, 0);
			hex = 0;
			window = 0;
		}
	}

	if (hex != 0)
		print_base64(hex, window % 3);
}

static void print_base64(uint32_t hex, uint8_t padding)
{
	for (uint8_t i = padding; i < 4; ++i)
		printf("%c", base64chars[(hex >> (6 * (3 + padding - i))) & 0x3F]);

	if (padding != 0)
		for (uint8_t i = 0; i < padding; ++i)
			printf("=");
}

static uint8_t char_to_hex(char c)
{
	char lower_char = tolower(c);
	if (lower_char >= 48 && lower_char <= 57)
		return lower_char - 48;

	else if (lower_char >= 97 && lower_char <= 122)
		return (lower_char - 'a') + 10;

	printf("'%d' is not a valid hex value\n", c);
	exit(EXIT_FAILURE);
	return 0;
}
