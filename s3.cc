// Program 3 - HW4
// Author: <YOUR NAME>

#include "image.h"
#include <string>
#include <iostream>

using namespace ComputerVisionProjects;

int main(int argc, char **argv) {
    if (argc != 9) {
      std::cout << "Usage: " << argv[0] <<
        " {input-directions-file} {image1} {image2} {image3} {step} {threshold} {normals-output-file} {albedo-output-file}"
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

    std::cout << "Running s3: " << directions_file << " " << image1_file <<  " " << image2_file << " " << image3_file
              << " " << step << " " << threshold << " " << normals_output_file << " "
              <<  " " << albedo_output_file << std::endl;
    return 0;
}
