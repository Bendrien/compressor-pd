#include "library.h"

void *compressor_tilde_new(void)
{
    t_compressor_tilde *x = (t_compressor_tilde *)pd_new(compressor_tilde_class);

    return (void *)x;
}

void compressor_tilde_bang(t_compressor_tilde *x)
{
    post("Hello world !!");
}

void compressor_tilde_setup(void)
{
    compressor_tilde_class = class_new(gensym("compressor~"),
                                       (t_newmethod) compressor_tilde_new,
                                       0, sizeof(t_compressor_tilde),
                                       CLASS_DEFAULT, 0);

    class_addbang(compressor_tilde_class, compressor_tilde_bang);
}