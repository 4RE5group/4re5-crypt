#ifndef ARESCRYPT_H
#define ARESCRYPT_H

#define SALT_SIZE 16
#define MAX_INPUT_SIZE 512
#define OUTPUT_SIZE 32

namespace crypt4re5 {
    // Function to get salt from a provided string
    int getSalt(const char* salt);

    // Function to create a hash
    void crypt(char* output, const char* _text, const char* _salt="");
};

#endif // HASHLIB_H
