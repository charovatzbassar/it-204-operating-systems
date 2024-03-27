#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

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




char* intToRoman(int num) {
    static char romanNumeral[20];
    char romanCharacters[] = {'M', 'D', 'C', 'L', 'X', 'V', 'I'};
    int values[] = {1000, 500, 100, 50, 10, 5, 1};
    int i = 0, j = 0;

    while (num > 0) {
        int count = num / values[i];
        for (int k = 0; k < count; k++) {
            romanNumeral[j++] = romanCharacters[i];
        }
        num %= values[i];
        i++;
    }

    romanNumeral[j] = '\0';

    // Replace substrings for special cases
    char* specialCases[] = {"IIII", "VIV", "XXXX", "LXL", "CCCC", "DID"};
    char* replacements[] = {"IV", "IX", "XL", "XC", "CD", "CM"};

    for (int k = 0; k < 6; k++) {
        char* found = strstr(romanNumeral, specialCases[k]);
        if (found != NULL) {
            strcpy(found, replacements[k]);
        }
    }

    return romanNumeral;
}

int isInArray(char *target, char **array, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(target, array[i]) == 0) {
            return i; // String found in array
        }
    }
    return -1; // String not found in array
}


char** sliceArray(char* arr[], int start, int end) {
    int length = end - start + 1;
    char** sliced_arr = (char**)malloc(length * sizeof(char*));
    if (!sliced_arr) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    for (int i = start; i <= end; i++) {
        sliced_arr[i - start] = arr[i];
    }

    return sliced_arr;
}

void cat(char* args[], int argCount) {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {

        FILE *file;
    	char* filename;
    	char line[100];

	if (args[1] == NULL) {
		file = stdin;
	} else {
		filename = args[1];
    		file = fopen(filename, "r");
    		if (file == NULL) {
            		fprintf(stderr, "Error opening file %s\n", filename);
            		exit(1);
    		}

	}

	FILE* output_file = NULL;

	int redirectIndex = isInArray(">", args, argCount);

	if (redirectIndex > 0) {
		output_file = fopen(args[redirectIndex+1], "w");
		if (output_file == NULL) {
    			perror("Failed to open output file");
    			exit(1);
		}
	}

	int lineNumber = 1;

    	while (fgets(line, sizeof(line), file) != NULL) {
	    if (argCount > 2 && strcmp(args[2], "-n") == 0) {
                printf("%d %s", lineNumber, line);
		if (redirectIndex > 0) {
		    fprintf(output_file, "%d %s", lineNumber, line);
		}
            } else if (argCount > 2 && strcmp(args[2], "-roman") == 0) { 
	        if (redirectIndex > 0) {
			fprintf(output_file, "%s %s", intToRoman(lineNumber), line);
		}
		printf("%s %s", intToRoman(lineNumber), line);

	    } else {
                if (redirectIndex > 0) {
		    fprintf(output_file, "%s", line);
		}
		printf("%s", line);
            }
            lineNumber++;
	}

	
    	if (file != stdin) {
            fclose(file);
        } 
        if (output_file != NULL) {
            fclose(output_file);
        }
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
    	system("clear");
    } else {
    	wait(NULL);
    }

}

void cowsay(char* args[], int argCount) {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
      char cowsayText[100] = "";

      	FILE* output_file = NULL;
        int redirectIndex = isInArray(">", args, argCount);

        if (redirectIndex > 0) {
                output_file = fopen(args[redirectIndex+1], "w");
                if (output_file == NULL) {
                        perror("Failed to open output file");
                        exit(1);
                }
        }

	int endPoint = redirectIndex > 0 ? redirectIndex : argCount;


      for (int i = 1; i < endPoint; i++) {
       	  strcat(cowsayText, args[i]);
	  strcat(cowsayText, " "); 
       }

if (redirectIndex > 0) {
      fprintf(output_file, "     < %s>\n", cowsayText);
      fprintf(output_file, "        \\   ^__^\n");
      fprintf(output_file, "         \\  (oo)\\_______\n");
      fprintf(output_file, "            (__)\\       )\\/\\\n");
      fprintf(output_file, "                ||----w |\n");
      fprintf(output_file, "                ||     ||\n");

      fclose(output_file);
}

      printf("     < %s>\n", cowsayText);
      printf("        \\   ^__^\n");
      printf("         \\  (oo)\\_______\n");
      printf("            (__)\\       )\\/\\\n");
      printf("                ||----w |\n");
      printf("                ||     ||\n");

    } else {
        wait(NULL);
    }

}


void forkbomb() {
    while(1) {
        fork();
    }
}

