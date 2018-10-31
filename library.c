#include <math.h>
#include "library.h"

t_int *compressor_tilde_perform(t_int *w)
{
    t_compressor_tilde *self = (t_compressor_tilde *)(w[1]);
    t_sample          *inBuf =           (t_sample *)(w[2]);
    t_sample         *outBuf =           (t_sample *)(w[3]);
    t_sample     *compOutBuf =           (t_sample *)(w[4]);
    t_sample      *envOutBuf =           (t_sample *)(w[5]);
    int                    n =                  (int)(w[6]);

    compressor_perform(self->compressor, inBuf, outBuf, compOutBuf, envOutBuf, n);

    return (w+7);
}

/*
 * Threshold [dB]
 */
void compressor_tilde_set_threshold(t_compressor_tilde *x, t_floatarg threshold)
{
    compressor_set_threshold(x->compressor, threshold);
}

/*
 * Ratio
 */
void compressor_tilde_set_ratio(t_compressor_tilde *x, t_floatarg ratio)
{
    compressor_set_ratio(x->compressor, ratio);
}

/*
 * Attack [s]
 */
void compressor_tilde_set_attack(t_compressor_tilde *x, t_floatarg attack)
{
    compressor_set_attack(x->compressor, attack);
}

/*
 * Release [s]
 */
void compressor_tilde_set_release(t_compressor_tilde *x, t_floatarg release)
{
    compressor_set_release(x->compressor, release);
}

/*
 * Post Gain [dB]
 */
void compressor_tilde_set_post_gain(t_compressor_tilde *x, t_floatarg post_gain)
{
    compressor_set_post_gain(x->compressor, post_gain);
}

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp)
{
    dsp_add(compressor_tilde_perform, 6, x, sp[0]->s_vec,
            sp[1]->s_vec, sp[2]->s_vec, sp[3]->s_vec, sp[0]->s_n);

    compressor_set_sample_rate(x->compressor, sp[0]->s_sr);
}

void *compressor_tilde_new(int argc, t_atom *argv)
{
    t_compressor *compressor = compressor_new();

    switch (argc)
    {
        case 5 : compressor_set_post_gain(compressor, atom_getfloat(argv + 4));
        case 4 : compressor_set_release(compressor, atom_getfloat(argv + 3));
        case 3 : compressor_set_attack(compressor, atom_getfloat(argv + 2));
        case 2 : compressor_set_ratio(compressor, atom_getfloat(argv + 1));
        case 1 : compressor_set_threshold(compressor, atom_getfloat(argv));
        default: break;
    }

    t_compressor_tilde *x = (t_compressor_tilde *)pd_new(compressor_tilde_class);
    x->compressor = compressor;

    x->in2 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("threshold"));
    x->in3 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("ratio"));
    x->in4 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("attack"));
    x->in5 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("release"));
    x->in6 = inlet_new(&x->x_obj, &x->x_obj.ob_pd, &s_float, gensym("gain"));

    x->out  = outlet_new(&x->x_obj, &s_signal);
    x->out2 = outlet_new(&x->x_obj, &s_signal);
    x->out3 = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void compressor_tilde_free(t_compressor_tilde *x)
{
    compressor_free(x->compressor);

    inlet_free(x->in2);
    inlet_free(x->in3);
    inlet_free(x->in4);
    inlet_free(x->in5);
    inlet_free(x->in6);

    outlet_free(x->out);
    outlet_free(x->out2);
    outlet_free(x->out3);
}

void compressor_tilde_setup(void)
{
    compressor_tilde_class = class_new(gensym("compressor~"),
                                       (t_newmethod) compressor_tilde_new,
                                       (t_method) compressor_tilde_free,
                                       sizeof(t_compressor_tilde),
                                       CLASS_DEFAULT,
                                       A_GIMME,
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

    class_sethelpsymbol(compressor_tilde_class, gensym("compressor~"));
}
