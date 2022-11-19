# CTF - Open the Floodgate

## For the Instructor(s)

### Docker

The Docker application used for this challenge consists of two containers.
One of the containers is running [nginx](https://hub.docker.com/_/nginx/), functioning as a reverse proxy.
The other container is based on [Alpine Linux with Python 3](https://hub.docker.com/_/python), and is running both [gunicorn](https://gunicorn.org/) and [flask](https://flask.palletsprojects.com/en/2.2.x/),
in which gunicorn feeds HTTP requests form the nginx reverse proxy to the flask web app.

#### Configuring the Docker Image

##### Modifying the Flag

The flag is set as an environment variable in the container running the flask web app.
To modify the flag:
1. Open the file [`docker-compose.yml`](./docker-compose.yml) in a text editor.
2. Find the line beginning with `CTF_FLAG`, which is nested under:
```
services
|
|__├──├
```

Simply modify the contents of [`src/server/flag.txt`](./src/server/flag.txt) to update the flag.
There are no restrictions on what `flag.txt` may contain.

#### Managing the Docker Container

There is a supplied Bash script, [`dockerHelper.sh`](./dockerHelper.sh), that will assist with managing the Docker container for this CTF.
Running `dockerHelper.sh` without any parameters or passing it the `-h` parameter will print a help dialogue for the script.
You may need to run `dockerHelper.sh` with root privileges if any of the Docker commands executed by the script fail.
The following is a summary of the available functions supplied by the script:

| Function                    | Command                         |
| --------------------------- | ------------------------------- |
| Build the Docker Image      | `$ [sudo] ./dockerHelper.sh -b` |
| Start the Docker App        | `$ [sudo] ./dockerHelper.sh -r` |
| Check the Docker App Status | `$ [sudo] ./dockerHelper.sh -s` |
| Stop the Docker App         | `$ [sudo] ./dockerHelper.sh -k` |

Commands can be concatenated in one call to the script, and the function will be executed in the order in which the argument flag appears:
* `$ [sudo] ./dockerHelper -rs` will start the Docker app, then print the status of the app.
* `$ [sudo] ./dockerHelper -kbr` will stop the Docker app, then rebuild it before running again.

#### Deploying the Challenge

The source code of the binaries that is given to the students is kept closed source so that the students do not have visibility of it while reverse engineering the binary executable.
The source code specifies some default values, so please contact the project adminstrators to request a copy of the source code and instructions on how to compile it if you would like to change those default values.

## For the Student(s)

You will be supplied a binary executable and it is your task to reverse engineer the binary in order to retrieve the flag.
