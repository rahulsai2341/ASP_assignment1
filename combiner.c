#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void main(int argc, char * argv[]){
    char *input_file_name = argv[1];

    int pfd[2];
    
    // Initialize the pipe
    if(pipe(pfd) == -1){
        _exit(1);
    }

    // Spawn first child process
    switch (fork())
    {

    // If fork fails
    case -1:
        printf("Fork 1 failed");
        _exit(1);
        break;
    
    // Child gets in here
    case 0:
        // Close read end
        if (close(pfd[0]) == -1){
            printf("CLosing read end failed");
            _exit(1);
        }
        // Direct STDOUT to pipe out(pfd(1))
        if (pfd[1] != STDOUT_FILENO) {              
            if (dup2(pfd[1], STDOUT_FILENO) == -1)
                _exit(1);
            // Close pfd(1) 
            if (close(pfd[1]) == -1)
                _exit(1);
        } 

        // Call the mapper program
        execl("mapper", "mapper", input_file_name, (char *)NULL);
    
    // Parent executes this code
    default:
        break;
    }


    // Spawn second child process
    switch (fork())
    {

    // If fork fails
    case -1:
        printf("Fork 2 failed");
        _exit(1);   
        break;
    
    // Child gets in here
    case 0:
        // Close write end
        if (close(pfd[1]) == -1){
            printf("Closing read end failed");
            _exit(1);
        }
        // Direct STDIN from pipe i0(pfd(1))
        if (pfd[0] != STDIN_FILENO) {             
            if (dup2(pfd[0], STDIN_FILENO) == -1)
                _exit(1);
            // Close pfd(0) 
            if (close(pfd[0]) == -1)
                _exit(1);
        } 

        // Call the reducer program
        execl("reducer", "reducer", (char *)NULL);
    
    // Parent executes this code
    default:
        break;
    }


    // Wait for the child processes
    if (wait(NULL) == -1){
        _exit(1);
    }
        if (wait(NULL) == -1){
        _exit(1);
    }

}