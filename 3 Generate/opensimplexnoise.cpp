#include "opensimplexnoise.h"

float OpenSimplexNoiseWorldGenerator::get_noise(float x, float z) const
{
    // Compute the cell coordinates
    int xi = std::floor(x);
    int zi = std::floor(z);

    // Compute the fractional part
    float xf = x - xi;
    float zf = z - zi;

    // Compute the gradients
    float grad00 = grad(m_permutationTable[(m_permutationTable[xi & 255] + zi) & 255], xf, zf);
    float grad01 = grad(m_permutationTable[(m_permutationTable[xi & 255] + (zi + 1)) & 255], xf, zf - 1);
    float grad10 = grad(m_permutationTable[(m_permutationTable[(xi + 1) & 255] + zi) & 255], xf - 1, zf);
    float grad11 = grad(m_permutationTable[(m_permutationTable[(xi + 1) & 255] + (zi + 1)) & 255], xf - 1, zf - 1);

    // Compute the fade curves
    float u = fade(xf);
    float v = fade(zf);

    // Interpolate along x
    float interpX0 = LERP(u, grad00, grad10);
    float interpX1 = LERP(u, grad01, grad11);

    // Interpolate along y
    return LERP(v, interpX0, interpX1);
}

float OpenSimplexNoiseWorldGenerator::get_height(float x, float z) const
{
    float result = 0.0f;
    float scale = 1.0f;

    for (int i = 0; i < num_octaves; i++)
    {
        result += scale * get_noise(x, z);
        scale *= frequency;
        x *= lacunarity;
        z *= lacunarity;
    }

    return (1.0f + result * 1.414213f * (frequency - 1.0f) / (scale - 1.0f)) / 2.0f;
}