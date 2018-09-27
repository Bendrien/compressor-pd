#ifndef COMPRESSOR_LIBRARY_H
#define COMPRESSOR_LIBRARY_H

#include "m_pd.h"

static t_class *compressor_tilde_class;

typedef struct _compressor_tilde {
    t_object x_obj;

    t_float in;
    t_inlet *in2;
    t_inlet *in3;
    t_inlet *in4;
    t_inlet *in5;
    t_inlet *in6;
    t_outlet *out;

    float threashold;
    float ratio;
    float attack;
    float release;
    float gain;
} t_compressor_tilde;

t_int *compressor_tilde_perform(t_int *w);
void compressor_tilde_set_in2(t_compressor_tilde *x, t_floatarg in2);
void compressor_tilde_set_in3(t_compressor_tilde *x, t_floatarg in3);
void compressor_tilde_set_in4(t_compressor_tilde *x, t_floatarg in4);
void compressor_tilde_set_in5(t_compressor_tilde *x, t_floatarg in5);
void compressor_tilde_set_in6(t_compressor_tilde *x, t_floatarg in6);

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp);
void *compressor_tilde_new(void);
void compressor_tilde_free(t_compressor_tilde *x);

void compressor_tilde_setup(void);

#endif
