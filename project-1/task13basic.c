#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_task() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing...\n");

        // Execute a command using exec
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);

        // If execvp returns, it must have failed
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process waiting for child to complete...\n");
        wait(NULL);
        printf("Child process completed, parent continuing...\n");
    }
}

int main() {
    execute_task();
    return 0;
}
