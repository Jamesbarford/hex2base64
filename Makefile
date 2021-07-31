TARGET := hex2base64
CFLAGS := -Wall -Werror -Wextra -O2
CC     := cc

$(TARGET): ./hex2base64.c
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)

clean:
	rm $(TARGET)
