
#include <stdio.h>

typedef struct point {
  int x;
  int y;
} point;

// address is pointer
void updatePoint( point *p ) {
  p->x++;
  p->y++;
}

int main()
{

  // without typedef, we'd use
  // `struct point` rather than `point`

  // in C++, you can just use `point`

  point p;
  p.x = 3;
  p.y = 7;

  // pass "address of p"
  updatePoint( &p );

  printf( "%d, %d\n", p.x, p.y );

  return 0;
}