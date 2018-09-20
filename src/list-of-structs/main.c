
// word counting with linked list of structs

// usage: binary < file.txt

#define MAX_STR 1000

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
  while ( head )
  {
    printf( "%s:\t\t%d\n", head->word, head->count );
    head = head->next;
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

  char str[MAX_STR];
  int n;

  for ( n = 0; n < MAX_STR && (str[n] = tolower(getchar())) != EOF; n++ )
    ;

  struct WordInfo head;
  head.word = "PLACEHOLDER";
  head.count = 0;
  head.next = NULL;

  char *delim = " ,.";
  char *word = strtok( str, delim );

  while ( word ) {
    addWord( &head, word );
    word = strtok( NULL, delim );
  }

  printCounts( &head );

  return 0;
}
