// Program 1 - HW4
// Author: <Devin Chen>

#include "image.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>
using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    std::cout << "Usage: " << argv[0] << " {gray-level-sphere-file} {gray-level-threshold} {output-parameters-file}" << std::endl;
    return 0;
  }
  const std::string input_file(argv[1]);
  const int threshold = atoi(argv[2]);
  const std::string output_file(argv[3]);

  Image image;
  if (!ReadImage(input_file, &image))
  {
    std::cout << "Can't open file" << input_file << std::endl;
    return 0;
  }

  for (int i = 0; i < image.num_rows(); i++)
  {
    for (int j = 0; j < image.num_columns(); j++)
    {
      if (image.GetPixel(i, j) < threshold)
      {
        image.SetPixel(i, j, 0);
      }

      else
      {
        image.SetPixel(i, j, 255);
      }
    }
  }

  struct Object
  {
    double x = 0;
    double y = 0;
    double area = 0;
  };

  int min_y = std::numeric_limits<int>::max();
  int min_x = std::numeric_limits<int>::max();
  int max_y = std::numeric_limits<int>::min();
  int max_x = std::numeric_limits<int>::min();

  Object objects;

  for (int i = 0; i < image.num_rows(); i++)
  {
    for (int j = 0; j < image.num_columns(); j++)
    {
      int label = image.GetPixel(i, j);
      if (label != 0)
      {
        objects.x += j; // column
        objects.y += i; // row
        objects.area += 1;
        min_y = std::min(min_y, i);
        min_x = std::min(min_x, j);

        max_y = std::max(max_y, i);
        max_x = std::max(max_x, j);
      }
    }
  }

  double center_x = objects.x / objects.area;
  double center_y = objects.y / objects.area;
  double diameter_x = static_cast<double>(max_x - min_x);
  double diameter_y = static_cast<double>(max_y - min_y);
  double diameter = (diameter_x + diameter_y) / 2.0;
  double radius = diameter / 2.0;

  std::ofstream outText(output_file);
  outText << (int)center_x << " " << (int)center_y << " " << radius << "\n";
  outText.close();
  image.SetPixel((int)center_y, (int)center_x, 0);

  std::cout << "Running s1 " << input_file << " " << threshold << " " << output_file << std::endl;
  return 0;
}
