#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <nlohmann/json.hpp>

class ConverterJSON {
    std::vector<std::string>startId;
    std::vector<std::string>requests;
    int responsesLimit;
  public:
    ConverterJSON() = default;

     std::vector<std::string>startApp()
     {
        std::ifstream file("config.json");
         if(!file.is_open())
         {
             throw std::range_error("config file is missing");
         }
        nlohmann::json startControl;
        file >> startControl;

        auto it = startControl.begin();
        std::string  appConfig = it.key();
        std::string appName = startControl.at("config").at(1);
        std::string versionNumber = startControl.at("config").at(3);
        responsesLimit = startControl.at("config").at(5);
        startId.push_back(appConfig);
        startId.push_back(appName);
        startId.push_back(versionNumber);
        file.close();
        return startId;
     }

     std::vector<std::string> GetTextDocuments(std::vector<std::string> &textDocuments)
        {
            auto recursiveGetFilePathsByExtension =
                    [&textDocuments](std::filesystem::path path,
                       const std::string extension)
                    {
                        for(auto& p: std::filesystem::recursive_directory_iterator(path))
                        {
                            if(is_regular_file(p.path()))
                            {
                                if(p.path().extension().compare(extension))
                                {
                                   std::ifstream file(p.path(), std::ios::in | std::ios::binary);

                                   if(!file.is_open())
                                    {
                                        throw std::range_error("source file is missing");
                                    }
                                   const auto sz = std::filesystem::file_size(p.path());
                                   std::string content(sz, '\0');
                                   file.read(content.data(), sz);
                                   textDocuments.push_back(content);
                                }
                            }
                        }
                    };
            recursiveGetFilePathsByExtension("C:\\Users\\user\\CLionProjects\\FinalProject\\searchEngine\\cmake-build-debug\\resources","txt");
            return textDocuments;
        };

    int GetResponsesLimit()
    {
        return responsesLimit;
    }

    std::vector<std::string> GetRequests()
    {
        std::ifstream file("request.json");
        if(!file.is_open())
        {
            throw std::range_error("request file is missing");
        }
        nlohmann::json requestFileOperation;
        file >> requestFileOperation;

        for (auto it = requestFileOperation.begin(); it != requestFileOperation.end(); ++it)
        {
            for(auto valueIterator = it.value().begin();valueIterator != it.value().end(); ++valueIterator)
            {
                requests.push_back(*valueIterator);
            }
        }
        file.close();
        return requests;
    }
/*
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>
    answers);
};



#ifndef SEARCHENGINE_CONVERTER_H
#define SEARCHENGINE_CONVERTER_H

#endif //SEARCHENGINE_CONVERTER_H
