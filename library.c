#include "library.h"

t_int *compressor_tilde_perform(t_int *w)
{
    t_compressor_tilde *x = (t_compressor_tilde *)(w[1]);
    t_sample          *in =           (t_sample *)(w[2]);
    t_sample         *out =           (t_sample *)(w[3]);
    int                 n =                  (int)(w[4]);

    while (n--)
    {
        // *out++ = (*in++)*1.f;
    }

    return (w+5);
}

void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp)
{
    dsp_add(compressor_tilde_perform, 4, x,
            sp[0]->s_vec, sp[1]->s_vec, sp[0]->s_n);
}

void *compressor_tilde_new(void)
{
    t_compressor_tilde *x = (t_compressor_tilde *)pd_new(compressor_tilde_class);

    x->out = outlet_new(&x->x_obj, &s_signal);

    return (void *)x;
}

void compressor_tilde_free(t_compressor_tilde *x)
{
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
                    (t_method)compressor_tilde_dsp,
                    gensym("dsp"),
                    A_CANT,
                    0);

    CLASS_MAINSIGNALIN(compressor_tilde_class,
                       t_compressor_tilde,
                       in);
}
