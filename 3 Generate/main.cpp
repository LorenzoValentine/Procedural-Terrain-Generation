#include <windows.h>
#include <MMSystem.h>
#include <stdio.h>
#include <conio.h>
#include <cmath> // Include cmath for math functions like sqrtf

#include "valuenoise.h"

const int CELLSIZE = 4000; //width of square grid
const int ALTITUDE = 4000; //altitude scale value

CDesignerWorld g_cDesignerWorld;

// 新的高度分布数据
const int POINTCOUNT = 31;
int g_nUtahDistribution[POINTCOUNT] = {
  1, 2, 3, 5, 8, 12, 18, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140
};

/// Print the header for a DEM file.
/// \param output Output file handle.
void printDEMfileHeader(FILE* output) {
    if (output == NULL) return; //bail and fail

    fprintf(output, "nrows %d\n", CELLSIZE);
    fprintf(output, "ncols %d\n", CELLSIZE);
    fprintf(output, "xllcenter %0.6f\n", 0.0f);
    fprintf(output, "yllcenter %0.6f\n", 0.0f);
    fprintf(output, "cellsize 5.000000\n");
    fprintf(output, "NODATA_value  -9999\n");
}

int main(int argc, char* argv[]) {
    // initialize the random number generator
    // int seed = timeGetTime();
    int seed = 8124078;
    srand(seed);
    printf("Pseudorandom number seed = %d\n", seed);

    // set up designer world
    g_cDesignerWorld.Initialize();
    g_cDesignerWorld.SetValueTable(g_nUtahDistribution, POINTCOUNT);

    // add some features
    g_cDesignerWorld.AddFeature(FLAT_AREA, 0.5f, 0.5f, 0.2f, 0.1f); // 添加一片平地
    g_cDesignerWorld.AddFeature(MOUNTAIN_RANGE, 0.7f, 0.3f, 0.1f, 0.9f); // 添加一个山脉
    g_cDesignerWorld.AddFeature(VALLEY, 0.2f, 0.8f, 0.15f, 0.3f); // 添加一个山谷
    g_cDesignerWorld.AddFeature(CANYON, 0.8f, 0.6f, 0.05f, 0.1f); // 添加一个峡谷

    // start the DEM file
    char filename[MAX_PATH];
    sprintf_s(filename, "%d.asc", seed);
    FILE* output;
    errno_t err = fopen_s(&output, filename, "wt");
    if (err != 0) {
        printf("Failed to open file for writing.\n");
        return 1;
    }

    printDEMfileHeader(output);

    // get random origin
    float x = fmod((float)rand(), 1000.0f); // 将 x 限制在 0 到 1000 的范围内
    float z = fmod((float)rand(), 1000.0f); // 将 z 限制在 0 到 1000 的范围内

    // 新的Octave Noise参数
    const float BASE_FREQUENCY = 0.05f; // 减小基础频率
    const float LACUNARITY = 2.0f;
    const int NUMOCTAVES = 8; // 减少Octave数量

    // generate and save grid heights to DEM file
    for (int i = 0; i < CELLSIZE; i++) {
        for (int j = 0; j < CELLSIZE; j++)
            fprintf(output, "%0.2f ", ALTITUDE *
                g_cDesignerWorld.GetHeight(x + i / 512.0f, z + j / 512.0f, BASE_FREQUENCY, LACUNARITY, NUMOCTAVES)); // 调整坐标范围
        fprintf(output, "\n");
        if (i % 100 == 0) printf(".");
    } //for

    // shut down and exit
    printf("\n");
    fclose(output);

    printf("Hit Almost Any Key to Exit...\n");
    _getch();
    return 0;
} //main

