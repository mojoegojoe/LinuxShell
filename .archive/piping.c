void pipe_cmd(int n, instruction* command)
{
    int in = 0,fd[2], i;
    int pid, status,pipest;

    // if(externalIn)
    // {
    //     in = open(inputfile, O_RDONLY); // open the file
    //     if(in < 0)
    //     {
    //         perror("+--- Error in executable : input file ");
    //     }
    // }
    //printf("%d %d\n",command[0].argcount,n );
    // enters only in case of pipes
    for (i = 1; i < n; i++)
    {
        /*printf("Input ");
        int k;
        for(k=0;k<command[0].argcount;k++)
        {
            printf("%s ",command[0].argval[k]);
        }*/
        //printf("i is in loop : %d %s\n",i-1,command[i-1].argval[0]);
        pipe (fd);// fd[0] => fd[1] i.e, r=>w
        int id = fork();
        if (id==0)
        {

            if (in!=0)
            {
                dup2(in, 0);
                close(in);
            }
            if (fd[1]!=1)
            {
                dup2(fd[1], 1);
                close(fd[1]);
            }

            //printf("pipe_dup send %s to runprocess\n",command[i].argval[0]);
            runprocess(command[i-1].argval[0], command[i-1].argval,command[i-1].argcount);
            exit_shell(0);

        }
        else wait(&pipest);
        close(fd[1]);
        in = fd[0]; // store input for next child, it there is one
    }
    i--; // for final case
    // keep a copy of current file descriptor
    if(in != 0)
    {
        dup2(in, 0);
    }
    // if(externalOut)
    // {
    //     int ofd = open(outputfile, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    //     dup2(ofd, 1);
    // }
    //  printf("cli sent from pipe_dup : %s\n",command[i].argval[0]);
    runprocess(command[i].argval[0], command[i].argval, command[i].argcount);
}