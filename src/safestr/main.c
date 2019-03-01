
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/*

  A "safe string" implementation to
  prevent overflow

*/

// ---

static int ALOC_COUNT = 0;
static void* jmalloc(size_t size) {
  ALOC_COUNT++;
  return malloc(size);
}
static void jfree(void* p) {
  ALOC_COUNT--;
  free(p);
}

// ---

typedef struct {
  char* src;
  int size;
} SafeString;

SafeString* makeSafeString(char* str, int maxSize)
{
  SafeString* safe = jmalloc(sizeof(SafeString));

  int inStrSize = strlen(str);
  if (inStrSize > maxSize)
  {
    fprintf(stderr, "WARNING: input string too big, it will be truncated\n");
  }
  int targetStrSize = inStrSize < maxSize ? inStrSize : maxSize;
  int allocSize = targetStrSize + 1;

  safe->src = jmalloc(allocSize);
  if (!safe->src)
  {
    fprintf(stderr, "FATAL: could not allocate memory for string\n");
    jfree(safe);
    return NULL;
  }
  safe->size = allocSize;
  memcpy(safe->src, str, targetStrSize);
  safe->src[allocSize-1] = '\0';

  return safe;
}

void destroySafeString(SafeString* safe)
{
  if (safe)
  {
    if (safe->src)
    {
      jfree(safe->src);
    }
    jfree(safe);
  }
}

int main()
{

  {
    char* longstr = "this is a really long string that exceeds the allowed size"; // 58
    SafeString *safeString = makeSafeString(longstr, 16);
    if (safeString)
    {
      printf("original: %s^\n", longstr);
      printf("after:    %s^\n", safeString->src);
      printf("after length: %d\n", safeString->size);
      destroySafeString(safeString);
    }
  }

  {
    char* longstr = "this string does not exceed allowed size"; // 40
    SafeString *safeString = makeSafeString(longstr, 64);
    if (safeString)
    {
      printf("original: %s^\n", longstr);
      printf("after:    %s^\n", safeString->src);
      printf("after length: %d\n", safeString->size);
      destroySafeString(safeString);
    }
  }

  assert(ALOC_COUNT == 0);

  return 0;
}