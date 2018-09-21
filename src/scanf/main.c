
#include <stdio.h>

int main()
{

  int n = 0, sum = 0;

  printf( "enter numbers to sum them:\n" );

  // scanf returns number if items substituted
  while ( scanf( "%d", &n ) == 1 )
    printf( "sum:\t%d\n", sum += n );
 
  return 0;
}