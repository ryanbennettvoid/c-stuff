
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compare( const void *key, const void *entry )
{
  // cast as int pointer and dereference
  int k = *(int *) key;
  int e = *(int *) entry;

  return  k < e ? -1 :
          k > e ? 1 :
          0;
}

int main()
{

  int nums[] = { 2, 3, 5, 77, 365, 900, 5000, 12777, 60000 };
  int query = 77;

  int *pResults = bsearch( 
    &query,                   // search item
    nums,                     // array of entries
    sizeof(nums)/sizeof(int), // number of items
    sizeof(nums[0]),          // size of an item
    compare                   // compare function
  );

  assert( pResults != &query );  // different objects...
  assert( *pResults == 77 );     // but same value

  return 0;
}