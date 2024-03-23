#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_BUFFER_SIZE 256

char* getHostnameOutput() {
    FILE *hostname_pipe = popen("hostname", "r");
    if (!hostname_pipe) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Read the output of the "hostname" command
    char* hostname_output = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (!fgets(hostname_output, MAX_BUFFER_SIZE, hostname_pipe)) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    // Close the pipe
    pclose(hostname_pipe);

    size_t len = strlen(hostname_output);
    if (len > 0 && hostname_output[len - 1] == '\n') {
    	hostname_output[len - 1] = '\0';
    }

    return hostname_output;
}

char* getWhoamiOutput() {
    // Open a pipe to execute the "whoami" command
    FILE *whoami_pipe = popen("whoami", "r");
    if (!whoami_pipe) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    // Read the output of the "whoami" command
    char *whoami_output = (char *)malloc(MAX_BUFFER_SIZE * sizeof(char));
    if (!fgets(whoami_output, MAX_BUFFER_SIZE, whoami_pipe)) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }

    // Close the pipe
    pclose(whoami_pipe);

    // Remove the newline character at the end
    size_t len = strlen(whoami_output);
    if (len > 0 && whoami_output[len - 1] == '\n') {
        whoami_output[len - 1] = '\0';
    }

    return whoami_output;
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    int status;

    while (1) {
        // Print a prompt
	

        printf("\033[1;36m%s\033[0m@\033[1;33m%s\033[0m:~$ ", getHostnameOutput(), getWhoamiOutput());

        // Read the command from the user
        fgets(command, MAX_COMMAND_LENGTH, stdin);

        // Remove newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Parse the command into arguments
        char *token = strtok(command, " ");
        int arg_count = 0;
        while (token != NULL && arg_count < MAX_ARGUMENTS - 1) {
            arguments[arg_count++] = token;
            token = strtok(NULL, " ");
        }
        arguments[arg_count] = NULL;

        // Exit the shell if the user enters "exit"
        if (strcmp(arguments[0], "exit") == 0) {
            break;
        }

        // Fork a child process to execute the command
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            execvp(arguments[0], arguments);
            // If execvp returns, there was an error
            perror("execvp");
            exit(EXIT_FAILURE);
        } else if (pid < 0) {
            // Fork failed
            perror("fork");
        } else {
            // Parent process
            // Wait for the child process to finish
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

