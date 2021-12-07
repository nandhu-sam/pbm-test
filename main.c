
#include <stdio.h>
#include "pbmtest.h"
#include <stdlib.h>


int main() {
  size_t width = 1500, height = 500;
  
  struct pbmObject* pic = pbmObject_construct(width, height);

  for(size_t i=0; i<width; ++i) {
    for(size_t j=0; j<height; ++j) {
      pbmObject_set_pixel(pic, i, j, (random()&0x11)?1:0);
    }
  }


  FILE* outfile = fopen("banner3.pbm", "w");
  if(outfile == NULL) {
    fprintf(stderr, "error opening file\n");
    pbmObject_free(pic);
    return -1;
  }


  pbmObject_output(pic, outfile);
  fflush(outfile);
  pbmObject_free(pic);
  fclose(outfile);

  return 0;

}

