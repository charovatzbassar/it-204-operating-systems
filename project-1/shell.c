#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10
#define MAX_BUFFER_SIZE 256

char* getCommandOutput(char* command) {
	FILE* pipe = popen(command, "r");
	if (!pipe) {
		perror("popen");
		exit(EXIT_FAILURE);
	}

	char* output = (char*)malloc(MAX_BUFFER_SIZE * sizeof(char));
	if (!fgets(output, MAX_BUFFER_SIZE, pipe)) {
		perror("fgets");
		exit(EXIT_FAILURE);
	}

	pclose(pipe);

	size_t len = strlen(output);
	if (len > 0 && output[len - 1] == '\n') {
		output[len - 1] = '\0';
	}

	return output;
}

void executeCommand(char *args[]) {
    int p = fork();
    if (p < 0) {
        fprintf(stderr, "Fork failed\n");
        exit(1);
    } else if (p == 0) {
        if (execvp(args[0], args) < 0) {
            fprintf(stderr, "Exec failed\n");
            exit(1);
        }
    } else {
        wait(NULL); 
    }
}



int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];

    while (1) {

        printf("\033[1;36m%s\033[0m@\033[1;33m%s\033[0m:~$ ", getCommandOutput("hostname"), getCommandOutput("whoami"));

        fgets(command, MAX_COMMAND_LENGTH, stdin);

        command[strcspn(command, "\n")] = '\0';

        char *token = strtok(command, " ");
        int argCount = 0;
        while (token != NULL && argCount < MAX_ARGUMENTS - 1) {
            arguments[argCount++] = token;
            token = strtok(NULL, " ");
        }
        arguments[argCount] = NULL;

	if (argCount == 0) continue;
       
        if (strcmp(arguments[0], "exit") == 0) {
            break;
        } else if (strcmp(arguments[0], "cat") == 0) {
		printf("Cat command\n");
	} else if (strcmp(arguments[0], "clear") == 0) {
		printf("Clear command\n");
	} else if (strcmp(arguments[0], "rm") == 0) {
		printf("Rm command\n");
	} else if (strcmp(arguments[0], "cowsay") == 0) {
		printf("Cowsay command\n");
	} else {
		printf("Invalid input\n");
	}
	


    }

    return 0;
}

