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
    t_outlet *out2;
    t_outlet *out3;

    float threshold;
    float slope;
    float attack;
    float attack_gain;
    float release;
    float release_gain;
    float post_gain;

    float envelope;
    float comp_gain;

    float sample_rate;
} t_compressor_tilde;

t_int *compressor_tilde_perform(t_int *w);

void compressor_tilde_set_threshold(t_compressor_tilde *x, t_floatarg threshold);
void compressor_tilde_set_ratio(t_compressor_tilde *x, t_floatarg ratio);
void compressor_tilde_set_attack(t_compressor_tilde *x, t_floatarg attack);
void compressor_tilde_set_release(t_compressor_tilde *x, t_floatarg release);
void compressor_tilde_set_post_gain(t_compressor_tilde *x, t_floatarg post_gain);

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp);
void *compressor_tilde_new(void);
void compressor_tilde_free(t_compressor_tilde *x);

void compressor_tilde_setup(void);

#endif
