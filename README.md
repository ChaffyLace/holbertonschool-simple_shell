# holbertonschool-simple_shell
A simple UNIX command line interpreter developed for Holberton School.

## Description
This shell can:
* Display a prompt and wait for the user to type a command.
* Execute commands with their arguments (ex: `ls -l /tmp`).
* Handle the `PATH` to find executable programs.
* Implement built-ins: `exit` and `env`.
* Handle the end-of-file (Ctrl+D).

## Compilation
The shell is compiled this way:
```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
Usage
Interactive mode:

Bash

$ ./hsh
($) /bin/ls
hsh main.c shell.h
($) exit
Non-interactive mode:

Bash

$ echo "/bin/ls" | ./hsh
hsh main.c shell.h

<img width="517" height="772" alt="image" src="https://github.com/user-attachments/assets/d298001c-8d88-4081-a820-b1908c7fd7ee" />
