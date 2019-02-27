
#include <stdio.h>
#include <assert.h>

// ref: http://yann.lecun.com/exdb/mnist/

int main()
{
  char* filename = "./src/recog/t10k-images.idx3-ubyte";
  FILE* fd = fopen(filename, "rb");

  if (!fd)
  {
    fprintf(stderr, "could not open file: %s\n", filename);
    return 1;
  }

  int pos, 
      end, 
      magic,
      numImages,
      numRows,
      numColumns,
      pixelPos
      ;

  int c;

  fseek(fd, 0, SEEK_END);
  end = ftell(fd);
  rewind(fd);

  int* pixels;

  while ((pos = ftell(fd)) < end)
  {
    c = fgetc(fd);
    if (pos < 4) {
      magic += (c << ((3-pos) * 8));
    } else if (pos < 8) {
      numImages += (c << ((3-pos) * 8));
    } else if (pos < 12) {
      numRows += (c << ((3-pos) * 8));
    } else if (pos < 16) {
      numColumns += (c << ((3-pos) * 8));
    } else {
      if (pos == 16) {
        assert(magic == 2051);
        assert(numImages == 10000);
        assert(numRows == 28);
        assert(numColumns == 28);
      }
      printf("%4d,", c);
      if (pixelPos % numColumns == 0) {
        // next row
        putchar('\n');
      }
      if (pixelPos % 784 == 0) {
        // next image
        putchar('\n');
      }
      pixelPos++;
    }
  }

  fclose(fd);
  return 0;

}