
// download `Consumer_Complains.csv`:
// https://data.consumerfinance.gov/api/views/s6ew-h6mp/rows.csv?accessType=DOWNLOAD

// debugging notes:
// $ gdb
// $ file <executable>
// $ run <inputfile>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LINE_BUFFER_SIZE 32384

typedef struct Table
{
  int numCols;
  int numRows;
  struct Row *header;
} Table;

// (Row) header -> (Row) next row -> (Row) next row...

typedef struct Row
{
  char **values;
  struct Row *next;
} Row;

void makeTable( struct Table *table, FILE *file );
int getNumColumns( FILE *file );
void printTable( Table *table );

int main( int argc, char *argv[] )
{

  if ( argc != 2 )
  {
    printf( "usage: %s somefile.csv\n", argv[0] );
    exit( 1 );
  }

  char  *filepath = argv[1];

  FILE *f = fopen( filepath, "r" );

  if ( !f )
  {
    fprintf( stderr, "could not open file: %s\n", filepath );
    exit( 1 );
  }

  struct Table table;
  table.header = NULL;
  makeTable( &table, f );
  assert( table.numRows == 1671954 );
  printf( "processed %d rows by %d cols\n", table.numRows, table.numCols );

  printTable( &table );

  fclose( f );

  return 0;
}

void makeTable( struct Table *table, FILE *file )
{

  int numCols = getNumColumns( file );
  if ( numCols == 0 )
  {
    fprintf( stderr, "no columns found in file\n");
    exit( 1 );
  }
  rewind( file );
  table->numCols = numCols;

  char  buffer[LINE_BUFFER_SIZE],
        colValue[LINE_BUFFER_SIZE];

  int numLines,
      linePos,
      colIndex,
      colPos,
      dblquote
      ;

  struct Row *rowTail;

  while ( (fgets(buffer, LINE_BUFFER_SIZE, file)) != NULL )
  {

    // on each line...
    linePos = colIndex = colPos = dblquote = 0;

    Row *row = malloc( sizeof(struct Row) );
    if ( row == NULL )
    {
      fprintf( stderr, "could not allocate for row\n" );
      exit( 1 );
    }

    row->values = malloc( sizeof(char *) * numCols );
    if ( row->values == NULL )
    {
      fprintf( stderr, "could not allocate for row->values\n" );
      exit( 1 );
    }

    if ( table->header == NULL )
      table->header = row; // add as first row
    else
      rowTail->next = row; // add to tail of rows

    rowTail = row; // set tail as this row

    while ( linePos < LINE_BUFFER_SIZE-1 && colIndex < numCols )
    {
      // on each character...
      switch ( buffer[linePos] )
      {
        case '\"':
          dblquote = !dblquote;
          break;
        case '\0':
          linePos = LINE_BUFFER_SIZE; // skip to next line
          dblquote = 0;
        case ',':
          if ( !dblquote )
          {
            colValue[colPos] = '\0';
            // add column to row values
            if ( colPos > 1 )
            {
              row->values[colIndex] = malloc( sizeof(char) * (strlen(colValue) + 1) );
              if ( row->values[colIndex] == NULL )
              {
                fprintf( stderr, "could not allocate for row->values[%d]\n", colIndex );
                exit( 1 );
              }
              strcpy( row->values[colIndex], colValue );
            }
            ++colIndex;
            colPos = 0;
          }
          break;
        default:
          colValue[colPos++] = buffer[linePos];
      }
      ++linePos;
    }

    ++numLines;

  }

  table->numRows = numLines;

}

int getNumColumns( FILE *file )
{
  char buffer[LINE_BUFFER_SIZE];
  int numCommas = 0;
  int linePos = 0;
  if ( (fgets(buffer, LINE_BUFFER_SIZE, file)) != NULL )
  {
    while ( buffer[linePos] != '\0' )
    {
      if ( buffer[linePos] == ',' )
        ++numCommas;
      ++linePos;
    }
  }
  return numCommas + 1;
}

void printTable( Table *table )
{
  Row *row = table->header;
  int i;
  char *colName;
  while ( row )
  {
    for ( i = 0; i < table->numCols; i++ )
    {
      colName = table->header->values[i];
      printf( "%20s: %s\n", colName, row->values[i] );
    }
    row = row->next;
  }
}
