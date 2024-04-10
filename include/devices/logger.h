#ifndef LOGGER_H_
#define LOGGER_H_

#include <stdint.h>

void logger_init(void);
void logger_printf(uint32_t level,
  const char *fstr, ...);

#endif