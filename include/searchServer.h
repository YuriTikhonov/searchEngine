#include "../include/invertedIndex.h"
#include <sstream>
#include <unordered_set>

struct RelativeIndex{
    size_t doc_id;
    float rank;
    bool operator ==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};
class SearchServer {
public:
/**
* @param idx в конструктор класса передаётся ссылка на класс
InvertedIndex,
* чтобы SearchServer мог узнать частоту слов встречаемых в
запросе
*/
    std::map<std::string, std::vector<Entry>> inFreqDict;
   InvertedIndex* idxSearch = new InvertedIndex;
   void printMapSs(std::map<std::string, std::vector<Entry>>& dict)
            {
                    for(auto it: dict)
                {
                    std::cout  << it.first << " :";
                    for(auto its : it.second)
                        std::cout <<"{" << its.docId <<" ," << its.count << "}";
                    std::cout << std::endl;
                }
            }

/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    int requestNumber = 0;
    std::vector<std::vector<RelativeIndex>> search(const std::string& queries_input, unsigned int inRequestId)
    {
        std::vector<std::vector<RelativeIndex>> relativeIndex;
        std::unordered_set<std::string>st;
        std::istringstream inStream(queries_input);

        if(inRequestId != 0)
        {
            while (inStream) {
                std::string tempWord;
                inStream >> tempWord;
                st.insert(tempWord);
            }
        }
         inFreqDict = idxSearch-> getFreqDictionary();

        std::unordered_set<std::string> :: iterator itr;
        for (itr = st.begin(); itr != st.end(); itr++)
        {
           std::cout << *itr << " " << requestNumber << std::endl;//список уникальных слов в каждом запросе
           //необходимо отсортировать по По возрастанию значения поля count поля
            //freq_dictionary.



        }
        requestNumber++;
        std::cout << "__________________"  << std::endl;

        //delete idxSearch;
        return relativeIndex;
    }

private:
    InvertedIndex _index;
};

#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H

#endif //SEARCHENGINE_SEARCHSERVER_H
