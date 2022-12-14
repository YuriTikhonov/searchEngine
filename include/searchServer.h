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
    //SearchServer(InvertedIndex& idx) : _index(idx){ };
/**
* Метод обработки поисковых запросов
* @param queries_input поисковые запросы взятые из файла
requests.json
* @return возвращает отсортированный список релевантных ответов для
заданных запросов
*/
    std::vector<std::vector<RelativeIndex>> search(const std::string& queries_input)
    {
        std::vector<std::vector<RelativeIndex>> relativeIndex;
        //std::cout << queries_input  << " received from searchServer" <<  std::endl;
        std::unordered_set<std::string>st;
        std::vector<std::string>uniqueQueriesWords;
        std::istringstream inStream(queries_input);
        while (inStream) {
            std::string tempWord;
            inStream >> tempWord;
            st.insert(tempWord);
        }
        uniqueQueriesWords.insert(uniqueQueriesWords.end(),st.begin(),st.end());
        return relativeIndex;
    }

private:
    InvertedIndex _index;
};

#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H

#endif //SEARCHENGINE_SEARCHSERVER_H
