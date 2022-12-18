#pragma once
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iterator>
#include <thread>
#include <mutex>
#include <algorithm>

struct Entry
{
    size_t docId = 0, count = 0;
    bool operator == (const Entry& other) const {
        return (docId == other.docId &&
                count == other.count);
    }
};

class InvertedIndex
{
public:
    std::mutex freqDictionaryAccess;

    InvertedIndex() = default;

    std::string prepareWord(std::string &inWord)
    {
        std::string result;
        std::remove_copy_if(inWord.begin(), inWord.end(),
                            std::back_inserter(result),
                            std::ptr_fun<int, int>(&std::ispunct)
        );
        std::string lowerWord;
        for(int i = 0;i < result.size();++i)
        {
            if ((result[i] >= 'a' && result[i] <= 'z') || (result[i] >= 'A' && result[i] <= 'Z'))

                lowerWord += tolower(result[i]);
        }
        return lowerWord;
    }

    // void UpdateDocumentBase(std::vector<std::string> inputDocs);

    //std::vector<Entry> GetWordCount(const std::string& word, size_t &n)
    std::vector<Entry> GetWordCount( std::string& word, size_t &n)
    {
        if(freqDictionary.count(word)) {
            for (size_t i = 0; i < freqDictionary.at(word).size(); ++i) {
                if (freqDictionary.at(word)[i].docId == n) {
                    freqDictionary.at(word)[i].count++;
                }
            }
            return freqDictionary.at(word);
        }
        else
        {
            return std::vector<Entry>{};
        }
    }

    //void fillFreqDict(std::vector<Entry> &inEntry, bool wordFound, const std::string &currentWord)
    void fillFreqDict(std::vector<Entry> &inEntry, bool wordFound,  std::string &currentWord)
    {
        if(!wordFound && !currentWord.empty() && currentWord != "\r")
        {
            freqDictionary.insert(std::make_pair(currentWord,inEntry));
        }else if(!currentWord.empty() && currentWord != "\r")
        {
            freqDictionary.at(currentWord) = inEntry;
        }
    }
    std::map<std::string, std::vector<Entry>> getFreqDictionary()
            {
                return freqDictionary;
            };

    void printMap()
    {
        for(auto it: freqDictionary)
        {
            std::cout  << it.first << " :";
            for(auto its : it.second)
                std::cout <<"{" << its.docId <<" ," << its.count << "}";
            std::cout << std::endl;
        }
    }


private:
    std::map<std::string, std::vector<Entry>> freqDictionary;
};

void UpdateDocumentBase( std::vector<std::string> &docs);
#ifndef SEARCHENGINE_INVERTEDINDEX_H
#define SEARCHENGINE_INVERTEDINDEX_H
#endif //SEARCHENGINE_INVERTEDINDEX_H
