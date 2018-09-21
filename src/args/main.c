
#include <stdio.h>

int main( int argc, char *argv[] )
{

  printf( "arg count: %d\n", argc );

  while ( --argc >= 0 ) {
    char *v = argv[argc];
    printf( "argv[%d]: %s\n", argc, v );
  }

  return 0;
}