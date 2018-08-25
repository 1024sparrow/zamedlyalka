void parentProcSignalCallback(int signum)
{
    if (signum == SIGUSR1)
    {
    }
    signal(signum, parentProcSignalCallback);
}
