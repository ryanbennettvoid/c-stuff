
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

  Hashing algorithm that reads 
  chunks of CHUNK_LENGTH spaced 
  out by exponentially increasing 
  gaps with max length MAX_SKIP, 
  the hash limited to the characters
  of CHARSET.

  Optimized for low collision of 
  small files and speed for larger 
  files.

*/

// size of hash
const int HASH_LENGTH = 16;
// characters in charset
const char* CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
// number of characters to read at a time
const int CHUNK_LENGTH = 1024 * 1024;
// max size of skip
const int MAX_SKIP = 1024 * 1024 * 512;

int max(int a, int b) {
  return a > b ? a : b;
}

int main(int argc, char** argv)
{

  char* filename = argv[1];
  if (!filename)
  {
    fprintf(stderr, "filename is missing\n");
    return 1;
  }

  FILE* fd = fopen(filename, "rb");
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
  int c;
  int hashCharIndex;
  int charsetIndex;
  fpos_t pos;
  int newPos;
  int skip = 2;
  while ((c = fgetc(fd)) != EOF)
  {
    // update hash
    hashCharIndex = count++ % HASH_LENGTH;
    charsetIndex = ((hash[hashCharIndex] << 5) + c) % charsetLength;
    hash[hashCharIndex] = CHARSET[charsetIndex];
    // skip some characters
    if (count % CHUNK_LENGTH == 0)
    {
      fgetpos(fd, &pos);
      newPos = pos + skip;
      fseek(fd, newPos, SEEK_SET);
      if (skip < MAX_SKIP)
      {
        skip *= 2;
      }
    }
  }

  printf("%s\n", hash);

  free(hash);

  return 0;
}