
// word counting with linked list of structs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *bigString = "this is a really big string and this string is a cool one";

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
    printf( "%s\t%d\n", head->word, head->count );
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

  struct WordInfo head;
  head.word = "PLACEHOLDER";
  head.count = 0;
  head.next = NULL;

  // TODO: turn string of words into array
  // of words and add them

  addWord( &head, "foo" );
  addWord( &head, "foo" );
  addWord( &head, "foo" );
  addWord( &head, "cake" );
  addWord( &head, "tiger" );
  addWord( &head, "foo" );
  addWord( &head, "cake" );

  printCounts( &head );

  return 0;
}
