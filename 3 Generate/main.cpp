/// \file main.cpp

//Copyright Ian Parberry, November 2013.
//
//This file is made available under the GNU All-Permissive License.
//
//Copying and distribution of this file, with or without
//modification, are permitted in any medium without royalty
//provided the copyright notice and this notice are preserved.
//This file is offered as-is, without any warranty.

#include <chrono>
#include <filesystem>
#include <fstream>
#include <format>
#include <random>
#include <array>
#include <iostream>

#include "valuenoise.h"

constexpr int CELLSIZE = 4000; // width of square grid
constexpr int NUMOCTAVES = 8; // What is 
constexpr int ALTITUDE = 4000; // altitude scale value

auto g_cDesignerWorld = ValueNoiseWorldGenerator(); // Designer world object

//Height distribution data.
constexpr int POINTCOUNT = 31;
std::array<int, POINTCOUNT> g_nUtahDistribution = {
    1, 4, 6, 7, 7, 8, 10, 11, 14, 30, 37, 30, 19, 11, 8, 5, 5, 4, 3, 3, 3, 3, 3, 3, 5, 4, 4, 3, 2, 2, 1
}; // Terrain height distribution data from Utah

/// Print the header for a DEM file.
/// \param output Output file handle.

void printDEMfileHeader(std::ofstream& output)
{
    if (!output) return; //bail and fail

    output << std::format("nrows {}\n", CELLSIZE);
    output << std::format("ncols {}\n", CELLSIZE);
    output << std::format("xllcenter {:0.6f}\n", 0.0f);
    output << std::format("yllcenter {:0.6f}\n", 0.0f);
    output << "cellsize 5.000000\n";
    output << "NODATA_value  -9999\n";
} //printDEMfileHeader

void printProgressBar(int step, int total, int bar_width = 50);

int main(int argc, char* argv[])
{
    //initialize the random number generator
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(0.0, 1.0);
    std::cout << std::format("Pseudorandom number seed = {}\n", seed);

    //set up designer world
    g_cDesignerWorld.initialize_permutation_table();
    g_cDesignerWorld.set_value_table(g_nUtahDistribution.data(), POINTCOUNT);

    //start the DEM file
    std::filesystem::path filename = std::format("{}.asc", seed);
    std::ofstream output(filename);
    printDEMfileHeader(output);

    //get random origin
    float x = distribution(generator);
    float z = distribution(generator);

    //generate and save grid heights to DEM file
    for (int i = 0; i < CELLSIZE; i++)
    {
        for (int j = 0; j < CELLSIZE; j++)
        {
            output << std::format("{:0.2f} ", ALTITUDE *
                                  g_cDesignerWorld.get_height(x + i / 256.0f, z + j / 256.0f, 0.5f, 2.0f, NUMOCTAVES));
        }
        output << "\n";
        // show the current progress
        printProgressBar(i, CELLSIZE);
    } //for

    //shut down and exit
    std::cout << "\n";
    output.close();

    std::cout << "Hit Almost Any Key to Exit...\n";
    std::cin.get();
    return 0;
} //main

void printProgressBar(const int step,const int total,const int bar_width)
{
    std::cout << "[";
    int pos = bar_width * step / total;
    for (int i = 0; i < bar_width; ++i)
    {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << static_cast<int>(static_cast<float>(step) / static_cast<float>(total) * 100.0) << " %\r";
    std::cout.flush();
}
