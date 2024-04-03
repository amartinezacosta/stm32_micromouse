#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

typedef struct
{
  uint8_t * buffer;
  uint32_t length;
  volatile uint32_t head;
  volatile uint32_t tail;
}ringbuffer_t;

void ringbuffer_init(ringbuffer_t * const self, 
  uint8_t *buffer,
  uint32_t length);
uint32_t ringbuffer_write(ringbuffer_t * const self, uint8_t c);
uint32_t ringbuffer_read(ringbuffer_t * const self, uint8_t *c);
uint32_t ringbuffer_space(ringbuffer_t * const self);

#endif