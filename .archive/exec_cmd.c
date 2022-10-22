#define INPUT_BUFFER_SIZE 80

typedef struct command { 
    char * cmd;
    char * args;
    int arg_count;
} Command;

typedef struct command_pipe { 
    Command *cmd1;
    Command *cmd2;
} CommandPipe;

typedef struct command_redirect {

}

void runprocess(char * cli, char* args[], int count)
{
    /*int i;
    printf("open file now\n");
    printf("cli : %s\n",cli );
    for(i = 0; i < count; i++ )
    {
        printf("arg %d %s \n",i,args[i] );
    }
    printf("\n" );
    */
    int ret = execvp(cli, args);
    char* pathm;
    pathm = getenv("PATH");// check for all paths , executing non./
    char path[1000];
    strcpy(path, pathm);
    strcat(path,":");
    strcat(path,cwd);
    char * cmd = strtok(path, ":\r\n");
    while(cmd!=NULL)
    {
       char loc_sort[1000];
        strcpy(loc_sort, cmd);
        strcat(loc_sort, "/");
        strcat(loc_sort, cli);
        printf("execvp : %s\n",loc_sort );
        ret = execvp(loc_sort, args);
        if(ret==-1)
        {
            perror("+--- Error in running executable ");
            exit_shell(0);
        }
        cmd = strtok(NULL, ":\r\n");
    }
}