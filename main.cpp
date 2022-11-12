#include "converter.h"


int main() {
    ConverterJSON*  convert = new ConverterJSON;
    std::vector<std::string>startCheck;
    try {
        startCheck = convert->Starting();
    }
    catch (std::exception& x) {
            std::cout << x.what() <<  std::endl;
            return 0;
        }

    std::cout  << startCheck[1] << " " << startCheck[2]  <<  " is started" << std::endl;
    std::cout << "Good luck with your project!";
    delete convert;
    return 0;
}