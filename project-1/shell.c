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

void cat(char* args[]) {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
        FILE *file;
    	char* filename = args[1];
    	char line[100];

    	file = fopen(filename, "r");
    	if (file == NULL) {
            fprintf(stderr, "Error opening file %s\n", filename);
            exit(1);
    	}

    	while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
        }

    	fclose(file);
    } else {
        wait(NULL);
    }

}

void rm(char* args[]) {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
        char* filename = args[1];

    	if (remove(filename) == 0) {
       	    printf("File %s removed successfully.\n", filename);
        } else {
       	    fprintf(stderr, "Error removing file %s\n", filename);
	 }

    } else {
        wait(NULL);
    }

}

void clear(char* args[]) {
    int p = fork();

    if (p < 0) {
    	perror("Fork failed");
	exit(1);
    } else if (p == 0) {
    	printf("\033[2J");
    	printf("\033[H");
    } else {
    	wait(NULL);
    }

}

void cowsay(char* args[]) {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
      char* cowsayText = args[1];

      printf("     <%s>\n", cowsayText);
      printf("        \\   ^__^\n");
      printf("         \\  (oo)\\_______\n");
      printf("            (__)\\       )\\/\\\n");
      printf("                ||----w |\n");
      printf("                ||     ||\n");



    } else {
        wait(NULL);
    }

}



int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];

    while (1) {

        printf("\033[1;36m%s@%s\033[0m:\033[1;33m%s\033[0m$ ", getCommandOutput("hostname"), getCommandOutput("whoami"), getCommandOutput("pwd"));

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
		cat(arguments);
	} else if (strcmp(arguments[0], "clear") == 0) {
		clear(arguments);
	} else if (strcmp(arguments[0], "rm") == 0) {
		rm(arguments);
	} else if (strcmp(arguments[0], "cowsay") == 0) {
		cowsay(arguments);
	} else {
		int p = fork();

		if (p < 0) {
		    perror("fork");
		    exit(1);
		} else if (p == 0) {
		    execvp(arguments[0], arguments);
		    perror("execvp");
		    exit(1);
		} else {
		    wait(NULL);
		}
	}
	


    }

    return 0;
}

