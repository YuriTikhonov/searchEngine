#include "converter.h"
#include <iostream>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

struct Start
{
    std::string checkConfig;
    std::string checkVersion;
};

int main() {
    Start start;
    //
  /*  std::ofstream file("..//config.json");
    nlohmann::json temp = {
            {"config", {
                "name", "SearchEngine",
                        "version", "0.1",
                        "max_responses", 5
            }},
            { "files", {
            "../resources/file001.txt",
            "../resources/file002.txt",
            "../resources/file003.txt",
             "../resources/file004.txt"

            }}
    };




    file << temp;
    file.close();*/
    //
    std::ifstream file("..//config.json");
    nlohmann::json startControl;
    file >> startControl;

    std::cout << startControl.at("config").at(1) << std::endl;

    std::cout << startControl.at("config").at(3) << std::endl;


    std::cout << startControl.at("config").at(5) << std::endl;

std::cout << "Good luck with your project!";
    return 0;
}