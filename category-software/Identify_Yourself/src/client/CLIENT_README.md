# CTF - Identify Yourself

## `client.c`

The C program `client.c` is the source code for the binary executable supplied to students.
It is a fairly simple program and does the following:

1. Verifies that an IP address was supplied from the command line.
2. Prompts the user for username/password until the correct credentials are supplied.
3. Once the credentials have been validated, establish a TCP connection with the remote host.
4. An interactve command shell is spawned on the remote host.

There are 4 C preprocessor macros that determine the behavior of the program:
* `USERNAME` - The username used in the credentials that will authenticate the user in order to establish a command shell with the remote host.
* `PASSWORD` - The password used in the credentials that will authenticate the user in order to establish a command shell with the remote host.
* `PORT` - The port number on the remote host that the TCP connection will be established on.
           This should match the port number specified in the `docker-compose.yml` and `Dockerfile` for the challenge Docker image.
* `MD5HASH` - In the hard version of the challenge `MD5HASH` is a stored MD5 hash of the password, and will be compared to the generated MD5 hash of the password that the user enters.
              The Ubuntu program [`md5pass`](https://manpages.ubuntu.com/manpages/bionic/man1/md5pass.1.html) was used to generate the MD5 hash that is the default value.
              You may use whatever method to generated the MD5 hash of your password, but the hash must be in the format `$id$salt$encrypted`, which is required by the glibc implementation of the `crypt()` function.
              See [here](https://www.man7.org/linux/man-pages/man3/crypt.3.html) and [here](https://www.gnu.org/software/libc/manual/2.36/html_node/Passphrase-Storage.html) for more on the correct MD5 hash format.

### `#include <crypt.h>`

The program uses the `crypt()` function from the GNU C library, specified in `crypt.h`.
The implementation of `crypt()` is not standardized, and varies between different Linux distributions.
`client.c` was originally developed and compiled on Ubuntu 22.04.
If you have issues compiling `client.c`, or if it does compile but the executable does not behave as you'd expect, it's likely that the version of `crypt()` your Linux distribution has is different than the one that `client.c` was developed with.
You may need to download and compile with the official [GNU C library (glibc)](https://www.gnu.org/software/libc/sources.html) in order to overcome these issues.

## Makefile and Compiling

If you modify `client.c`, you will need to recompile and distribute the binary to your students.
A C Makefile is supplied to assist with compilation.
You should modify the macros in `client.c` directly and recompile to change the default values, rather than trying to pass macro values through the make command line.

### Compile Easy

Compile the easy version of the challenge: `$ make easy`

### Compile Hard

Compile the hard version of the challenge: `$ make hard`

### Compile Both

By default both the easy and hard versions of the challenge are compiled: `$ make`

### Clean

You can delete the compiled binaries: `$ make clean`

### Debug

You can enable the `DEBUG` flag to have error messages printed when running the executable:

```
$ make CFLAGS=-DDEBUG
```

