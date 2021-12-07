
#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>


struct pbmObject {
  size_t width;
  size_t height;
  uint8_t* data;
};

  
struct pbmObject*
pbmObject_construct(size_t width,
                    size_t height);


void
pbmObject_free(struct pbmObject* pic);


struct pbmObject*
pbmObject_set_pixel(struct pbmObject* pic,
                    size_t xcor,
                    size_t ycor,
                    uint8_t bit);


uint8_t
pbmObject_get_pixel(const struct pbmObject* pic,
                    size_t xcor,
                    size_t ycor);

size_t
pbmObject_output(const struct pbmObject* pic, FILE* file);


