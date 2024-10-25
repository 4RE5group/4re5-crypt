// compile it with 
// g++ test.cpp 4re5-crypt.cpp -I. -o test

#include "4re5-crypt.h"
#include "stdio.h"

int main() {
  char testHash[33]; // OUTPUT_SIZE + 1
  crypt4re5::crypt(testHash, "Hello world", "SALT");
  printf(testHash);
  printf("\n");
  return 0;
}
