
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void handleSignal( int sig )
{
  printf( "received signal: %d\n", sig );
  exit( 1 );
}

int main()
{

  signal( SIGINT, handleSignal );

  puts( "running..." );

  while ( 1 )
    ;

  return 0;
}