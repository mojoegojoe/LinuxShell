#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g -Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: mysh

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
mysh:  shell.o piping.o redirection.o run_proc.o built_in_handler.o exit.o pwd.o cd.o echo.o str_functions.o output.o input.o
	$(CC) $(CFLAGS) -o mysh shell.o piping.o redirection.o run_proc.o built_in_handler.o  exit.o pwd.o cd.o echo.o str_functions.o output.o input.o

# To create the object file countwords.o, we need the source
# files countwords.c, scanner.h, and counter.h:
#
shell.o:  shell.c shell.h common.h 
	$(CC) $(CFLAGS) -c shell.c

piping.o:  piping.c piping.h common.h 
	$(CC) $(CFLAGS) -c piping.c

redirection.o:  redirection.c redirection.h common.h
	$(CC) $(CFLAGS) -c redirection.c

run_proc.o:  run_proc.c run_proc.h common.h
	$(CC) $(CFLAGS) -c run_proc.c

built_in_handler.o:  built_in_handler.c built_in_handler.h common.h cd.h pwd.h echo.h exit.h
	$(CC) $(CFLAGS) -c built_in_handler.c 

cd.o: cd.c cd.h common.h output.h 
	$(CC) $(CFLAGS) -c cd.c

pwd.o: pwd.c pwd.h common.h 
	$(CC) $(CFLAGS) -c pwd.c

exit.o: exit.c exit.h
	$(CC) $(CFLAGS) -c exit.c

echo.o: echo.c echo.h str_functions.h common.h 
	$(CC) $(CFLAGS) -c echo.c

str_functions.o:  str_functions.c str_functions.h common.h
	$(CC) $(CFLAGS) -c str_functions.c

output.o:  output.c output.h common.h
	$(CC) $(CFLAGS) -c output.c

input.o:  input.c input.h common.h
	$(CC) $(CFLAGS) -c input.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) mysh *.o *~