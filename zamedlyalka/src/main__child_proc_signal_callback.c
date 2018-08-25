void childProcSignalCallback(int signum)
{
    if (signum == SIGUSR1)
    {
        //received = 1;
        read(fdPipe[0], commandBuf, COMMAND_BUF_SIZE);
        processCommand(commandBuf);
    }
    signal(signum, childProcSignalCallback);
}
