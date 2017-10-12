#include <boost/program_options.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include "../color_transfer/color_transfer.hpp" 

namespace po = boost::program_options;
using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
    string source, target, path;

    po::options_description description("Allowed options");
    auto&& options = description.add_options();
    options("help,", "show available options");
    options("scr,s", po::value<string>(&source), "source image");
    options("tar,t", po::value<string>(&target), "target image");
    options("path,p", po::value<string>(&path)->default_value("NULL"), "path to save");
    
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);
    po::notify(vm);
  
    if (vm.count("help") || !vm.count("scr") || !vm.count("tar")) {
      cout << description << endl;
      return 1;
    }

    Mat image = imread(source);
    Mat image2 = imread(target);
    Mat result = colorTransfer(image.clone(), image2.clone());
    
    imshow("Result", result);
    waitKey(0);

    // Save the output
    if (path != "NULL") {
      try {
        imwrite(path, result);        
      }
      catch(...) {
        cout << "Invalid path or image type" << endl;
      }
    }

    return 0;
}