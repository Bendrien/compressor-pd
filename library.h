#ifndef COMPRESSOR_LIBRARY_H
#define COMPRESSOR_LIBRARY_H

#include "m_pd.h"
#include "compressor.h"

////////////////////////////////////////////////////////////
/// Static compressor instance
////////////////////////////////////////////////////////////
static t_class *compressor_tilde_class;

////////////////////////////////////////////////////////////
/// \brief Structure holding a compressors state
////////////////////////////////////////////////////////////
typedef struct t_compressor_tilde {
    t_object x_obj;

    // Inputs
    t_float in;
    t_inlet *in2;
    t_inlet *in3;
    t_inlet *in4;
    t_inlet *in5;
    t_inlet *in6;

    // Outputs
    t_outlet *out;
    t_outlet *out2;
    t_outlet *out3;

    // DSP instance
    t_compressor *compressor;
} t_compressor_tilde;

////////////////////////////////////////////////////////////
/// \brief Main DSP function
///
/// This functions does the main DSP computations.
///
/// \param w Pointer to a compressor instance and input/output arrays
///
/// \return A pointer to the data space for the next DSP object
///
////////////////////////////////////////////////////////////
t_int *compressor_tilde_perform(t_int *w);

////////////////////////////////////////////////////////////
/// \brief Threshold setter
///
/// This functions sets the threshold of the compressor.
///
/// \param x         Pointer to a compressor instance
/// \param threshold New value for the threshold
///
////////////////////////////////////////////////////////////
void compressor_tilde_set_threshold(t_compressor_tilde *x, t_floatarg threshold);

////////////////////////////////////////////////////////////
/// \brief Ratio setter
///
/// This functions sets the ratio of the compressor.
///
/// \param x     Pointer to a compressor instance
/// \param ratio New value for the ratio
///
////////////////////////////////////////////////////////////
void compressor_tilde_set_ratio(t_compressor_tilde *x, t_floatarg ratio);

////////////////////////////////////////////////////////////
/// \brief Attack setter
///
/// This functions sets the attack of the compressor.
///
/// \param x      Pointer to a compressor instance
/// \param attack New value for the attack
///
////////////////////////////////////////////////////////////
void compressor_tilde_set_attack(t_compressor_tilde *x, t_floatarg attack);

////////////////////////////////////////////////////////////
/// \brief Release setter
///
/// This functions sets the release of the compressor.
///
/// \param x       Pointer to a compressor instance
/// \param release New value for the release
///
////////////////////////////////////////////////////////////
void compressor_tilde_set_release(t_compressor_tilde *x, t_floatarg release);

////////////////////////////////////////////////////////////
/// \brief Post gain setter
///
/// This functions sets the post gain of the compressor.
///
/// \param x         Pointer to a compressor instance
/// \param post_gain New value for the post gain
///
////////////////////////////////////////////////////////////
void compressor_tilde_set_post_gain(t_compressor_tilde *x, t_floatarg post_gain);

////////////////////////////////////////////////////////////
/// \brief Post gain setter
///
/// This functions adds the object to the signal chain. 
/// Required by PD. It also initialized the sample rate.
///
/// \param x  Pointer to a compressor instance
/// \param sp A pointer to the input and output arrays
///
////////////////////////////////////////////////////////////
void compressor_tilde_dsp(t_compressor_tilde *x, t_signal **sp);

////////////////////////////////////////////////////////////
/// \brief Instanciate new compressor instance
///
/// This functions instanciate new compressor instance. It is
/// possible to construct the new object with  up to 5 
/// initialization arguments. These are, in order: threshold, 
/// ratio, attack, release and post gain.
///
/// \param argc Number of initialization arguments (range [0, 5])
/// \param argv Values for the initialization arguments.
///
/// \returns A pointer to the new instance
///
////////////////////////////////////////////////////////////
void *compressor_tilde_new(int argc, t_atom *argv);

////////////////////////////////////////////////////////////
/// \brief Free a compressor instance
///
/// This functions frees the memory acquired by a compressor
/// instance.
///
/// \param x         Pointer to a compressor instance
///
////////////////////////////////////////////////////////////
void compressor_tilde_free(t_compressor_tilde *x);

////////////////////////////////////////////////////////////
/// \brief Free a compressor instance
///
/// This functions registers the compressor struct and methods
/// to PDs system.
///
////////////////////////////////////////////////////////////
void compressor_tilde_setup(void);

#endif
