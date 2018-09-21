
#include <stdio.h>

int add( int a, int b )
{
  return a + b;
}

int mult( int a, int b )
{
  return a * b;
}

// int          (*fn)             (int, int)
// return val   func ptr name     params

int performOperation( int a, int b, int (*fn)(int,int) )
{
  return fn( a, b );
}

int main()
{

  int a = 7, b = 5;

  int addResult = performOperation( a, b, add );
  int multResult = performOperation( a, b, mult );

  printf( "addResult: %d\n", addResult );
  printf( "multResult: %d\n", multResult );

  return 0;
}