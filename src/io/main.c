
#include <stdio.h>
#include <stdlib.h>

void printFile( char *filepath )
{

  FILE *file = fopen( filepath, "r" );

  if ( !file )
  {
    printf( "could not open file: %s\n", filepath );
    exit( 1 );
  }

  int c;

  for ( ; (c = fgetc(file)) != EOF; putchar(c) )
    ;

  fclose( file );

  puts( "\n" );

}

int main( int argc, char *argv[] )
{

  if ( argc < 2 )
  {
    puts( "file path not given\n" );
    exit( 1 );
  }

  char *filepath = argv[ 1 ];

  printf( "FILENAME_MAX: %d\n", FILENAME_MAX );
  printf( "FOPEN_MAX: %d\n\n", FOPEN_MAX );

  printFile( filepath );

  return 0;
}