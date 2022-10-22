# LinuxShell
The mysh program provides a subset of the functionality provided by common Linux shells such as bash.

# Genral
  The program is implemented in C and is easily buildable though the "make" command. Is a stand alone program, meaning that not only the standard C libary is [not] used for all functional components, instead we fully utalized the portable linux system calls. 

# Functionally
## Known Bugs
  Echo function - dependent on limit of string print 
  
## Functional requirment
  Fully interactive interface the allows for repeated user inputed prompts from the standard input libary, execute the process (with appropriate user error message when execution is not possible) and return an output to the user. This proceses is continued indefintaly until the user exits mysh.\
  The shell can run an interactive login screen, when accessed a client can access one or more user accounts. 
  
# Shell IO
  {cmd | arg |} &  - Command Runs in the Background. \
  {cmd | arg } | {cmd | arg} | ... - Connects procedually two or more processes. \
  {cmd | arg < } [V] { cmd | arg > } [V] ... - Allows for user defined redirected output : subset of redirection functionality to be extended. \
  
# File/Dependency Tree
| src  	| Root  	| lvl 0 	| lvl 1 	| clear up 	|
|---	|---	|---	|---	|---	|
|   LICENSE 	|   	|   	|   	|   	|
|   README.md	|   	|   	|   	|   	|
|   mysh	| MakeFile	|   	|   	|   	|
|   	|  shell.c 	|   	|   	|   	|
|   	|   	|  commmon.c 	| unistd.h sys/types.h sys/wait.h sys/stat.h fcntl.h	|   stdio.h stdlib 	|
|   	|   	| run-proc.c 	| common.h str_functions.h built_in_handler.h redirection.h |   	|
|   	|   	|  piping.c 	| run_proc.h str_functions.h shell.h 	|   	|
|   	|   	|  built_in_handler.c 	| common.h str_functions.h pwd.h cd.h echo.h 	|   	|
|   	|   	|  input.c 	| common.h  |   	|
|   	|   	|  output.c 	| common.h 	|   	|
|---  |---  |---  |---  |---  |
|File | File Name | Function  | ||
|| built_in_handler.h| | | |
|| cd.h| | | |
|| common.h| | | |
|| echo.h| | | |
|| error.h| | | |
|| input.h| | | |
|| output.h| | | |
|| piping.h| | | |
|| pwd.h| | | |
|| redirection.h| | | |
|| run_proc.h| | | |
|| shell.h| | | |
|| str_functions.h| | | |
|| strtok.h | | | | 
|---  |---  |---  |---  |---  |
