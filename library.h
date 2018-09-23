#ifndef COMPRESSOR_LIBRARY_H
#define COMPRESSOR_LIBRARY_H

#include "m_pd.h"

static t_class *compressor_tilde_class;

typedef struct _compressor_tilde {
    t_object x_obj;

    t_float in;
    t_outlet *out;
} t_compressor_tilde;

t_int *compressor_tilde_perform(t_int *w);

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp);
void *compressor_tilde_new(void);
void compressor_tilde_free(t_compressor_tilde *x);

void compressor_tilde_setup(void);

#endif
