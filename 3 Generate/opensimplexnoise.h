
#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <random>
#include <ranges>

#include "noise.h"

class OpenSimplexNoiseWorldGenerator : public NoiseGenerator
{
public:
    explicit OpenSimplexNoiseWorldGenerator(int numOctaves, float frequency, float lacunarity)
        : NoiseGenerator(numOctaves, frequency, lacunarity)
    {
        initialize_permutation_table();
    }

    float get_noise(float x, float z) const override;

    float get_height(float x, float z) const override;

private:
    static float grad(int hash, float x, float y)
    {
        int h = hash & 7;
        float u = h < 4 ? x : y;
        float v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0 * v : 2.0 * v);
    }

    static float fade(float t)
    {
        return t * t * t * (t * (t * 6 - 15) + 10);
    }

    static float lerp(float a, float b, float t)
    {
        return (1 - t) * a + t * b;
    }
};