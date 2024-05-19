/// \file valuenoise.cpp
/// \brief Code for the designer world class CDesignerWorld.

#include <stdlib.h>
#include <stdio.h>
#include <cmath> // Include cmath for math functions like sqrtf

#include "valuenoise.h"

void CDesignerWorld::Initialize(){
  // start with identity permutation
  for(int i=0; i<SIZE; i++)
    m_nPermute[i] = i;

  // randomize 
  for(int i=SIZE-1; i>0; i--){
    int j = rand() % (i + 1);
    int temp = m_nPermute[i];
    m_nPermute[i] = m_nPermute[j];
    m_nPermute[j] = temp;
  }
}

void CDesignerWorld::SetValueTable(int table[], const int n){
  // check that the values add up to 256
  int sum = 0;
  for(int i=0; i<n; i++)
    sum += table[i];
  if(sum != SIZE){
    printf("Height distribution values must sum to %d, not %d\n", SIZE, sum);
    return;
  }

  // fill the table
  float delta = 2.0f/(float)(n-1); // interval size
  float min = -1.0f; // lower limit if interval
  int k = 0; // fill in m_fPosition[k]
  for(int i=0; i<n-1; i++){
    for(int j=0; j<table[i]; j++)
      m_fPosition[k++] = min + delta * (float)rand()/(float)RAND_MAX;
    min += delta;
  }

  // missed the largest values, get them now
  for(int j=0; j<table[n-1]; j++)
    m_fPosition[k++] = 1.0f;
}

float CDesignerWorld::GetHeight(float x, float z, float baseFrequency, float lacunarity, int numOctaves) {
  float baseHeight = 0.0f; // 初始基本高度为0

  float frequency = baseFrequency; // 初始频率
  float amplitude = 1.0f; // 初始振幅
  float maxAmplitude = 0.0f; // 最大振幅

  for (int octave = 0; octave < numOctaves; octave++) { // 对每个Octave
    baseHeight += amplitude * noise(x * frequency, z * frequency);
    maxAmplitude += amplitude;
    frequency *= lacunarity; // 调整下一个Octave的频率
    amplitude *= 0.5f; // 调整下一个Octave的振幅
  }

  baseHeight /= maxAmplitude; // 归一化高度
  baseHeight = (1.0f + baseHeight) / 2.0f; // 将基本高度缩放到[0.0, 1.0]范围内

  return ApplyFeatures(x, z, baseHeight); // 应用地形特征
}

float CDesignerWorld::noise(float x, float z){
  const int dx = (int)x;
  const float sx = s_curve(x - dx);
  const int i = m_nPermute[MASK & dx];
  const int j = m_nPermute[MASK & (dx + 1)];

  const int dz = (int)z;
  const float sz = s_curve(z - dz);

  float u0 = m_fPosition[m_nPermute[(i + dz) & MASK]];
  float u1 = m_fPosition[m_nPermute[(j + dz) & MASK]];
  const float v0 = lerp(sx, u0, u1);
  u0 = m_fPosition[m_nPermute[(i + dz + 1) & MASK]];
  u1 = m_fPosition[m_nPermute[(j + dz + 1) & MASK]];
  const float v1 = lerp(sx, u0, u1);

  return lerp(sz, v0, v1);
}

void CDesignerWorld::AddFeature(FeatureType type, float centerX, float centerZ, float radius, float height) {
  FeatureInfo info = { type, centerX, centerZ, radius, height };
  m_features.push_back(info);
}

float CDesignerWorld::ApplyFeatures(float x, float z, float baseHeight) {
  float height = baseHeight;
  for (const FeatureInfo& info : m_features) {
    float dx = x - info.centerX;
    float dz = z - info.centerZ;
    float distance = sqrtf(dx * dx + dz * dz);
    if (distance <= info.radius) {
      switch (info.type) {
      case FLAT_AREA:
        height = info.height;
        break;
      case MOUNTAIN_RANGE:
        height = std::max(height, info.height);
        break;
      case VALLEY:
        height = std::min(height, info.height);
        break;
      case CANYON:
        height = info.height;
        break;
      }
    }
  }
  return height;
}
