# Simple_Shell

### Overview
`shell` is a UNIX command interpreter that replicates core functionalities of the `sh` shell. This project was developed as part of the third month curriculum at [Alx Africa](https://www.\alxafrica.com/).

### Installation
Clone this repository to your local system and compile using `gcc -Wall -Werror -Wextra -pedantic *.c`.

### Usage
* Once in the shell, use exactly like `sh`. A list of covered features is provided below. The shell can run in either interactive or non-interactive mode.
* Function returns with the specified exit status.

### Features
The shell handles command line input, including arguements, without the use of most standard library functions such as `printf`, `strtok`, or `getline`. In addition to running executables in the PATH, the following features are currently implemented.

|  Builtin Commands  |    Functionality                            |
| ------------------ | ------------------------------------------- |
| `exit [status]`    | Exit shell with specified exit status       |
| `env`              | Print list of current environment variables |
| `setenv`           | Set an environment variable                 |
| `unsetenv`         | Unset an environment variable               |
| `cd`               | Change directories                          |
| `history`			 | Prints command history					   |
| `help` 			 | Displays help for builtin commands		   |
| `alias`			 | Alias a command as another or print aliases |

|  Other Features    |    Functionality                            |
| ------------------ | ------------------------------------------- |
| `Ctrl-D`           | End of file - exit shell                    |
| `Ctrl-C`           | Does not exit shell - (Differs from `sh`)   |
| `;`                | Command separator, allows command chaining  |
| `#`                | Comment indicator                           |
| `<`				 | Redirect input							   |
| `>`				 | Redirect output							   |
| `<<`				 | Append input (heredoc)					   |
| `>>`				 | Append output							   |

### Example Usage
* This shell takes input the same as a standard unix shell.  After running the executable `hsh`, enter desired input and press return.
* `ls -l`
* `exit 98`
* `cd -`

### About
All files were created and compiled on `Ubuntu 14.04.4 LTS` using `GCC 4.8.4` with the following flags: `-Wall -Werror -Wextra -pedantic`

### Authors
* Yassine Borak [Github](https://github.com/pro0pegasus) 
* [Mohamed amine Toumi cherkaoui](https://github.com/Aminetoumi0) 
