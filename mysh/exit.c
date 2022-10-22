#include "exit.h"



/********************************************************
/    @FUNCION exit_shell
/    @input   int - Exit number
/             
/                      
/    @output  void 
/    @method  Wrapper for the exit call.
/           Takes an error number as input and exits the
/           process with the error number as the return
/           value
/
********************************************************/
void exit_shell(int errorn) {
    exit(errorn);
}