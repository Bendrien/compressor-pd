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
        const float out;
        *outBuf++ = out;
    }

    return (w+5);
}

void compressor_tilde_set_in2(t_compressor_tilde *x, t_floatarg in2)
{
    x->threashold = in2;
}

void compressor_tilde_set_in3(t_compressor_tilde *x, t_floatarg in3)
{
    x->ratio = in3;
}

void compressor_tilde_set_in4(t_compressor_tilde *x, t_floatarg in4)
{
    x->attack = in4;
}

void compressor_tilde_set_in5(t_compressor_tilde *x, t_floatarg in5)
{
    x->release = in5;
}

void compressor_tilde_set_in6(t_compressor_tilde *x, t_floatarg in6)
{
    x->gain = in6;
}

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp)
{
    dsp_add(compressor_tilde_perform, 4, x,
            sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void *compressor_tilde_new(void)
{
    t_compressor_tilde *x = (t_compressor_tilde *)pd_new(compressor_tilde_class);

    x->threashold = 1.f;
    x->ratio      = 1.f;
    x->attack     = 1.f;
    x->release    = 1.f;
    x->gain       = 1.f;

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
                    (t_method) compressor_tilde_set_in2,
                    gensym("threshold"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_in3,
                    gensym("ratio"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_in4,
                    gensym("attack"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_in5,
                    gensym("release"),
                    A_DEFFLOAT,
                    0);
    class_addmethod(compressor_tilde_class,
                    (t_method) compressor_tilde_set_in6,
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
