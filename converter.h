#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
//template to fill config
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


class ConverterJSON {
public:
    ConverterJSON() = default;

    static std::vector<std::string>Starting()
     {
        std::ifstream file("config.json");
         if(!file.is_open())
         {
             throw std::range_error("config file is missing");

         }
        nlohmann::json startControl;
        std::vector<std::string>startId;

            file >> startControl;

        auto it = startControl.begin();
        std::string  appConfig = it.key();
        std::string appName = startControl.at("config").at(1);
         if(appName == "")
         {
             throw std::exception();
         }
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
    std::vector<std::string> GetTextDocuments();
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
