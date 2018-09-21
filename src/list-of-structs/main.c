
// word counting with linked list of structs

// usage: binary < file.txt

#define MAX_STR 50

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct WordInfo
{
  char *word;
  int count;
  struct WordInfo *next;
};

void printCounts( struct WordInfo *head )
{
  // poor man's sorting (n * max iterations)
  struct WordInfo *oldHead = head;
  // find max count
  int max = 0;
  while ( head )
  {
    max = head->count > max ? head->count : max;
    head = head->next;
  }
  // decrement max and print words where count == max
  while ( max > 0 )
  {
    head = oldHead;
    while ( head )
    {
      if ( head->count == max )
      {
        printf( "%20s:\t%d\n", head->word, head->count );
      }
      head = head->next;
    }
    --max;
  }
}

void addWord( struct WordInfo *head, char *word )
{

  struct WordInfo *cursor;

  do {
    if ( strcmp(head->word, word) == 0 ) {
      head->count++;
      return;
    }
    cursor = head;
    head = head->next;
  } while ( head );

  cursor->next = malloc( sizeof(struct WordInfo) );
  cursor->next->word = malloc( sizeof(char) * (strlen(word) + 1) );
  strcpy( cursor->next->word, word );
  cursor->next->count++;
  cursor->next->next = NULL;
}

int main()
{

  // placeholder for start of linked list
  struct WordInfo head;
  head.word = "pkwh9xXW9E";
  head.count = -1;
  head.next = NULL;

  char word[MAX_STR];
  int n = 0;

  // characters from input are added to `word`
  // use MAX_STR-1 in case the last char needs to be '\0'
  while ( n < MAX_STR-1 && (word[n] = tolower(getchar())) != EOF )
  {
    switch ( word[n] )
    {
      case ' ':
      case ',':
      case '.':
      case ';':
      case ':':
      case '\t':
      case '\n':
      case '\r':
        word[n] = '\0';
        // word must have at least 1 char + '\0'
        if ( strlen(word) > 1 )
          addWord( &head, word );
        n = 0;
        continue;
    }
    n++;
  }

  printCounts( &head );

  return 0;
}
