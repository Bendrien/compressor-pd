#ifndef COMPRESSOR_COMPRESSOR_H
#define COMPRESSOR_COMPRESSOR_H

typedef struct t_compressor
{
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
} t_compressor;

t_compressor *compressor_new();
void compressor_free(t_compressor *self);

void compressor_perform(t_compressor *self, float *in, float *out, float *comp_out, float *env_out, int samples);

void compressor_set_threshold(t_compressor *self, float threshold);
void compressor_set_ratio(t_compressor *self, float ratio);
void compressor_set_attack(t_compressor *self, float attack);
void compressor_set_release(t_compressor *self, float release);
void compressor_set_post_gain(t_compressor *self, float post_gain);
void compressor_set_sample_rate(t_compressor *self, float sample_rate);


#endif //COMPRESSOR_COMPRESSOR_H
