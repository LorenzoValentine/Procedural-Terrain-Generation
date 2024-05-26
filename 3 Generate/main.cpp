/// \file main.cpp

// Copyright Ian Parberry, November 2013.
//
// This file is made available under the GNU All-Permissive License.
//
// Copying and distribution of this file, with or without
// modification, are permitted in any medium without royalty
// provided the copyright notice and this notice are preserved.
// This file is offered as-is, without any warranty.

#include <array>
#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <random>

#include "opensimplexnoise.h"
#include "valuenoise.h"

constexpr int CELLSIZE = 4000; // width of square grid
constexpr int NUMOCTAVES = 8;  // What is
constexpr int ALTITUDE = 4000; // altitude scale value

// Height distribution data.
constexpr int POINTCOUNT = 31;
std::array<int, POINTCOUNT> g_nUtahDistribution = {
    1, 4, 6, 7, 7, 8, 10, 11, 14, 30, 37, 30, 19, 11, 8, 5, 5, 4, 3, 3, 3, 3, 3, 3, 5, 4, 4, 3, 2, 2, 1}; // Terrain height distribution data from Utah

/// Print the header for a DEM file.
/// \param output Output file handle.

void printDEMfileHeader(std::ofstream &output)
{
    if (!output)
        return; // bail and fail

    output << std::format("nrows {}\n", CELLSIZE);
    output << std::format("ncols {}\n", CELLSIZE);
    output << std::format("xllcenter {:0.6f}\n", 0.0f);
    output << std::format("yllcenter {:0.6f}\n", 0.0f);
    output << "cellsize 5.000000\n";
    output << "NODATA_value  -9999\n";
} // printDEMfileHeader

void printProgressBar(int step, int total, int bar_width = 50);

int main(int argc, char *argv[])
{
    std::ios_base::sync_with_stdio(false);
    // create a Timer
    auto start = std::chrono::high_resolution_clock::now();
    NoiseGenerator *g_cDesignerWorld = new OpenSimplexNoiseWorldGenerator(NUMOCTAVES, 0.5f, 2.0f); // Designer world object
    // initialize the random number generator
    auto seed = std::random_device{}(); // use hardware entropy if available
    // avoid using time as seed
    // auto seed = 8124078;
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    std::cout << std::format("Pseudorandom number seed = {}\n", seed);

    // set up designer world
    g_cDesignerWorld->initialize_permutation_table();
    if (dynamic_cast<ValueNoiseWorldGenerator*>(g_cDesignerWorld))
    {
        g_cDesignerWorld->set_value_table(g_nUtahDistribution.data(), POINTCOUNT);
    }

    // start the DEM file
    std::filesystem::path filename = std::format("{}.asc", seed);
    std::ofstream output(filename);
    printDEMfileHeader(output);

    // get random origin
    float x = distribution(generator);
    float z = distribution(generator);

    // generate and save grid heights to DEM file
    for (int i = 0; i < CELLSIZE; i++)
    {
        for (int j = 0; j < CELLSIZE; j++)
        {
            output << std::format("{:0.2f} ", ALTITUDE *
                                                  g_cDesignerWorld->get_height(x + i / 256.0f, z + j / 256.0f));
        }
        output << "\n";
        // show the current progress
        printProgressBar(i, CELLSIZE);
    } // for

    // shut down and exit
    std::cout << "\n";
    output.close();

    // timer stop
    auto stop = std::chrono::high_resolution_clock::now();
    // calculate the elapsed time, use xx.xxs format
    std::chrono::duration<double> elapsed = stop - start;
    std::cout << std::format("Elapsed time: {:.1f}s\n", elapsed.count());
    std::cout << "Hit Almost Any Key to Exit...\n";
    std::cin.get();
    return 0;
} // main

void printProgressBar(const int step, const int total, const int bar_width)
{
    std::cout << "[";
    int pos = bar_width * step / total;
    for (int i = 0; i < bar_width; ++i)
    {
        if (i < pos)
            std::cout << "=";
        else if (i == pos)
            std::cout << ">";
        else
            std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(static_cast<float>(step) / static_cast<float>(total) * 100.0) << " %\r";
    std::cout.flush();
}
