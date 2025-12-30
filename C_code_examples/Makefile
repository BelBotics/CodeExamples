CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -std=c11
TARGET  = reverse_test

SRCS    = main.c reverse_string.c is_power_of_two.c c_tasks.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

