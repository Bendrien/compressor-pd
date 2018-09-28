#include <math.h>
#include "library.h"

t_int *compressor_tilde_perform(t_int *w)
{
    t_compressor_tilde *self = (t_compressor_tilde *)(w[1]);
    t_sample          *inBuf =           (t_sample *)(w[2]);
    t_sample         *outBuf =           (t_sample *)(w[3]);
    int                    n =                  (int)(w[4]);

    while (n--)
    {
        const float in = *inBuf++;

        // compute envelope via lp filter
        const float env_in   = fabsf(in);
        const float env_gain = self->envelope < env_in ?
                               self->attack_gain :
                               self->release_gain;
        self->envelope = env_in + env_gain * (self->envelope - env_in);

        // compute compressor gain
        const float env_dB = 20.f * log10f(self->envelope);
        const float comp_dB = env_dB >= self->threshold ?
                              self->slope * (self->threshold - env_dB) :
                              0.f;
        const float comp_gain = powf(10.f, comp_dB * 0.05f);

        // apply gains
        *outBuf++ = in * self->post_gain * comp_gain;
    }

    return (w+5);
}

/*
 * Threshold [dB]
 */
void compressor_tilde_set_threshold(t_compressor_tilde *x, t_floatarg threshold)
{
    x->threshold = threshold;
}

/*
 * Ratio
 */
void compressor_tilde_set_ratio(t_compressor_tilde *x, t_floatarg ratio)
{
    x->slope = ratio == 0.f ? 1.f : 1.f - 1.f / ratio;
}

/*
 * Attack [s]
 */
void compressor_tilde_set_attack(t_compressor_tilde *x, t_floatarg attack)
{
    x->attack = attack < 0.f ? 0.f : attack;
    x->attack_gain = x->attack == 0.f ? 0.f : expf(-1.f / (x->sample_rate * x->attack));
}

/*
 * Release [s]
 */
void compressor_tilde_set_release(t_compressor_tilde *x, t_floatarg release)
{
    x->release = release < 0.f ? 0.f : release;
    x->release_gain = x->release <= 0.f ? 0.f : expf(-1.f / (x->sample_rate * x->release));
}

/*
 * Post Gain [dB]
 */
void compressor_tilde_set_post_gain(t_compressor_tilde *x, t_floatarg post_gain)
{
    x->post_gain = powf(10.f, post_gain * 0.05f);
}

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp)
{
    dsp_add(compressor_tilde_perform, 4, x,
            sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);

    x->sample_rate = sp[0]->s_sr;

    compressor_tilde_set_attack(x, x->attack);
    compressor_tilde_set_release(x, x->release);
}

void *compressor_tilde_new(void)
{
    t_compressor_tilde *x = (t_compressor_tilde *)pd_new(compressor_tilde_class);

    compressor_tilde_set_threshold(x, -2.f);    // threshold [dB]
    compressor_tilde_set_ratio    (x,  2.f);    // ratio
    compressor_tilde_set_attack   (x,  0.f);    // attack    [s]
    compressor_tilde_set_release  (x,  0.035f); // release   [s]
    compressor_tilde_set_post_gain(x,  0.f);    // gain      [dB]

    x->envelope    = 0.f;
    x->sample_rate = 0.f;

    x->in2 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("threshold"));
    x->in3 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("ratio"));
    x->in4 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("attack"));
    x->in5 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("release"));
    x->in6 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("gain"));

    x->out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void compressor_tilde_free(t_compressor_tilde *x)
{
    inlet_free(x->in2);
    inlet_free(x->in3);
    inlet_free(x->in4);
    inlet_free(x->in5);
    inlet_free(x->in6);

    outlet_free(x->out);
}

void compressor_tilde_setup(void)
{
    compressor_tilde_class = class_new(gensym("compressor~"),
                                       (t_newmethod) compressor_tilde_new,
                                       (t_method) compressor_tilde_free,
                                       sizeof(t_compressor_tilde),
                                       CLASS_DEFAULT,
                                       0);

    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_threshold,
                    gensym("threshold"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_ratio,
                    gensym("ratio"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_attack,
                    gensym("attack"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_release,
                    gensym("release"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_post_gain,
                    gensym("gain"),
                    A_DEFFLOAT,
                    0);

    class_addmethod(compressor_tilde_class,
                    (t_method)compressor_tilde_dsp,
                    gensym("dsp"),
                    A_CANT,
                    0);

    CLASS_MAINSIGNALIN(compressor_tilde_class,
                       t_compressor_tilde,
                       in);
}
