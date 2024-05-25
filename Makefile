.RECIPEPREFIX = >
.PHONY: all

CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror
LDFLAGS = -lpthread

TARGET = libprogbar.a
TARGET_THR = libprogbar_thr.a

EXAMPLE_SRC = example.c
EXAMPLE_OBJ = $(EXAMPLE_SRC:.c=.o)
EXAMPLE = example

all: $(TARGET) $(TARGET_THR)

$(TARGET): progbar.o
> $(AR) src $@ $^

$(TARGET_THR): progbar.o progbar_thr.o
> $(AR) src $@ $^

$(EXAMPLE): $(EXAMPLE_OBJ) $(TARGET) $(TARGET_THR)
> $(CC) -L. -Wl,-rpath=. $(CFLAGS) $^ -lprogbar -lprogbar_thr $(LDFLAGS) -o $@

clean:
> $(RM) $(wildcard *.o)

clean_all: clean
> $(RM) $(TARGET) $(TARGET_THR) $(EXAMPLE)
