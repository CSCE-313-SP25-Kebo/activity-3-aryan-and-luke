#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(int argc, char *argv[])
{
    int option = 0; // default option: execute the command ls -l and terminate normally

    // Get flag from command line
    int opt;
    while ((opt = getopt(argc, argv, "n:")) != -1)
    {
        switch (opt)
        {
        case 'n':
            option = atoi(optarg);
            break;
        }
    }

    /* TODO: FORK A NEW PROCESS */
    int p = fork();
    if (p < 0/* TODO: CONDITION IF FORK FAILS*/)
    {
        cout << "Fork failed" << endl;
        return 1;
    }
    else if (p == 0/* TODO: CONDITION IF CHILD PROCESS */)
    {
        cout << "Hello from the child process!" << endl;
        /* TODO: PRINT THE PARENT PID value: "The parent process ID is $ID" */
        cout << "The parent process ID is " << getppid() << endl;
        if (option % 2 == 0) // if the option number is even, execute the command ls -l and terminate normally
        {
            std::cout << "The child process will execute the command: ls -l after 6 seconds" << std::endl;
            /* TODO: SLEEP FOR 6 SECONDS*/
            sleep(6);
            /* TODO: EXECUTE THE COMMAND ls -l USING EXECVP*/
            const char * c = "ls";
            constexpr char * args[] = {"ls", "-l", NULL};
            execvp(c, args);
        }
        else // if the option number is odd, terminate with a kill signal
        {
            std::cout << "The child process is exiting" << std::endl;
            kill(getpid(), SIGINT);
        }
    }
    else if (p > 0 /*TODO: CONDITION IF PARENT PROCESS*/)
    {
        // int status;

        /* TODO: WAIT FOR CHILD PROCESS TO FINISH */
        wait(nullptr);

        cout << "\nHello from the parent process!" << endl;

        /* TODO: PRINT THE CHILD PID value: "The child process ID is $ID" */
        cout << p;

        /* TODO: PRINT THE EXIT STATUS OF THE CHILD PROCESS BASED waitpid().
        MAKE SURE TO PASS BY REFERENCE THE STATUS VARIABLE TO THE SECOND PARAMETER OF waitpid()
        IF WIFEXITED, PRINT THE MESSAGE "The child process exited normally" WITH ENDLINE
        IF WIFSIGNALED, PRINT THE MESSAGE "The child process exited due to the kill signal" WITH ENDLINE
        */
        int* s = nullptr;
        waitpid(p, s, 0);
        if (WIFEXITED(*s)) {
            cout << "The child process exited normally" << endl;
        } else if (WIFSIGNALED(*s)) {
            cout << "The child process exited due to the kill signal" << endl;
        }
    }

    return 0;
}