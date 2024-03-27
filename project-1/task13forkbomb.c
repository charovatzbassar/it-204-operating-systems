#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[20];
    char secondin[20];

    // Infinite loop to continuously prompt for input
    while (1) {
        printf("Enter a command (type 'exit' to quit, or 'forkbomb' and prepare for consequences): ");
        fgets(input, sizeof(input), stdin); // Read user input
        
        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        // Check if the user wants to exit
        if (strcmp(input, "exit") == 0) {
            printf("Exiting the program...\n");
            break; // Exit the loop
        } else if (strcmp(input, "forkbomb") == 0) {
            printf("Are you sure about this? (Y/N)");
            fgets(secondin, sizeof(secondin), stdin);
            secondin[strcspn(secondin, "\n")] = '\0'; // Remove newline character
            if (strcmp(secondin, "Y") == 0) {
                while (1) {
                    fork();
                }
            } else {
                printf("Good choice!\n");
            }
        } else {
            printf("There is no such command!\n");
        }
    }
    return 0;
}

