/// \file valuenoise.h
/// \brief Interface for the designer world class ValueNoiseWorldGenerator.

// Copyright Ian Parberry, November 2013.
//
// This file is made available under the GNU All-Permissive License.
//
// Copying and distribution of this file, with or without
// modification, are permitted in any medium without royalty
// provided the copyright notice and this notice are preserved.
// This file is offered as-is, without any warranty.

#pragma once
#include <array>
#include <random>

#include "noise.h"

/// \brief Designer World generator.
///
/// The Designer World generator makes 2D noise suitable for terrain height
/// maps. It combines Value Noise with a height distribution.

class ValueNoiseWorldGenerator : public NoiseGenerator
{
    static constexpr int SIZE = 256;  ///< Size of height table;
    static constexpr int MASK = 0xFF; ///< Mask for height table indices.

    float get_noise(float x, float z) const override;

public:
    ValueNoiseWorldGenerator(int numOctaves, float frequency, float lacunarity)
        : NoiseGenerator(numOctaves, frequency, lacunarity)
    {
        initialize_permutation_table();
    }
    float get_height(float x, float z) const override; ///< Get height.
}; // ValueNoiseWorldGenerator
