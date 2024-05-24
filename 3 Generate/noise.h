#pragma once

#define S_CURVE(t) ((t) * (t) * (3.0f - 2.0f * (t)))
#define LERP(t, a, b) (a + (t) * (b - a))
#include <array>
#include <random>

class NoiseGenerator
{
public:
    float get_height(float x,
                     float z); // Get height for a point in the terrain.
    NoiseGenerator() : m_gen(m_rd()) { initialize_permutation_table(); }
    virtual ~NoiseGenerator() = default;
    void initialize_permutation_table();      ///< Initialize.
    void set_value_table(int table[], int n); //< Set value table,

private:
    static constexpr int SIZE = 256;  ///< Size of height table;
    static constexpr int MASK = 0xFF; ///< Mask for height table indices.

    std::array<float, SIZE> m_heightValues; ///< Value table.
    std::array<int, SIZE>
        m_permutationTable;  ///< Permutation table. Holds a random permutation.
    std::random_device m_rd; /// Fill sample table.
    std::mt19937 m_gen;      ///< Noise generator.

    /// Get random height value at a point in the terrain.
    virtual float get_noise(float x, float z) const = 0;
};
