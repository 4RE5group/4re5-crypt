#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define SALT_SIZE 16
#define MAX_INPUT_SIZE 512
#define OUTPUT_SIZE 32

int getSalt(const char* salt) {
    int a = strlen(salt);
    for (int i = 0; i < a; i++) {
        int b = (int)salt[i];
        a += (b % 2 == 0) ? b : -b;
    }
    return (a < 0) ? -a : a % 10;
}

int main(int argc, char* argv[]) {
    char salt[SALT_SIZE] = "";
    char text[MAX_INPUT_SIZE] = "";

    char* outputHash = (char*)malloc(OUTPUT_SIZE + 1);
    if (outputHash == NULL) {
        printf("Memory allocation failure\n");
        return 1;
    }
    outputHash[0] = '\0';  // Initialize outputHash as an empty string

    char newChar;
    int saltInt;

    // Banner
    printf("   █████ █████                     ██████████                                             █████   \n");
    printf("  ░░███ ░░███                     ░███░░░░░░█                                            ░░███    \n");
    printf("   ░███  ░███ █ ████████   ██████ ░███     ░      ██████  ████████  █████ ████ ████████  ███████  \n");
    printf("   ░███████████░░███░░███ ███░░███░█████████     ███░░███░░███░░███░░███ ░███ ░░███░░███░░░███░   \n");
    printf("   ░░░░░░░███░█ ░███ ░░░ ░███████ ░░░░░░░░███   ░███ ░░░  ░███ ░░░  ░███ ░███  ░███ ░███  ░███    \n");
    printf("         ░███░  ░███     ░███░░░   ███   ░███   ░███  ███ ░███      ░███ ░███  ░███ ░███  ░███ ███\n");
    printf("         █████  █████    ░░██████ ░░████████    ░░██████  █████     ░░███████  ░███████   ░░█████ \n");
    printf("        ░░░░░  ░░░░░      ░░░░░░   ░░░░░░░░      ░░░░░░  ░░░░░       ░░░░░███  ░███░░░     ░░░░░  \n");
    printf("                                                                     ███ ░███  ░███               \n");
    printf("           2024 4re5 group - https://4re5group.github.io             ░░██████   █████              \n");
    printf("                                                                     ░░░░░░   ░░░░░               \n");
    printf("\n");

    // Check for input arguments
    if (argc >= 2) {
        if (strlen(argv[1]) >= MAX_INPUT_SIZE) {
            printf("Input text length is way too big: expected between 1 to %d chars\n", MAX_INPUT_SIZE - 1);
            free(outputHash);
            return 1;
        }
        strcpy(text, argv[1]);

        if (strlen(text) == 0) {
            printf("Please enter a valid text to crypt\n");
            free(outputHash);
            return 1;
        }

        printf("-----------------------------------------------------------\n");
        
        // If the salt argument is provided but empty, or if it's not provided, use `text` as the salt
        if (argc >= 3 && strlen(argv[2]) > 0) {
            if (strlen(argv[2]) >= SALT_SIZE) {
                printf("Invalid salt length: expected between 1 to %d characters\n", SALT_SIZE - 1);
                free(outputHash);
                return 1;
            }
            strcpy(salt, argv[2]); // Copy provided salt
            saltInt = getSalt(salt);
            printf("Encrypting '%s' with salt '%s'...\n", text, salt);
        } else {
            saltInt = getSalt(text); // Use text as salt if salt is empty or not provided
            printf("Encrypting '%s' without salt, using text as salt...\n", text);
        }

        printf("    saltInt => %d\n", saltInt);
        printf("-----------------------------------------------------------\n");

        char char1, char2;
        int running = 1;
        while (running) {
            for (int i = 0; i < strlen(text) - 1; i += 2) {
                char1 = text[i];
                if (i + 1 < strlen(text)) {
                    char2 = text[i + 1];
                }

                int transformedChar = (i + strlen(outputHash) + (int)char1 + (int)char2) + saltInt;

                // Ensure the transformed character is within ASCII 20 to 126
                while (transformedChar > 126 || transformedChar <= 32) {
                    transformedChar -= 106;
                }
                newChar = (char)transformedChar;

                // Append the new character to the outputHash
                size_t len = strlen(outputHash);
                if (len < OUTPUT_SIZE - 1) {
                    outputHash[len] = newChar;
                    outputHash[len + 1] = '\0';
                } else {
                    running = 0;
                    break;
                }
            }
        }

        printf("done: here's your hash:\n%s\n", outputHash);

        // Clean up
        free(outputHash);
    } else {
        printf("usage: %s <text> [salt]\n", argv[0]);
        free(outputHash);
        return 1;
    }

    return 0;
}
