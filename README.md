# LinuxShell
The mysh program provides a subset of the functionality provided by common Linux shells such as bash.

# Genral
  The program is implemented in C and is easily buildable though the "make" command. Is a stand alone program, meaning that not only the standard C libary is [not] used for all functional components, instead we fully utalized the portable linux system calls. 

# Functionally
  Fully interactive interface the allows for repeated user inputed prompts from the standard input libary, execute the process (with appropriate user error message when execution is not possible) and return an output to the user. This proceses is continued indefintaly until the user exit_shells mysh.\
  The shell can run an interactive login screen, when accessed a client can access one or more user accounts. 
  
# Shell IO
  {cmd | arg |} &  - Command Runs in the Background. \
  {cmd | arg } | {cmd | arg} | ... - Connects procedually two or more processes. \
  {cmd | arg < } [V] { cmd | arg > } [V] ... - Allows for user defined redirected output : subset of redirection functionality to be extended. \
  Users can access any external command from the mysh system directly via absoulute pathname that can be found via a search (tab) extention. \
  \
  We also made some fun signals like Ctrl + C to end a current proccess, continue, pause and kill process commands.\
