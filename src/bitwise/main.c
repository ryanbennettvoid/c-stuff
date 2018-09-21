
#include <stdio.h>
#include <assert.h>

enum PERM {
  READ    = 0b0001, // 1
  WRITE   = 0b0010, // 2
  EXECUTE = 0b0100  // 4
};

void addPermission( int *perm, int permToAdd )
{
 *perm = *perm | permToAdd;
}

void removePermission( int *perm, int permToRemove )
{
  *perm = *perm ^ permToRemove;
}

int main()
{

  printf( "READ: \t\t%d\n", READ );
  printf( "WRITE: \t\t%d\n", WRITE );
  printf( "EXECUTE: \t%d\n", EXECUTE );

  int permissions = 0;

  assert( !(permissions & READ) );
  addPermission( &permissions, READ );
  printf( "permissions after add READ (%d): \t%d\n", READ, permissions );
  assert( permissions & READ );

  assert( !(permissions & EXECUTE) );
  addPermission( &permissions, EXECUTE );
  printf( "permissions after add EXECUTE (%d): \t%d\n", EXECUTE, permissions );
  assert( permissions & EXECUTE );

  assert( !(permissions & WRITE) );
  addPermission( &permissions, WRITE );
  printf( "permissions after add WRITE (%d): \t%d\n", WRITE, permissions );
  assert( permissions & WRITE );

  assert( permissions == READ + WRITE + EXECUTE );

  // ---

  assert( permissions & EXECUTE );
  removePermission( &permissions, EXECUTE );
  printf( "permissions after remove EXECUTE (%d): \t%d\n", EXECUTE, permissions );
  assert( !(permissions & EXECUTE) );

  assert( permissions & READ );
  removePermission( &permissions, READ );
  printf( "permissions after remove READ (%d): \t%d\n", READ, permissions );
  assert( !(permissions & READ) );

  assert( permissions & WRITE );
  removePermission( &permissions, WRITE );
  printf( "permissions after remove WRITE (%d): \t%d\n", WRITE, permissions );
  assert( !(permissions & WRITE) );

  assert( permissions == 0 );

  return 0;
}