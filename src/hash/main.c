
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int HASH_LENGTH = 16;
const char* CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

int main(int argc, char** argv)
{

  char* filename = argv[1];
  if (!filename)
  {
    fprintf(stderr, "filename is missing\n");
    return 1;
  }

  FILE* fd = fopen(filename, "r");
  if (!fd)
  {
    fprintf(stderr, "could not open file: %s\n", filename);
    return 1;
  }

  // fill the hash with placeholder chars
  char* hash = malloc(sizeof(char) * (HASH_LENGTH + 1));
  for (int i = 0; i < HASH_LENGTH; i++)
  {
    hash[i] = '0';
  }
  hash[HASH_LENGTH] = '\0';

  int charsetLength = strlen(CHARSET);

  // generate hash
  int count = 0;
  char c;
  int hashCharIndex;
  char charsetIndex;
  while ((c = fgetc(fd)) != EOF)
  {
    hashCharIndex = count++ % HASH_LENGTH;
    charsetIndex = ((hash[hashCharIndex] << 5) + c) % charsetLength;
    hash[hashCharIndex] = CHARSET[charsetIndex];
  }

  printf("%s\n", hash);

  free(hash);

  return 0;
}