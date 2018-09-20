
#include <stdio.h>
#include <stdlib.h>

void custom_strcpy( char *dst, char *src )
{

  // copy src chars to dest char by
  // assigning and increment pointers
  // until null termination '\0'

  while ( (*dst++ = *src++) != '\0' )
    ;

}

int custom_strlen( char *a )
{

  int n;

  // can access characters like an array

  // for ( n = 0; a[n] != '\0'; n++ )
  //   ;

  // ... or dereference ( pointer address + n )
  for ( n = 0; *(a+n) != '\0'; n++ )
    ;

  return n;

}

int main()
{

  char *str = "this is a string";

  // new string requires allocating memory via malloc
  // add 1 to strlen for trailing '\0'
  char *cpy = malloc( sizeof(char) * (custom_strlen(str) + 1) );
  custom_strcpy( cpy, str );

  printf( "%s\n", cpy );

  return 0;
}