void magic8() {
    int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {
        char* fortunes[16] = {
    "Yes, definitely.",
    "Without a doubt.",
    "You may rely on it.",
    "Most likely.",
    "Outlook good.",
    "Signs point to yes.",
    "Reply hazy, try again.",
    "Ask again later.",
    "Better not tell you now.",
    "Cannot predict now.",
    "Concentrate and ask again.",
    "Don't count on it.",
    "My reply is no.",
    "My sources say no.",
    "Outlook not so good.",
    "Very doubtful."
};
	
srand(time(NULL));

char* fortune = fortunes[rand() % 16];

    printf(" .-\"\"\"-.\n");
    printf("/   _   \\\n");
    printf("|  (8)  |\n");
    printf("\\   ^   /\n");
    printf(" '-...-'\n");

    printf("Your fortune is: %s\n", fortune);
	

	
    } else {
        wait(NULL);
    }

}

void draw(char* args[]) {
   int p = fork();

    if (p < 0) {
        perror("Fork failed");
        exit(1);
    } else if (p == 0) {

	 if (args[1] == NULL) {
	 	printf("Usage: draw <no. of cards>\n");
		exit(1);
	 }

        int numOfCards = atoi(args[1]);

	char* values[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
	char* suits[4] = {"♠", "♥", "♣", "♦"};

	srand(time(NULL));

	for (int i = 1; i <= numOfCards; i++) {
	    char* value = values[rand() % 16];
	    char* suit = suits[rand() % 4];

	    printf("Card %d: %s%s\n", i, value, suit);
	}

    } else {
        wait(NULL);
    }

}

void prepareCommand(char command[]) {
     char *arguments[MAX_ARGUMENTS];

     char *token = strtok(command, " ");
     int argCount = 0;
     while (token != NULL && argCount < MAX_ARGUMENTS - 1) {
            arguments[argCount++] = token;
            token = strtok(NULL, " ");
     }
     arguments[argCount] = NULL;



    executeCommand(arguments, argCount);

}

void executeCommand(char* arguments[], int argCount) {
	if (argCount == 0) return;
	
	int pipeSymbolLocation = isInArray("|", arguments, argCount);	

	if (pipeSymbolLocation > 0) {
		char command1[100] = "";
		char command2[100] = "";

	for (int i = 0; i < pipeSymbolLocation; i++) {
          strcat(command1, arguments[i]);
          strcat(command1, " ");
       }

	for (int i = pipeSymbolLocation + 1; i < argCount; i++) {
          strcat(command2, arguments[i]);
          strcat(command2, " ");
       }

	prepareCommand(command1);
	prepareCommand(command2);



	} else {
		
        if (strcmp(arguments[0], "cat") == 0) {
                cat(arguments, argCount);
        } else if (strcmp(arguments[0], "clear") == 0) {
                clear(arguments);
        } else if (strcmp(arguments[0], "rm") == 0) {
                rm(arguments);
        } else if (strcmp(arguments[0], "cowsay") == 0) {
                cowsay(arguments, argCount);
        } else if (strcmp(arguments[0], "forkbomb") == 0) {
                forkbomb();
        } else if (strcmp(arguments[0], "magic8") == 0) {
		magic8();
	} else if (strcmp(arguments[0], "draw") == 0) {
		draw(arguments);
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
     
}




int main() {
	system("clear");
    char command[MAX_COMMAND_LENGTH];
    printf("  .g8\"\"8q. `7MM\"\"\"Mq.  `7MM\"\"\"Yp,      db      `YMM'   `MP' \n");
    printf(".dP'    `YM. MM   `MM.   MM    Yb     ;MM:       VMb.  ,P   \n");
    printf("dM'      `MM MM   ,M9    MM    dP    ,V^MM.       `MM.M'    \n");
    printf("MM        MM MMmmdM9     MM\"\"\"bg.   ,M  `MM         MMb     \n");
    printf("MM.      ,MP MM  YM.     MM    `Y   AbmmmqMA      ,M'`Mb.   \n");
    printf("`Mb.    ,dP' MM   `Mb.   MM    ,9  A'     VML    ,P   `MM.  \n");
    printf("  `\"bmmd\"' .JMML. .JMM..JMMmmmd9 .AMA.   .AMMA..MM:.  .:MMa.\n");

    while (1) {

        printf("\033[1;36m%s@%s\033[0m:\033[1;33m%s\033[0m$ ", getCommandOutput("whoami"), getCommandOutput("hostname"), getCommandOutput("pwd"));

        fgets(command, MAX_COMMAND_LENGTH, stdin);

        command[strcspn(command, "\n")] = '\0';


        prepareCommand(command);
	

        
	


    }

    return 0;
}

