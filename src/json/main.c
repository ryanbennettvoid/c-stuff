
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

static int ALOC_COUNT = 0;
static void* jmalloc(size_t size) {
  ALOC_COUNT++;
  return malloc(size);
}
static void jfree(void* p) {
  ALOC_COUNT--;
  free(p);
}

typedef enum
{
  INVALID = 0,
  OBJECT,
  ARRAY,
  STRING,
  NUMBER,
  NULLTHING
} TYPE;

typedef struct Property
{
  char* key;
  struct JSONObject* value;
} Property;

typedef struct JSONObject
{
  char* source;
  TYPE type;
  struct Property* objectProperties; // object
  int numObjectProperties;
  struct JSONObject* arrayObjects;   // array
  int numArrayObjects;
  char* stringValue;          // string
  float* numberValue;         // number
} JSONObject;

void populate(JSONObject* root)
{
  if (!root->source)
  {
    fprintf(stderr, "json object has not source\n");
    return;
  }
  char* source = root->source;
  int count = 0;
  bool quotes = false;
  char c;
  while ((c = *(source++)) != '\0')
  {
    putchar(c);
    if (count == 0)
    {
      switch (c)
      {
        case '{':
          root->type = OBJECT;
          break;
        case '[':
          root->type = ARRAY;
          break;
        default:
          root->type = INVALID;
      }
    }
    else
    {
      switch (root->type)
      {
        case OBJECT:
          break;
        case ARRAY:
          break;
        case STRING:
          break;
        case NUMBER:
          break;
        case NULLTHING:
          break;
        default:
          break;
      }
    }
    count++;
  }
}

void cleanup(JSONObject* root)
{
  while (root)
  {
    jfree(root->source);
    root->source = NULL;
    switch (root->type)
    {
      case OBJECT:
        for (int i = 0; i < root->numObjectProperties; i++)
        {
          // Property* property = root->objectProperties[i];
        }
        break;
      case ARRAY:
        break;
      case STRING:
        break;
      default:
        break;
    }
    jfree(root);
    root = NULL;
  }
}

JSONObject* fromFile(char* filename)
{
  // read file to string
  FILE* fd = fopen(filename, "r");
  if (!fd)
  {
    fprintf(stderr, "could not open file: %s\n", filename);
    return NULL;
  }
  fseek(fd, 0, SEEK_END);
  int len = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  char* buf = jmalloc(sizeof(char) * len);
  if (!buf)
  {
    fprintf(stderr, "could not allocate buffer of size: %d\n", len);
    return NULL;
  } 
  fread(buf, sizeof(char), len, fd);
  // make json object
  JSONObject* jo = jmalloc(sizeof(JSONObject));
  jo->source = buf;
  populate(jo);
  return jo;
}

int main()
{

  JSONObject* jsonObject = fromFile("./src/json/test.json");
  assert(jsonObject);
  assert(jsonObject->source);
  assert(jsonObject->type == OBJECT);
  assert(jsonObject->numObjectProperties == 1);
  assert(strcmp(jsonObject->objectProperties[0].key, "anObject") == 0);

  cleanup(jsonObject);
  assert(ALOC_COUNT == 0);

  putchar('\n');

  return 0;
}