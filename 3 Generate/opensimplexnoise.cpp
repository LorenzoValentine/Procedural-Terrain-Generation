#include "opensimplexnoise.h"

float OpenSimplexNoiseWorldGenerator::get_noise(float x, float z) const
{
    // Compute the cell coordinates
    int xi = std::floor(x);
    int zi = std::floor(z);

    // Compute the fractional part
    double xf = x - xi;
    double zf = z - zi;

    // Compute the gradients
    double grad00 = grad(m_permutationTable[(m_permutationTable[xi & 255] + zi) & 255], xf, zf);
    double grad01 = grad(m_permutationTable[(m_permutationTable[xi & 255] + (zi + 1)) & 255], xf, zf - 1);
    double grad10 = grad(m_permutationTable[(m_permutationTable[(xi + 1) & 255] + zi) & 255], xf - 1, zf);
    double grad11 = grad(m_permutationTable[(m_permutationTable[(xi + 1) & 255] + (zi + 1)) & 255], xf - 1, zf - 1);

    // Compute the fade curves
    double u = fade(xf);
    double v = fade(zf);

    // Interpolate along x
    double interpX0 = lerp(grad00, grad10, u);
    double interpX1 = lerp(grad01, grad11, u);

    // Interpolate along y
    double interpY = lerp(interpX0, interpX1, v);
    // the range of the noise is -1 to 1, so we need to scale it to 0 to 1 so the code is consistent with the ValueNoiseWorldGenerator
    return (interpY + 1) / 2;
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