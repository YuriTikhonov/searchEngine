#include "../include/invertedIndex.h"
#include <sstream>
#include <unordered_set>
#include <algorithm>

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

    int requestNumber = 0;
    std::vector<std::vector<RelativeIndex>> search(const std::string& queriesInput, unsigned int inRequestId)
    {
        std::vector<std::vector<RelativeIndex>> relativeIndex;
        std::unordered_set<std::string>st;
        std::istringstream inStream(queriesInput);

        if(inRequestId != 0)
        {
            while (inStream) {
                std::string tempWord;
                inStream >> tempWord;
                st.insert(tempWord);
            }
        }
        int countedWords = 0;
        std::unordered_set<std::string> :: iterator itr;
        for (itr = st.begin(); itr != st.end(); itr++)
        {
            for(auto it: readyDictionary)
            {
                if(*itr == it.first)
                {
                    countedWords = 0;
                    std::cout  << it.first << " :";
                    for(auto its : it.second)
                    {
                        std::cout <<"{" << its.docId <<" ," << its.count << "}, ";
                        countedWords += its.count;
                    }
                    requestedWordFreq.insert(std::make_pair(it.first,countedWords));
                    std::cout << std::endl;
                    requestedWordFound = true;
               }else{
                    requestedWordFound = false;
                    relativeIndex = {};
                }
            }
    }
        std::copy(requestedWordFreq.begin(),
                  requestedWordFreq.end(),
                  std::back_inserter<std::vector<pair>>(vec));

        std::sort(vec.begin(),vec.end(),
                  [](const pair &l, const pair &r)
                  {
                    if(l.second != r.second){
                        return l.second < r.second;
                    }
                      return l.first < r.first;
                  });
        for (auto const &pair: vec) {
            std::cout << '{' << pair.first << "," << pair.second << '}' << std::endl;
        }


        requestNumber++;
        vec = {};
        requestedWordFreq = {};
        sortedRequestsWords = {};
        std::cout << std::endl << "__________________"  << std::endl;

        return relativeIndex;
    }
    /*
    void printWordFreq()
    {
        for(auto it : sortedRequestsWords)
     {
         //std::cout << it.reqWord << " " << it.frequency << " " << std::endl;
     }
    }
*/

private:
    std::map<std::string, std::vector<Entry>> readyDictionary;
    bool requestedWordFound = false;
    std::map<std::string,int>requestedWordFreq;
    std::vector<std::string>sortedRequestsWords;
    typedef std::pair<std::string,int> pair;
    std::vector<pair> vec;
};

#ifndef SEARCHENGINE_SEARCHSERVER_H
#define SEARCHENGINE_SEARCHSERVER_H
#endif //SEARCHENGINE_SEARCHSERVER_H
