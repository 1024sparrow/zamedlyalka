void sigintHandler(int signum)
{
    if (signum == SIGUSR1)
    {
        received = 1;
    }
    signal(signum, sigintHandler);
}
