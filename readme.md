# Enhancing the Efficiency of Real-World Procedural Terrain Generation

This is the extended version of the paper "Designer Worlds: Procedural Generation of Infinite Terrain from Real-World Elevation Data" by Ian Parberry. The original paper can be found [here](http://larc.unt.edu/ian/research/valuenoise/).

The purpose of this extended version is to enhance the efficiency of the original paper's method of generating terrain from real-world elevation data. The original paper describes a method to generate terrain from real-world elevation data using value noise. The method involves downloading elevation data from the United States Geographical Service, analyzing the data, and generating terrain based on the data.

We doing this enhancement by according to the knowledge we have gained from the Course COMP4610 from ANU (Australian National University) in 2024 Semester 1.

We, the authors of this extended version, have made the following changes to the original repository:

1. Code Frame Update:
    - Updated the code to Visual Studio 2022 and C++20 from Visual Studio 2012.

2. Code Optimization:



We acknowledge that the original paper was published under the GNU All-Permissive License, and we have made sure to follow the same license for this extended version.

To correctly use the code in this repository, please follow the instructions below:

Please note that the original repository use the Visual Studio 2012 Solution and C++ source code. We have updated the code to Visual Studio 2022 and C++20. The code must be compiled and executed in Visual Studio 2022(MSVC), with a windows operating system. The code may not work on other operating systems or compilers.

1. Compulsory Software:
    - Windows Operating System
    - Visual Studio 2022 with C++ Desktop Development
    - GIS Software to open .ais file [QGIS(free, recommend), ArcGIS, etc.]

## Here is the original readme file from the repository

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
