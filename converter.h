#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <regex>
#include <nlohmann/json.hpp>


class ConverterJSON {
    std::vector<std::string>startId;
   // std::vector<std::string>textDocuments;
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

        startId.push_back(appConfig);
        startId.push_back(appName);
        startId.push_back(versionNumber);

        file.close();
        return startId;
     }

        /*
 * Метод получения содержимого файлов
 * @return Возвращает список с содержимым файлов перечисленных
 * в config.json
 */
    std::vector<std::string> GetTextDocuments(std::vector<std::string> &textDocuments)
        {
            auto recursiveGetFileNamesByExtension =
                    [&textDocuments](std::filesystem::path path,
                       const std::string extension)
                    {
                        for(auto& p: std::filesystem::recursive_directory_iterator(path))
                        {
                            if(is_regular_file(p.path()))
                            {
                                if(p.path().extension().compare(extension))
                                {
                                    std::ifstream file(p.path());
                                    if(!file.is_open())
                                    {
                                        throw std::range_error("source file is missing");
                                    }
                                    std::string content;
                                    file >> content;
                                    textDocuments.push_back(content);
                                }
                            }
                        }
                    };
            recursiveGetFileNamesByExtension("C:\\Users\\user\\CLionProjects\\FinalProject\\searchEngine\\cmake-build-debug\\resources","txt");
            return textDocuments;
        };
/*
* Метод считывает поле max_responses для определения предельного
* количества ответов на один запрос
* @return
*/
    int GetResponsesLimit();
/*
* Метод получения запросов из файла requests.json
* @return возвращает список запросов из файла requests.json
*/
    std::vector<std::string> GetRequests();
/*
* Положить в файл answers.json результаты поисковых запросов
*/
    void putAnswers(std::vector<std::vector<std::pair<int, float>>>
    answers);
};



#ifndef SEARCHENGINE_CONVERTER_H
#define SEARCHENGINE_CONVERTER_H

#endif //SEARCHENGINE_CONVERTER_H
