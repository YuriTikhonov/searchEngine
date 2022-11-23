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

    void fillFreqDict(std::vector<std::string> &inDocsText)
    {
        std::vector<Entry> toEntry;
        size_t counter = 0;
        size_t indexCount = 0;
        Entry entry = {counter,indexCount};
        for(int i = 0;i < inDocsText.size();++i)
        {

            for(int j = 0;j < docs.size();++j)
            {
                bool entryFound = false;
                 bool wordFound = freqDictionary.find(docs[j]) != freqDictionary.end();
                //std::cout << counter << " ||| " << std::endl;
               if(!wordFound)
                {
                    entry = {counter,1};
                }
                std::cout << docs[j] << " - " << i << " word found? "<< wordFound <<  std::endl;
                toEntry.push_back(entry);
                freqDictionary.try_emplace(docs[j],toEntry);

                //std::cout  << " .... " << wordFound << std::endl;
            }
            counter++;
        }
    }
    /*
     * for (auto &word: words) {
        bool entryIsFind = false;
        bool wordIsFind = freqDictionary.find(word) != freqDictionary.end();

        if (wordIsFind) {
            if (freqDictionary[word].find(docId) != freqDictionary[word].end()) {
                ++freqDictionary[word][docId];
                entryIsFind = true;
            }
        }

        if (!wordIsFind || !entryIsFind)
            freqDictionary[word][docId] = 1;
    }
}
     */
    void printMap()
    {int i = 0;
        for(auto it: freqDictionary)
        {
            //std::cout <<it.first <<" -- " <<  it.second[i].docId << " - " << it.second[i].count << std::endl;

            i++;
        }
    }

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;
};
int invertIndex(std::vector<std::string> &docs);
#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H
#endif //SEARCHENGINE_INVERTEDINDEX_H
