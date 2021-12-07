
#include "pbmtest.h"

const char MAGIC[] = "P4";

static uint8_t get_bit(uint8_t byte, uint8_t pos) {
  pos &= 0x7;
  return (byte & (1 << pos)) >> pos;
}


static uint8_t set_bit(uint8_t byte, uint8_t pos, uint8_t bit) {
  pos &= 0x7;
  bit = (uint8_t)(bit != 0);
  return (byte & (~(1 << pos))) | (bit << pos);
}


struct pbmObject* pbmObject_set_pixel(struct pbmObject* pic,
                                      size_t xcor,
                                      size_t ycor,
                                      uint8_t bit) {

  bit = (uint8_t)(bit!=0);
  
  if(pic == NULL         ||
     xcor >= pic->width  ||
     ycor >= pic->height ||
     pic->data == NULL) {
    
    return NULL;
  }
  
  size_t row_width = ((pic->width)+7)/8;
  size_t byte_i  = xcor >> 0x3;
  size_t bit_i   = xcor & 0x7;
  size_t index   = ycor * row_width + byte_i;
  pic->data[index] = set_bit(pic->data[index], 7-bit_i, bit);
  return pic;
}


  
uint8_t pbmObject_get_pixel(const struct pbmObject* pic,
                            size_t xcor,
                            size_t ycor) {

  if(pic == NULL         ||
     xcor >= pic->width  ||
     ycor >= pic->height ||
     pic->data == NULL) {
    
    return 255;
  }
  
  size_t row_width = ((pic->width)+7)/8;
  size_t byte_i = xcor >> 0x3;
  size_t bit_i  = xcor & 0x7;
  return get_bit(pic->data[ycor*row_width + byte_i], 7-bit_i);
}


struct pbmObject* pbmObject_construct(size_t width,
                                      size_t height) {
  
  if(!width || !height) {
    return NULL;
  }
  
  struct pbmObject* pic = calloc(sizeof(struct pbmObject), 1);
  if(pic == NULL) {
    return NULL;
  }

  pic->width = width;
  pic->height = height;
  size_t row_width = (width+7)/8;
  pic->data = calloc(height, sizeof(uint8_t)*row_width);
  
  if(pic->data == NULL) {
    free(pic);
    return NULL;
  }

  return pic;
}


void pbmObject_free(struct pbmObject* pic) {

  if(pic != NULL) {
    if(pic->data != NULL) {
      free(pic->data);
    }
    free(pic);
  }
  
  return;
}

size_t pbmObject_output(const struct pbmObject* pic, FILE* file) {
  
  fwrite(MAGIC, sizeof(const char), 2, file);
  fprintf(file, "\n%lu %lu\n", pic->width, pic->height);
  size_t row_width = (pic->width+7)/8;
  return fwrite(pic->data,
                sizeof(char)*row_width,
                pic->height,
                file);

}


