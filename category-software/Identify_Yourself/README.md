# CTF - Identify Yourself

## For the Instructor(s)

### Easy and Hard Challenges

The Docker image used for this challenge is running [xinetd](https://en.wikipedia.org/wiki/Xinetd), which will listen for incoming TCP connection requests and establish a connection.

This CTF has been broken into two nearly identical versions, with one being denoted as the easy version, and the other denoted as the hard version.
The difference between the easy and hard version of the challenge is the binary executable that is supplied to the students.
The two versions of the binary are compiled from the same source code, and both behave very similarly.
Students should reverse engineer the binary in order to retrieve the flag.

The easy and hard versions of the challenge can be deployed simultaneously from the same host machine.
Only one Docker container is needed to run both the easy and hard versions of the challenge.

**NOTE:** There is only one flag, so it is recommended to run one version of the CTF to it's completion, bring the challenge down, modify the flag, then start the next version of the challenge.

#### Configuring the Docker Image

##### Modifying the Flag

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
