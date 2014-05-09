/*
 * Compute local image SNR using ground truth SOACs.
 */

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <boost/filesystem.hpp>
#include "multisnake.h"


std::string GetSuffix(const std::string &s) {
  return s.substr(s.size()-3);
}

int main(int argc, char **argv) {
  if (argc < 5) {
    std::cerr << "Usage: ./snr <image_dir> <snake_path> "
        "<radial_near> <radial_far>" << std::endl;
    return EXIT_FAILURE;
  }

  namespace fs = boost::filesystem;
  fs::path image_dir(argv[1]);

  try {
    if (fs::exists(image_dir)) {
      soax::Multisnake multisnake;
      // fs::directory_iterator end_it;
      // for (fs::directory_iterator it(image_dir); it != end_it; ++it) {
      //   multisnake.LoadImage(it->path().string());
      //   double snr = multisnake.ComputeImageSNR();
      //   std::cout << it->path().filename() << " SNR: " << snr << std::endl;
      // }
      int rnear = atoi(argv[3]);
      int rfar = atoi(argv[4]);
      if (fs::is_regular_file(image_dir)) {
        if (GetSuffix(image_dir.string()) == "mha" ||
            GetSuffix(image_dir.string()) == "tif") {
          multisnake.LoadImage(image_dir.string());
          multisnake.LoadGroundTruthSnakes(argv[2]);
          std::cout << multisnake.GetNumberOfComparingSnakes1()
                    << " ground truth snakes loaded." << std::endl;

          // double snr1 = multisnake.ComputeImageSNR("binary.mha");
          // std::cout << image_dir.filename() << " old SNR: "
          //           << snr1 << std::endl;
          // double snr2 = multisnake.ComputeImageSNR2("ternary.mha");
          // if (snr < 4.5 && snr > 3.5)
          // std::cout << image_dir.filename() << " new SNR: "
          //           << snr2 << std::endl;
          multisnake.PrintGroundTruthLocalSNRValues(rnear, rfar);
        }
      } else { // directory
        typedef std::vector<fs::path> Paths;
        Paths image_paths;
        std::copy(fs::directory_iterator(image_dir), fs::directory_iterator(),
                  back_inserter(image_paths));
        std::sort(image_paths.begin(), image_paths.end());
        for (Paths::const_iterator it(image_paths.begin());
             it != image_paths.end(); ++it) {
          if (GetSuffix(it->string()) == "mha" ||
              GetSuffix(it->string()) == "tif") {
            multisnake.LoadImage(it->string());
            std::cout << it->string() << std::endl;
            multisnake.LoadGroundTruthSnakes(argv[2]);
            std::cout << multisnake.GetNumberOfComparingSnakes1()
                      << " ground truth snakes loaded." << std::endl;

            // double snr = multisnake.ComputeImageSNR2();
            // if (snr < 4.5 && snr > 3.5)
            // std::cout << it->filename() << " SNR: " << snr << std::endl;
            multisnake.PrintGroundTruthLocalSNRValues(rnear, rfar);
            std::cout << std::endl;
          }
        }
      }
    } else {
      std::cout << image_dir << " does not exist." << std::endl;
    }
  } catch (const fs::filesystem_error &e) {
    std::cout << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
