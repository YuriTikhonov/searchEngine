#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>

struct Entry
{
    size_t docId, count;
    bool operator == (const Entry& other) const {
        return (docId == other.docId &&
                count == other.count);
    }
};

class InvertedIndex
{
public:
    InvertedIndex() = default;

    void UpdateDocumentBase(std::vector<std::string> inputDocs);

    std::vector<Entry> GetWordCount(const std::string& word);

    void getDocs(std::string &tempWord)
    {
        docs.push_back(tempWord);
    }
    void showDocs()
    {
        for(int i = 0;i < docs.size();++i)
        {
            std::cout << docs[i] << " - " << i << std::endl;
        }
    }

    void inputDataToDict(Entry &inEnty)
    {

        toEntry.push_back(inEnty);

    }
    std::vector<Entry> getEntryData()
    {
        return toEntry;
    }

    void fillFreqDict(std::vector<std::string> &inDocsText)
    {
        std::vector<Entry> getEntry;
        size_t counter = 0;
        size_t indexCount = 1;
        Entry entry = {counter,indexCount};
        for(size_t i = 0;i < inDocsText.size();++i)
        {
            for(int j = 0;j < docs.size();++j)
            {
                bool entryFound = false;
                 bool wordFound = freqDictionary.find(docs[j]) != freqDictionary.end();
              /*if(!wordFound)
                {

                    auto iterator = toEntry.insert(toEntry.begin(), {i,1});

                }
                else */
                    if(wordFound)
               {
                   ++indexCount;

                   toEntry.push_back({i,indexCount});
               }
                freqDictionary.try_emplace(docs[i],toEntry);
                std::cout << docs[j] << " - " << i << " word found? "<< wordFound <<  std::endl;

                //std::cout  << " .... " << wordFound << std::endl;
            }


            counter++;
        }
        ;
        //toEntry.clear();

    }

    void printMap()
    {int k = 0;
        for(auto it: freqDictionary)
        {
            std::cout  << it.first << " :";
            for(auto its : it.second)
                std::cout <<"{" << its.docId <<" - " << its.count << "}";
            std::cout << std::endl;
            ++k;

        }
    }

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;
    std::vector<Entry> toEntry;
};
int invertIndex(std::vector<std::string> &docs);
#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H
#endif //SEARCHENGINE_INVERTEDINDEX_H
