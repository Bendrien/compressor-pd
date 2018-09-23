#include "library.h"

void *compressor_new(void)
{
    t_compressor *x = (t_compressor *)pd_new(compressor_class);

    return (void *)x;
}

void compressor_bang(t_compressor *x)
{
    post("Hello world !!");
}

void compressor_setup(void)
{
    compressor_class = class_new(gensym("compressor"),
                                 (t_newmethod)compressor_new,
                                 0, sizeof(t_compressor),
                                 CLASS_DEFAULT, 0);

    class_addbang(compressor_class, compressor_bang);
}