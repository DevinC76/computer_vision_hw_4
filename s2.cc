// Program 2 - HW4
// Author: <Devin Chen>

#include "image.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace ComputerVisionProjects;

std::vector<double> calUnitNormal(int centerx, int centery, double radius, Image &sample)
{
  // startx = center x - radius
  // endx = center x  + radius

  // starty = center y + radius
  // endy = center y - raidus
  int max_x = 0;
  int max_y = 0;
  int value = 0;
  //Finding brightest point
  for (int i = centery - radius; i < centery + radius; i++)
  {
    for (int j = centerx - radius; j < centerx + radius; j++)
    {
      if (sample.GetPixel(i, j) > value)
      {
        max_x = j;
        max_y = i;
        value = sample.GetPixel(i, j);
      }
    }
  }

  double N1 = max_x - centerx; //Correct
  double N2 = max_y - centery; //Correct
  double N3 = std::sqrt(std::pow(radius, 2) - std::pow(N1, 2) - std::pow(N2, 2)); // Correct
  double nhat = std::sqrt(std::pow(N1, 2) + std::pow(N2, 2) + std::pow(N3, 2)); // Correct
  return std::vector<double>{N1 * value / nhat, N2 * value/ nhat, N3*value/nhat}; // Correct 
}

int main(int argc, char **argv)
{
  if (argc != 6)
  {
    std::cout << "Usage: " << argv[0] << " {input-parameters-file} {sphere-image-1} {sphere-image-2} {sphere-image-3} {output-directions-file}"
              << std::endl;
    return 0;
  }

  const std::string parameters_file(argv[1]);
  const std::string sphere_image1(argv[2]);
  const std::string sphere_image2(argv[3]);
  const std::string sphere_image3(argv[4]);
  const std::string output_directions_file(argv[5]);

  std::ifstream parameters(parameters_file);
  Image image1;
  Image image2;
  Image image3;

  /*
  Reading the Images
  */
  if (!ReadImage(sphere_image1, &image1))
  {
    std::cout << "Can't open file" << sphere_image1 << std::endl;
    return 0;
  }

  if (!ReadImage(sphere_image2, &image2))
  {
    std::cout << "Can't open file" << sphere_image2 << std::endl;
    return 0;
  }

  if (!ReadImage(sphere_image3, &image3))
  {
    std::cout << "Can't open file" << sphere_image3 << std::endl;
    return 0;
  }

  if (!parameters)
  {
    std::cout << "Can not open file " << parameters_file << std::endl;
    return 1;
  }

  int centerx;
  int centery;
  double radius;
  parameters >> centerx >> centery >> radius;

  auto result1 = calUnitNormal(centerx, centery, radius, image1);
  auto result2 = calUnitNormal(centerx, centery, radius, image2);
  auto result3 = calUnitNormal(centerx, centery, radius, image3);

  std::ofstream outText(output_directions_file);

  if (!outText)
  {
    std::cerr << "Could not open file for appending.\n";
    return 1;
  }

  outText << result1[0] << " " << result1[1] << " " << result1[2] << "\n";
  outText << result2[0] << " " << result2[1] << " " << result2[2] << "\n";
  outText << result3[0] << " " << result3[1] << " " << result3[2] << "\n";

  outText.close();

  std::cout << "Running s2 " << parameters_file << " " << sphere_image1 << " " << sphere_image2
            << " " << sphere_image3 << " " << output_directions_file << std::endl;
  return 0;
}
