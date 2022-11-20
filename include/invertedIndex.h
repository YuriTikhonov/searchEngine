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
        for(auto it :docs)
        {
            std::cout << it << std::endl;
        }
    }

    void fillFreqDict()
    {

    }

private:
    std::vector<std::string> docs;
    std::map<std::string, std::vector<Entry>> freqDictionary;
};
int invertIndex(std::vector<std::string> &docs);
#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H
#endif //SEARCHENGINE_INVERTEDINDEX_H
