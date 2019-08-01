void main(int argc, char **argv)
{
     int i, n = atoi(argv[1]);

     for (i = 0; i < n; i++)
          if (fork() == -1)
               break;
     printf("Process %ld with parent %ld\n", getpid(), getppid());
     sleep(1);
}
