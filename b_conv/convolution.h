/* setBfree - DSP tonewheel organ
 *
 * Copyright (C) 2012 Robin Gareus <robin@gareus.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef CONVOLUTION_H
#define CONVOLUTION_H

/* zita-convolver lib is C++ so we need extern "C" in order to link
 * functions using it. */
#ifdef __cplusplus
extern "C" {
#endif

#include "../src/cfgParser.h"
#include "../src/midi.h"

extern void setConvolutionMix (unsigned char u);

extern void initConvolution (void *clv, void *m, const unsigned int channels, const unsigned int buffersize, int sched_pri, int sched_pol);
extern void freeConvolution ();
extern void convolve (const float ** inbuf, float ** outbuf, size_t n_channels, size_t n_samples);

extern int convolutionConfig (ConfigContext * cfg);
const ConfigDoc *convolutionDoc ();

#ifdef __cplusplus
}
#endif

#endif
