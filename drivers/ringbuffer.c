#include "drivers/ringbuffer.h"

void ringbuffer_init(ringbuffer_t * const self, 
  uint8_t *buffer,
  uint32_t length)
{
  self->buffer = buffer;
  self->head = 0;
  self->tail = 0;
  self->length = length;
}

uint32_t ringbuffer_write(ringbuffer_t * const self, uint8_t c)
{
  uint32_t head = self->head + 1;
  if(head == self->length)
  {
    head = 0;
  }

  if(head != self->tail)
  {
    self->buffer[self->head] = c;
    self->head = head;
    return 1;
  }
  else
  {
    return 0;
  }
}

uint32_t ringbuffer_read(ringbuffer_t * const self, uint8_t *c)
{
  uint32_t tail = self->tail;
  if(self->head != tail)
  {
    *c = self->buffer[tail];
    tail++;
    if(tail == self->length)
    {
      tail = 0;
    }
    self->tail = tail;
    return 1;
  }
  else
  {
    return 0;
  }
}

uint32_t ringbuffer_space(ringbuffer_t * const self)
{
  uint32_t head = self->head;
  uint32_t tail = self->tail;

  if(head == tail)
  {
    return (uint32_t)(self->length - 1);
  }
  else if(head < tail)
  {
    return (uint32_t)(tail - head - 1);
  }
  else
  {
    return (uint32_t)(self->length + tail - head - 1);
  }
}