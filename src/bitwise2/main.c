
#include <stdio.h>
#include <assert.h>

// 00000000 == 0
// 00000001 == 1
// 00000010 == 2
// 00000100 == 4
// ...

int main()
{

  int num = 0b011;
  assert( num == 3 );

  // shift bits leftward by 1
  // new value: 0b110 == 6
  int b = num << 1;
  assert( b == 6 );

  // shift bits leftward by 2
  // new value: 0b1100 == 12
  int c = num << 2;
  assert( c == 12 );

  // shift bits rightward by 1, one bit falls off
  // new value: 0b01 == 1
  int d = num >> 1;
  assert( d == 1 );

  // shift bits rightward by 1, all bits fall off
  // new value: 0b0 == 0
  int e = num >> 2;
  assert( e == 0 );

  int i = 0;
  int end = sizeof(int) * 8; // 4 bytes * 8 bits each = 32 bits
  int max = 2147483647;
  while ( i++ < end )
  {
    if ( i < (end - 1) )
      printf( "%d:\t%d\n", i, 1 << i );
    else if ( i == (end - 1) )
      printf( "%d:\t%d + 1 (which would overflow)\n", i, (1 << i) - 1 );
    else
      printf( "%d:\tlast bit is for the sign\n", i);
  }

  assert( max == 0b01111111111111111111111111111111 );

  return 0;
}