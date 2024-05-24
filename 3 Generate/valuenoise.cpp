/// \file valuenoise.cpp
/// \brief Code for the designer world class ValueNoiseWorldGenerator.

// Copyright Ian Parberry, November 2013.
//
// This file is made available under the GNU All-Permissive License.
//
// Copying and distribution of this file, with or without
// modification, are permitted in any medium without royalty
// provided the copyright notice and this notice are preserved.
// This file is offered as-is, without any warranty.

#include "valuenoise.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <ranges>

/// Get random height value at a point in the terrain.
/// Computes 1/f noise using the sample table.
/// \param x X coordinate of point at which to sample
/// \param z Z coordinate of point at which to sample
/// \param a Frequency
/// \param b Lacunarity
/// \param n Number of octaves
/// \return Height value between 0.0 and 1.0

float ValueNoiseWorldGenerator::get_height(float x, float z, float a, float b,
                                           int n) const
{
    float result = 0.0f;
    float scale = 1.0f;

    for (int i = 0; i < n; i++)
    {
        result += scale * get_noise(x, z);
        scale *= a;
        x *= b;
        z *= b;
    }

    return (1.0f + result * 1.414213f * (a - 1.0f) / (scale - 1.0f)) / 2.0f;
} // get_height

/// Get random height value for a single octave at a point in the terrain.
/// This is Value Noise. If you understand Perlin Noise, then this code will
/// be hauntingly familiar except for the fact that it uses position instead
/// of gradient.
/// \param x X coordinate of point at which to sample
/// \param z Z coordinate of point at which to sample
/// \return Height value between -1.0 and 1.0

float ValueNoiseWorldGenerator::get_noise(float x, float z) const
{
    const int dx = static_cast<int>(x);
    const float sx = S_CURVE(x - dx);
    const int i = m_permutationTable[MASK & dx];
    const int j = m_permutationTable[MASK & (dx + 1)];

    const int dz = static_cast<int>(z);
    const float sz = S_CURVE(z - dz);

    float u0 = m_heightValues[m_permutationTable[(i + dz) & MASK]];
    float u1 = m_heightValues[m_permutationTable[(j + dz) & MASK]];
    const float v0 = LERP(sx, u0, u1);
    u0 = m_heightValues[m_permutationTable[(i + dz + 1) & MASK]];
    u1 = m_heightValues[m_permutationTable[(j + dz + 1) & MASK]];
    const float v1 = LERP(sx, u0, u1);

    return LERP(sz, v0, v1);
} // noise
