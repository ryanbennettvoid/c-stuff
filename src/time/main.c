
#define DURATION 3

#include <stdio.h>
#include <time.h>

int main()
{

  time_t t1, t2;
  time( &t1 );

  int n = 0;

  do {
    printf( "%d\n", n++ );
    time(&t2);
  } while ( difftime( t2, t1 ) < DURATION );

  printf( "done in %d seconds\n", DURATION );

  return 0;
}