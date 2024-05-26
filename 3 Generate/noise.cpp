#include "noise.h"

#include <algorithm>
#include <numeric>
#include <random>
#include <ranges>

/// Initialize the permutation table.
void NoiseGenerator::initialize_permutation_table()
{
    std::iota(m_permutationTable.begin(), m_permutationTable.end(), 0);
    std::ranges::shuffle(m_permutationTable, m_gen);
} // Initialize

/// Set the value table.
/// \param table Table of values.
/// \param n Size of table.

void NoiseGenerator::set_value_table(int table[], const int n)
{
    // Check that the table sums to SIZE.
    int sum = std::accumulate(table, table + n, 0);
    if (sum != SIZE)
    {
        printf("Height distribution values must sum to %d, not %d\n", SIZE,
               sum);
        return;
    }

    // Fill the height table with values from the distribution table.
    float delta = 2.0f / static_cast<float>(n - 1);
    float min = -1.0f;
    int k = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < table[i]; j++)
            m_heightValues[k++] = min + delta * dis(gen);
        min += delta;
    }

    for (int j = 0; j < table[n - 1]; j++)
        m_heightValues[k++] = 1.0f;
}

