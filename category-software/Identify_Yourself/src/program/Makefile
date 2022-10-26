EASY_EXEC_NAME=identify_yourself_easy
HARD_EXEC_NAME=identify_yourself_hard
CFLAGS=-lcrypt

all: easy hard

easy: shell.c
	gcc shell.c $(CFLAGS) -o $(EASY_EXEC_NAME)

hard: shell.c
	gcc shell.c $(CFLAGS) -DHARD -o $(HARD_EXEC_NAME)

clean:
	rm -f $(EASY_EXEC_NAME) $(HARD_EXEC_NAME)
