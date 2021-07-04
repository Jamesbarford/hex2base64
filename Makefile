TARGET := hextobase64
CFLAGS := -Wall -Werror -Wextra -O2
CC     := cc

$(TARGET): ./hextobase64.c
	$(CC) $(CFLAGS) -o $@ $^

all: $(TARGET)

clean:
	rm $(TARGET)
