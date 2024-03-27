#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void execute_command(char *command[]) {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        printf("Child process executing...\n");

        // Execute a command using execv
        execv(command[0], command);

        // If execv returns, it must have failed
        perror("Exec failed");
        exit(EXIT_FAILURE);
    } else {
        // Parent process
        printf("Parent process waiting for child to complete...\n");

        // Wait for child process to complete
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process terminated abnormally\n");
        }

        // Send SIGKILL signal to the child process
        printf("Sending SIGKILL signal to the child process...\n");
        if (kill(pid, SIGKILL) == -1) {
            perror("Kill failed");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    // Command to execute
    char *command[] = {"/bin/sleep", "10", NULL};

    // Call the function to execute the command
    execute_command(command);

    return 0;
}
