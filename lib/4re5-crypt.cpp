#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "4re5-crypt.h"
#include <iostream>


namespace crypt4re5 {
    int getSalt(const char* salt) {
        int a = strlen(salt);
        for (int i = 0; i < a; i++) {
            int b = (int)salt[i];
            a += (b % 2 == 0) ? b : -b;
        }
        return (a < 0) ? -a : a % 10;
    }

    void crypt(char* output, const char* _text, const char* _salt) {
        char salt[SALT_SIZE] = "";
        char text[MAX_INPUT_SIZE] = "";

        char* outputHash = (char*)malloc(OUTPUT_SIZE + 1);
        if (outputHash == NULL) {
            std::cerr << "Memory allocation failure";
            return;
        }
        outputHash[0] = '\0';  // Initialize outputHash as an empty string

        char newChar;
        int saltInt;


        // Check for input arguments
        if (strlen(_text) >= MAX_INPUT_SIZE) {
            printf("Input text length is way too big: expected between 1 to %d chars\n", MAX_INPUT_SIZE - 1);
            free(outputHash);
            return;
        }
        strcpy(text, _text);
        if (strlen(text) == 0) {
            printf("Please enter a valid text to crypt\n");
            free(outputHash);
            return;
        }
        
        // If the salt argument is provided but empty, or if it's not provided, use `text` as the salt
        if (_salt != "" && _salt && strlen(_salt) > 0) {
            if (strlen(_salt) >= SALT_SIZE) {
                free(outputHash);
                return;
            }
            strcpy(salt, _salt); // Copy provided salt
            saltInt = getSalt(salt);
        } else {
            saltInt = getSalt(text); // Use text as salt if salt is empty or not provided
        }
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
 
        // Clean up
        // std::string copy = outputHash;
        

        std::cout << outputHash << std::endl;

        strcpy(output, outputHash);
        // output = outputHash;
        
        free(outputHash);
    }
};