// Program 3 - HW4
// Author: <Devin Chen>

#include "image.h"
#include <string>
#include <iostream>
#include <bits/stdc++.h>

using namespace ComputerVisionProjects;

int main(int argc, char **argv)
{
  if (argc != 9)
  {
    std::cout << "Usage: " << argv[0] << " {input-directions-file} {image1} {image2} {image3} {step} {threshold} {normals-output-file} {albedo-output-file}"
              << std::endl;
    return 0;
  }

  const std::string directions_file(argv[1]);
  const std::string image1_file(argv[2]);
  const std::string image2_file(argv[3]);
  const std::string image3_file(argv[4]);
  const int step = atoi(argv[5]);
  const int threshold = atoi(argv[6]);
  const std::string normals_output_file(argv[7]);
  const std::string albedo_output_file(argv[8]);
  Image image1;
  Image image2;
  Image image3;

  if (!ReadImage(image1_file, &image1))
  {
    std::cout << "Can't open file" << image1_file << std::endl;
    return 0;
  }

  if (!ReadImage(image2_file, &image2))
  {
    std::cout << "Can't open file" << image2_file << std::endl;
    return 0;
  }

  if (!ReadImage(image3_file, &image3))
  {
    std::cout << "Can't open file" << image3_file << std::endl;
    return 0;
  }

  std::vector<std::vector<double>> S(3, std::vector<double>(3));
  std::ifstream direction_intensity(directions_file);
  if (!direction_intensity)
  {
    std::cout << "Can not open file " << directions_file << std::endl;
    return 1;
  }

  for (int i = 0; i < 3; ++i)
  {
    double sx, sy, sz;

    if (direction_intensity >> sx >> sy >> sz)
    {
      S[i][0] = sx;
      S[i][1] = sy;
      S[i][2] = sz;
    }
    else
    {
      std::cerr << "Error" << std::endl;
      return 1;
    }
  }

  std::vector<std::vector<double>> S_inverse = S;
  double det = S[0][0] * (S[1][1] * S[2][2] - S[1][2] * S[2][1]) -
               S[0][1] * (S[1][0] * S[2][2] - S[1][2] * S[2][0]) +
               S[0][2] * (S[1][0] * S[2][1] - S[1][1] * S[2][0]);
  double invert_det = 1 / det;

  S_inverse[0][0] = (S[1][1] * S[2][2] - S[1][2] * S[2][1]) * invert_det;
  S_inverse[0][1] = (S[0][2] * S[2][1] - S[0][1] * S[2][2]) * invert_det;
  S_inverse[0][2] = (S[0][1] * S[1][2] - S[0][2] * S[1][1]) * invert_det;
  S_inverse[1][0] = (S[1][2] * S[2][0] - S[1][0] * S[2][2]) * invert_det;
  S_inverse[1][1] = (S[0][0] * S[2][2] - S[0][2] * S[2][0]) * invert_det;
  S_inverse[1][2] = (S[0][2] * S[1][0] - S[0][0] * S[1][2]) * invert_det;
  S_inverse[2][0] = (S[1][0] * S[2][1] - S[1][1] * S[2][0]) * invert_det;
  S_inverse[2][1] = (S[0][1] * S[2][0] - S[0][0] * S[2][1]) * invert_det;
  S_inverse[2][2] = (S[0][0] * S[1][1] - S[0][1] * S[1][0]) * invert_det;

  Image albedoimage = image1;
  Image normalimage = image1;

  for (int i = 0; i < image1.num_rows(); i++)
  {
    for (int j = 0; j < image1.num_columns(); j++)
    {
      if (image1.GetPixel(i, j) < threshold || image2.GetPixel(i, j) < threshold || image3.GetPixel(i, j) < threshold)
      {
        albedoimage.SetPixel(i, j, 0);
        continue;
      }
      double I_1 = image1.GetPixel(i, j);
      double I_2 = image2.GetPixel(i, j);
      double I_3 = image3.GetPixel(i, j);
      std::vector<int> INTENSITY = {image1.GetPixel(i, j), image2.GetPixel(i, j), image3.GetPixel(i, j)};
      std::vector<double> N(3, 0);
      std::vector<double> n(3, 0);

      for (int i = 0; i < 3; i++)
      {
        for (int j = 0; j < 3; j++)
          N[i] += S_inverse[i][j] * INTENSITY[j];
      }
      double albedo = sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);
      for (int i = 0; i < 3; i++)
      {
        n[i] = N[i] / albedo;
      }
      albedoimage.SetPixel(i, j, albedo * 255);
      int length = 5;
      if (i % step == 0 && j % step == 0)
      {
        int row = (i + length * n[1]);
        int column = (j + length * n[0]);
        row = std::min<int>(std::max(row, 0), image1.num_rows() - 1);
        column = std::min<int>(std::max(column, 0), image1.num_columns() - 1);

        DrawLine(i, j, row, column, 255, &normalimage);
        normalimage.SetPixel(i, j, 0);
        normalimage.SetPixel(i - 1, j, 255);
        normalimage.SetPixel(i + 1, j, 255);
        normalimage.SetPixel(i, j - 1, 255);
        normalimage.SetPixel(i, j + 1, 255);
      }
    }
  }

  if (!WriteImage(albedo_output_file, albedoimage))
  {
    return 0;
  }

  if (!WriteImage(normals_output_file, normalimage))
  {
    return 0;
  }
  std::cout << "Running s3: " << directions_file << " " << image1_file << " " << image2_file << " " << image3_file
            << " " << step << " " << threshold << " " << normals_output_file << " "
            << " " << albedo_output_file << std::endl;
  return 0;
}
