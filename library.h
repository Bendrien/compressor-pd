#ifndef COMPRESSOR_LIBRARY_H
#define COMPRESSOR_LIBRARY_H

#include "m_pd.h"

static t_class *compressor_class;

typedef struct _compressor {
    t_object x_obj;
} t_compressor;

void *compressor_new(void);
void compressor_bang(t_compressor *x);

void compressor_setup(void);

#endif