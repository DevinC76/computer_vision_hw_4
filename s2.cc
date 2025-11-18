// Program 2 - HW4
// Author: <YOUR NAME>

#include "image.h"
#include <string>
#include <iostream>

using namespace ComputerVisionProjects;

int main(int argc, char **argv) {
    if (argc != 6) {
      std::cout << "Usage: " << argv[0] <<
        " {input-parameters-file} {sphere-image-1} {sphere-image-2} {sphere-image-3} {output-directions-file}" 
                << std::endl;
      return 0;
    }

    const std::string parameters_file(argv[1]);
    const std::string sphere_image1(argv[2]);
    const std::string sphere_image2(argv[3]);
    const std::string sphere_image3(argv[4]);
    const std::string output_directions_file(argv[5]);

    std::cout << "Running s2 " << parameters_file << " " << sphere_image1 << " " << sphere_image2
              << " " << sphere_image3 << " " << output_directions_file << std::endl;
    return 0;
}
