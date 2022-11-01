CC=gcc
CFLAGS=-Wall
LDLIBS=-lcrypt
EASY_EXEC_NAME=identify_yourself_easy
HARD_EXEC_NAME=identify_yourself_hard
OPTS=-static

all: easy hard

easy: client.c
	$(CC) client.c $(CFLAGS) $(LDLIBS) $(OPTS) -o $(EASY_EXEC_NAME)

hard: client.c
	$(CC) client.c $(CFLAGS) $(LDLIBS) $(OPTS) -DHARD -o $(HARD_EXEC_NAME)

clean:
	rm -f $(EASY_EXEC_NAME) $(HARD_EXEC_NAME)
