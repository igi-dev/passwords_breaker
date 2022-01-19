# PASSWORDS BREAKER
## Overview
Program was started during the "RT Operating Systems" classes at university and continued in free time. Its main purpose is to break MD5 hashed passwords using dictionary attack based method.

## Usage
### Compilation and running
To compile the program you can use makefile located in ```src/``` directory. In order to run it just invoke ```./pass_breaker```

### Features
#### New files with passwords
After start program will start to break 12 passwords given in ```passwords/my_passwords.txt``` file. When its done it will ask if user wants to try with another file. If yes it will ask new filename with passwords and start breaking it.
#### Statistics
Program is non-verbose, but it can show summary of latest work. To get the summary you need to send SIGHUP signal to the process (e.g. ```kill -HUP PID```).

 
