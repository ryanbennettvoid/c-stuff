
// Most functions in the standard
// library do not allocate memory,
// but instead take a pointer as
// an argument and sets the value
// at the provided memory address.

// Passing a double pointer as an
// argument is useful when you need
// to modify the address of the
// pointer itself, which you would 
// need to do if you wanted to
// allocate memory for the pointer
// inside a function.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void makeStr( char **p )
{
  char *s = "foo";
  // set the value of the thing p is 
  // pointing to (another pointer) to 
  // the address that malloc returns
  *p = malloc( sizeof(char) * (strlen(s) + 1) );
  strcpy( *p, s );
}

int main()
{
  char *str;
  makeStr( &str );
  assert( strcmp( str, "foo" ) == 0 );
  printf( "%s\n", str );
  return 0;
}