
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  char name[64];
  float x;
  float y;
  float z;
  void* next;
} Asset;

int main(int argc, char** argv)
{

  if (argc < 2)
  {
    fprintf(stderr, "no arguments supplied\n");
    return 1;
  }

  char* filename = argv[1];
  FILE* fd = fopen(filename, "r");
  if (!fd)
  {
    fprintf(stderr, "could not open: %s\n", filename);
    return 1;
  }

  char name[64];
  float x, y, z;
  Asset* head = NULL;
  Asset* cursor = NULL;
  while (fscanf(fd, "%[^,],%f,%f,%f", name, &x, &y, &z) == 4)
  {

    Asset* asset = malloc(sizeof(Asset));
    memcpy(asset->name, name, strlen(name));
    asset->x = x;
    asset->y = y;
    asset->z = z;

    if (!cursor)
    {
      head = cursor = asset;
    }
    else
    {
      cursor->next = asset;
      cursor = cursor->next; 
    }

  }

  Asset* a = head;
  do
  {
    printf("%s %f %f %f", a->name, a->x, a->y, a->z);
    Asset* next = a->next;
    free(a);
    a = next;
  } while (a);

  putchar('\n');

  return 0;
}