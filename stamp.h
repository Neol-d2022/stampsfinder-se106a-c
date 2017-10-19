#ifndef _STAMP_H_LOADED
#define _STAMP_H_LOADED

#include "vector.h"

int SFind(const Vector_t *stamps, Vector_t *out, unsigned int targetValue);
void SDestroyV(void *data, void *_);

#endif
