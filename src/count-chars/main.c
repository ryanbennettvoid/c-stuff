
#include <stdio.h>

int main( int argc, char *argv[] )
{

  int c;
  int n = 0;

  while ( ( c = getchar() ) != EOF )
  {
    putchar( c );
    ++n;
  }

  printf( "num chars: %d\n", n );

  return 0;
}