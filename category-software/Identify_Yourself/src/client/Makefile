EASY_EXEC_NAME=identify_yourself_easy
HARD_EXEC_NAME=identify_yourself_hard
CFLAGS=-static -lcrypt

all: easy hard

easy: client.c
	gcc client.c $(CFLAGS) -o $(EASY_EXEC_NAME)

hard: client.c
	gcc client.c $(CFLAGS) -DHARD -o $(HARD_EXEC_NAME)

clean:
	rm -f $(EASY_EXEC_NAME) $(HARD_EXEC_NAME)
