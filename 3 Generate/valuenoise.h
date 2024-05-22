/// \file valuenoise.h
/// \brief Interface for the designer world class CDesignerWorld.

//Copyright Ian Parberry, November 2013.
//
//This file is made available under the GNU All-Permissive License.
//
//Copying and distribution of this file, with or without
//modification, are permitted in any medium without royalty
//provided the copyright notice and this notice are preserved.
//This file is offered as-is, without any warranty.

#pragma once

#define S_CURVE(t)  ((t)*(t)*(3.0f - 2.0f*(t)))
#define LERP(t, a, b) (a + (t)*(b - a))
#include <array>

/// \brief Designer World generator.
///
/// The Designer World generator makes 2D noise suitable for terrain height maps.
/// It combines Value Noise with a height distribution.

class CDesignerWorld{
  static constexpr int SIZE = 256; ///< Size of height table;
  static constexpr int MASK = 0xFF; ///< Mask for height table indices.

  std::array<float, SIZE> m_heightValues; ///< Value table.
  std::array<int, SIZE> m_permutationTable; ///< Permutation table. Holds a random permutation.
  std::random_device m_rd; /// Fill sample table.
  std::mt19937 m_gen; ///< Noise generator.

  // void InitSampleTable(float scale);
  float noise(float x, float z) const;

public:
  CDesignerWorld() : m_gen(m_rd())
  {
    InitializePermutationTable();
  }

  void InitializePermutationTable(); ///< Initialize.
  void SetValueTable(int table[], int n); //< Set value table.
  float GetHeight(float x, float z, float a, float b, int n); ///< Get height.
}; //CDesignerWorld