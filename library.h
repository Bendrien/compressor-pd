#ifndef COMPRESSOR_LIBRARY_H
#define COMPRESSOR_LIBRARY_H

#include "m_pd.h"

static t_class *compressor_tilde_class;

typedef struct _compressor_tilde {
    t_object x_obj;
} t_compressor_tilde;

void *compressor_tilde_new(void);
void compressor_tilde_bang(t_compressor_tilde *x);

void compressor_tilde_setup(void);

#endif