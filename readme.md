# Enhancing the Efficiency of Real-World Procedural Terrain Generation

This is the extended version of the paper "Designer Worlds: Procedural Generation of Infinite Terrain from Real-World Elevation Data" by Ian Parberry. The original paper can be found [here](http://larc.unt.edu/ian/research/valuenoise/).

The purpose of this extended version is to enhance the efficiency of the original paper's method of generating terrain from real-world elevation data. The original paper describes a method to generate terrain from real-world elevation data using value noise. The method involves downloading elevation data from the United States Geographical Service, analyzing the data, and generating terrain based on the data.

We doing this enhancement by according to the knowledge we have gained from the Course COMP4610 from ANU (Australian National University) in 2024 Semester 1.

We, the authors of this extended version, have made the following changes to the original repository:

## Code Framework Update

1. Updated the code to C++20 from C++98 with Visual Studio 2012.
2. Deprecated the use of the MSBuild system and updated the code to use the XMake build system.

## Code Optimization without relating to change the method


Most enhancements are made in the generation of the terrain, which the 3 Generation folder contains.

1. Improved noise generation and permutation tables

   - Improve the noise generation algorithm by incorporating a more robust algorithm and updating the permutation table to enhance terrain height distribution. This change ensures that the resulting terrain is not only visually appealing but also provides better performance for real-time rendering applications.

2. Enhanced the code inheritance relationship

   - Refactor the code to improve the inheritance relationship between classes and reduce code duplication. The new `noise` class is now the base class for all noise generation algorithms, allowing for easier extensibility and maintenance.

## Method Optimization relating to enhance the method


The original paper describes a method to generate terrain from real-world elevation data using value noise. It compares the value noise with Perlin noise and concludes that value noise is more suitable for generating geotypical terrain based on elevation statistics. However, due to the paper is written in 2014, the method may not be the most efficient way to generate terrain in 2024. Therefore, we have made the following optimizations to the method:

1. New noise generation algorithm

   - After changing the inheritance relationship, we have implemented a new noise generation algorithm called SimplexNoise. This algorithm is more efficient than the value noise algorithm and provides better results in terms of terrain generation.
   - Currently, both the value noise and SimplexNoise algorithms are inherited from the noise class, allowing for easy switching between the two algorithms.

```cpp
class ValueNoiseWorldGenerator : public NoiseGenerator // Previous value noise algorithm

class OpenSimplexNoiseWorldGenerator : public NoiseGenerator // New SimplexNoise algorithm
```



We acknowledge that the original paper was published under the GNU All-Permissive License, and we have made sure to follow the same license for this extended version.

To correctly use the code in this repository, please follow the instructions below:

## Environment Setup

**Please remember to set the C++ Version to C++20 in the IDE. The code is not compatible with any other version of C++.**

### If you are using the Windows operating system

Make sure you have the following installed:

1. Install XMake build system from [here](https://xmake.io/#/) or by running the following command in windows terminal by using Scoop package manager:

    ```bash
    scoop install xmake
    ```

2. Install C++20 compiler by running the following command in windows terminal by using Scoop package manager:

    ```bash
    scoop install mingw-winlibs-llvm-ucrt
    ```

3. Install any of the IDEs, such as Visual Studio Code (recommend), Visual Studio, or CLion, to open the project.
4. Make sure the C++ Version is set to C++20 in the IDE.

### If you are using the MacOS operating system

Make sure you have the following installed:

1. Install XMake build system from [here](https://xmake.io/#/) or by running the following command in terminal by using Homebrew:

    ```bash
    brew install xmake
    ```

2. Install C++20 compiler by running the following command in windows terminal:

    ```bash
    xcode-select --install
    ```

    Please make sure to have the Xcode installed in your system and open it at least once. Once you have install the latest command line tools, you can easily use the C++20 compiler.


## How to run the code

Please make sure you are in the 3 Generation folder before running the following commands. Do not change any code in the `xmake.lua` file.

To build the code, run the following command:

```bash
xmake
```

To run the code, run the following command:

```bash
xmake run
```

The generated DEM file will be saved in the `build/windows` folder. Or if you are using MacOS, the generated DEM file will be saved in the `build/macosx` folder.
The DEM file is named as `seed.asc`, where seed is a random number generated by the code. You can check your seed number in the console output as follows:

```bash
bash Procedural-Terrain-Generation\3 Generate> xmake run
Pseudorandom number seed = 2484715620
[=================================================>] 99 %
Hit Almost Any Key to Exit...
```

## How to change noise generator

You can easily change the noise generator by changing the 4th line in the `main` function in the `main.cpp` file:

```cpp
NoiseGenerator *g_cDesignerWorld = new ValueNoiseWorldGenerator(NUMOCTAVES, 0.5f, 2.0f); // ValueNoise
NoiseGenerator *g_cDesignerWorld = new OpenSimplexNoiseWorldGenerator(NUMOCTAVES, 0.5f, 2.0f); // new SimplexNoise

```

## How to make seed number fixed

We use two random number generators to ensure that the random numbers generated each time are not 'pseudo-random numbers'. However, this results in that the DEM files generated each time the code is run are different and cannot be compared. In order to generate files containing the same seed value for both noises, you can make the following changes to the code:

1. Comment line 57 in the `main.cpp` file:

```cpp
auto seed = std::random_device{}(); // Comment this line
```

2. Uncomment line 59 in the `main.cpp` file:

```cpp
auto seed = 8124078; // Uncomment this line, you can change any of the seed numbers
```

3. Change the line 14 in the `noise.h` file to the following:

```cpp
m_gen(seed you entered in the main.cpp file);
```

- for example, if you change the seed number to 8124078, the line 14 in the `noise.h` file should be:

    ```cpp
    m_gen(8124078);
    ```
Any changes to the seed number in the `main.cpp` file will be reflected in the DEM file generated by the code. Please remember to rebuild the code after making these changes.

## How to view the generated DEM file

### Install Software by using the following instructions

The original instruction of the repository recommends using Terragen 3 to view the generated DEM file WITH rendered terrain. However, as the Terragen 3 software is outdated and not available for free, we recommend using the FREE Terragen 4 Software to view the generated DEM file. The Terragen 4 software can be downloaded from [here](https://planetside.co.uk/free-downloads/terragen-4-free-download/). (Most Recommended)

Otherwise, you can choose the following alternative:

The GIS software such as QGIS can be used to view the generated DEM file. The QGIS software can be downloaded from [here](https://qgis.org/en/site/forusers/download.html). But the application size is large and may take time to download.

### Open the DEM file in the software

#### If you are using Terragen 4

1. Open the Terragen 4 software.
2. Delete the default terrain in the left top corner by pressing the 'Delete' key.
3. Click 'Add Terrain' in the left top corner, choose 'Heightfield(load DEM)', then choose the generated DEM file(.asc).
4. Adjust the cameras to the right position to view the terrain, you can adjust the camera by click the 'Camera' button in the top bar, the change the position and rotation at the left bottom bar.
5. When the position is set, click the 'Render' button in the top left corner, the 4th small square icon with a 'R' to open the render view.
6. Click the 'Render' button in the render view to render the terrain.
7. The video tutorial can be found [here](https://youtu.be/HnRFJ4Vptt8?si=5vV3ZYlceLdAZgoc).

#### If you are using QGIS

1. Open the QGIS Desktop.
2. Drag and drop the generated DEM file(s) into the Center, white area.
3. At the left down corner, you can see the DEM file(s) loaded in the Layers Panel.
4. Mostly, the Layer styling panel will be opened at the right side of the screen. If not, you can open it by double clicking the DEM file in the Layers Panel.
5. In the Layer styling panel, you can change the color of the DEM file by clicking the color box in the Singleband pseudocolor section, we will only use the 'Singleband Gray', 'Hillshade' and 'Contours'.
6. When you import two of the different DEM files, you can set visibility by clicking the checkbox in the Layers Panel.
7. The video tutorial can be found [here](https://anu365-my.sharepoint.com/:v:/g/personal/u7381573_anu_edu_au/EWC128InWPtOmpTvr9m8lI4BMdIjZmt9cD_wJ5QOd-3ZCA?e=RKieqF).


## Here is the original readme file from the original repository

## Designer Worlds

  This GitHub repository contains supplementary material to accompany
  Ian Parberry, "Designer Worlds: Procedural Generation of Infinite Terrain from
  Real-World Elevation Data", Journal of Computer Graphics Techniques, Vol. 3,
  No. 1, pp. 74-85, 2014.

  See also http://larc.unt.edu/ian/research/valuenoise/.

## ABSTRACT

  The standard way to procedurally generate random terrain for video games
  and other applications is to post-process the output of a fast noise
  generator such as Perlin Noise. Tuning the post-processing to achieve
  particular types of terrain requires game designers to be reasonably
  well-trained in mathematics. A well-known variant of Perlin Noise called
  <em>value noise</em> is used in a process accessible to designers trained
  in geography to generate geotypical terrain based on elevation statistics
  drawn from widely available sources such as the United States Geographical
  Service. A step-by-step process for downloading and creating terrain from
  real-world elevation data is described, and an implementation in C++ is given.

## LICENSE

  The source code in this repository is made available under the following license.

  // Copyright Ian Parberry, (date).<br>
  //<br>
  // This file is made available under the GNU All-Permissive License.<br>
  //<br>
  // Copying and distribution of this file, with or without modification,<br>
  // are permitted in any medium without royalty provided the copyright<br>
  // notice and this notice are preserved.  This file is offered as-is,<br>
  // without any warranty.<br>

## CONTENTS

  1. Data
  2. Analyze
  3. Generate
  4. View

1. Data

  According to the paper, this folder is supposed to contain a DEM file
  12SVH200800.asc and an image file mountain2.png of the area that it covers.
  The image file is here, but the DEM file exceeds GitHub's size limit. Instead,
  12SVH200800.asc contains a link to a place from which you can download the
  actual file from the UAGRC.


2. Analyze

  This folder contains a Visual Studio 2012 Solution and C++ source code that,
  when compiled and executed, reads 12SVH200800.asc and outputs two text files,
  output.txt which contains data for a histogram, and code.txt which contains a
  code snippet to be added to the Designer Worlds generator. There is also an Excel
  spreadsheet data.xlsx containing a histogram drawn from the data in output.txt.

3. Generate

  This folder contains a Visual Studio 2012 Solution and C++ source code
  for the Designer Worlds Generator. The code from code.txt in the Analyze
  folder has been pasted into the appropriate place in main.cpp. Each time this
  code is executed it will output a DEM file for a piece of random terrain similar
  to the original DEM file. It is also supposed to contain a generated DEM file
  1293054609.asc, but once again we hit the GitHub size limit, so you'll have
  to generate it yourself.

4. View

  Contents: A Terragen 3 Project File 1293054609.tgd for the terrain described by
  1293054609.asc from the Generator, and an image file 1293054609.jpg generated by
  running Terragen 3 on that Project file. Terragen 3 is available from
  http://planetside.co.uk/products/terragen3.
