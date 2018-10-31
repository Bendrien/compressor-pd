#ifndef COMPRESSOR_COMPRESSOR_H
#define COMPRESSOR_COMPRESSOR_H

////////////////////////////////////////////////////////////
/// \brief Structure holding a compressors state
////////////////////////////////////////////////////////////
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

////////////////////////////////////////////////////////////
/// \brief Instanciate new compressor instance
///
/// This functions instanciate a new compressor instance.
///
/// \returns A pointer to the new instance
///
////////////////////////////////////////////////////////////
t_compressor *compressor_new();

////////////////////////////////////////////////////////////
/// \brief Free a compressor instance
///
/// This functions frees the memory acquired by a compressor
/// instance.
///
/// \param self      Pointer to a compressor instance
///
////////////////////////////////////////////////////////////
void compressor_free(t_compressor *self);

////////////////////////////////////////////////////////////
/// \brief Main DSP function
///
/// This functions does the main DSP computations.
///
/// \param w Pointer to a compressor instance and input/output arrays
///
////////////////////////////////////////////////////////////
void compressor_perform(t_compressor *self, float *in, float *out, float *comp_out, float *env_out, int samples);

////////////////////////////////////////////////////////////
/// \brief Threshold setter
///
/// This functions sets the threshold of the compressor.
///
/// \param self      Pointer to a compressor instance
/// \param threshold New value for the threshold
///
////////////////////////////////////////////////////////////
void compressor_set_threshold(t_compressor *self, float threshold);

////////////////////////////////////////////////////////////
/// \brief Ratio setter
///
/// This functions sets the ratio of the compressor.
///
/// \param self  Pointer to a compressor instance
/// \param ratio New value for the ratio
///
////////////////////////////////////////////////////////////
void compressor_set_ratio(t_compressor *self, float ratio);

////////////////////////////////////////////////////////////
/// \brief Attack setter
///
/// This functions sets the attack of the compressor.
///
/// \param self   Pointer to a compressor instance
/// \param attack New value for the attack
///
////////////////////////////////////////////////////////////
void compressor_set_attack(t_compressor *self, float attack);

////////////////////////////////////////////////////////////
/// \brief Release setter
///
/// This functions sets the release of the compressor.
///
/// \param self    Pointer to a compressor instance
/// \param release New value for the release
///
////////////////////////////////////////////////////////////
void compressor_set_release(t_compressor *self, float release);

////////////////////////////////////////////////////////////
/// \brief Post gain setter
///
/// This functions sets the post gain of the compressor.
///
/// \param self      Pointer to a compressor instance
/// \param post_gain New value for the post gain
///
////////////////////////////////////////////////////////////
void compressor_set_post_gain(t_compressor *self, float post_gain);

////////////////////////////////////////////////////////////
/// \brief Samplerate setter
///
/// This functions sets the samplerate of the compressor.
///
/// \param self        Pointer to a compressor instance
/// \param sample_rate New value for the samplerate
///
////////////////////////////////////////////////////////////
void compressor_set_sample_rate(t_compressor *self, float sample_rate);


#endif //COMPRESSOR_COMPRESSOR_H
