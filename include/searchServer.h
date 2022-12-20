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
   void getReadyDict(std::map<std::string, std::vector<Entry>> &dict)
            {
                for(auto it: dict)
                {
                    std::vector<Entry>v;
                    for(auto its : it.second)
                    {
                        v.push_back({its.docId,its.count});
                    }
                    readyDictionary.insert(std::make_pair(it.first,v));
                }

            }
/*
    void printDictionary()
    {
        for(auto it: readyDictionary)
        {
            std::cout  << it.first << " :";
            for(auto its : it.second)
            {

                std::cout <<"{" << its.docId <<" :" << its.count << "}";
                std::cout << std::endl;

            }
        }
    }
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

        std::unordered_set<std::string> :: iterator itr;
        for (itr = st.begin(); itr != st.end(); itr++)
        {
           std::cout << *itr << " " << requestNumber << std::endl;
            for(auto it: readyDictionary)
            {
                if(*itr == it.first)
                {
                    for(auto its : it.second)
                    {
                        std::cout  << it.first << " :";
                        std::cout <<"{" << its.docId <<" ," << its.count << "}";
                        std::cout << std::endl;
                    }
               }
            }
        }
        requestNumber++;
        std::cout << "__________________"  << std::endl;

        return relativeIndex;
    }

private:
    std::map<std::string, std::vector<Entry>> readyDictionary;
};

#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H

#endif //SEARCHENGINE_SEARCHSERVER_H
