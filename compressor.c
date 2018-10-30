#include <math.h>
#include <stdlib.h>
#include "compressor.h"


t_compressor *compressor_new()
{
    t_compressor *compressor = (t_compressor *)malloc(sizeof(t_compressor));

    float threshold = -2.f;
    float ratio     =  2.f;
    float attack    =  0.f;
    float release   =  0.035f;
    float post_gain =  0.f;

    compressor_set_threshold(compressor, threshold);
    compressor_set_ratio    (compressor, ratio);
    compressor_set_attack   (compressor, attack);
    compressor_set_release  (compressor, release);
    compressor_set_post_gain(compressor, post_gain);

    compressor->envelope    = 0.f;
    compressor->comp_gain   = 1.f;
    compressor->sample_rate = 0.f;

    return compressor;
}

void compressor_free(t_compressor *self)
{
    free(self);
}

void compressor_perform(t_compressor *self, float *in_buf, float *out_buf, float *comp_out_buf, float *env_out_buf, int samples)
{
    while (samples--)
    {
        const float in = *in_buf++;

        // compute envelope via lp filter
        const float env_in   = fabsf(in);
        const float env_gain = self->envelope < env_in ?
                               self->attack_gain :
                               self->release_gain;
        self->envelope = env_in + env_gain * (self->envelope - env_in);
        *env_out_buf++ = self->envelope;

        // compute compressor gain
        const float env_dB = 20.f * log10f(self->envelope);
        const float comp_dB = env_dB >= self->threshold ?
                              self->slope * (self->threshold - env_dB) :
                              0.f;
        self->comp_gain = powf(10.f, comp_dB * 0.05f);
        *comp_out_buf++ = self->comp_gain;

        // apply gains
        *out_buf++ = in * self->post_gain * self->comp_gain;
    }
}

/*
 * Threshold [dB]
 */
void compressor_set_threshold(t_compressor *self, float threshold)
{
    self->threshold = threshold;
}

/*
 * Ratio
 */
void compressor_set_ratio(t_compressor *self, float ratio)
{
    self->slope = ratio == 0.f ? 1.f : 1.f - 1.f / ratio;
}

/*
 * Attack [s]
 */
void compressor_set_attack(t_compressor *self, float attack)
{
    self->attack = attack < 0.f ? 0.f : attack;
    self->attack_gain = self->attack == 0.f ? 0.f : expf(-1.f / (self->sample_rate * self->attack));
}

/*
 * Release [s]
 */
void compressor_set_release(t_compressor *self, float release)
{
    self->release = release < 0.f ? 0.f : release;
    self->release_gain = self->release <= 0.f ? 0.f : expf(-1.f / (self->sample_rate * self->release));
}

/*
 * Post Gain [dB]
 */
void compressor_set_post_gain(t_compressor *self, float post_gain)
{
    self->post_gain = powf(10.f, post_gain * 0.05f);
}

void compressor_set_sample_rate(t_compressor *self, float sample_rate)
{
    self->sample_rate = sample_rate;

    compressor_set_attack(self, self->attack);
    compressor_set_release(self, self->release);
}