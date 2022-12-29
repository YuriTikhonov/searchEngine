#include "../include/invertedIndex.h"
#include "../include/converter.h"
#include "../include/searchServer.h"

std::mutex freqDictionaryAccess;

std::vector<Entry>  tempEntry{};
std::vector<std::vector<std::pair<int, float>>>answersVector;

InvertedIndex* invertedIndex = new InvertedIndex;

void textOperation(const std::string &inText, size_t n)
{
    std::string clearWord;
    std::istringstream docStream(inText);
    while (docStream) {
        std::string tempWord;
        docStream >> tempWord;
        clearWord = invertedIndex->prepareWord(tempWord);
        freqDictionaryAccess.lock();
        tempEntry = invertedIndex->GetWordCount(clearWord, n);
        freqDictionaryAccess.unlock();
        bool wordExist = false;
        bool entryExist = false;

        if (!tempEntry.empty()) {
            wordExist = true;
            freqDictionaryAccess.lock();
            for(auto it : tempEntry)
            {
                if(it.docId == n)
                {
                    entryExist = true;
                }
            }
            freqDictionaryAccess.unlock();
        }
        if(!entryExist)
        {
            freqDictionaryAccess.lock();
            tempEntry.push_back(Entry{n, 1});
            freqDictionaryAccess.unlock();
        }
        freqDictionaryAccess.lock();
        invertedIndex->fillFreqDict(tempEntry, wordExist, clearWord);
        freqDictionaryAccess.unlock();
    }
}

void UpdateDocumentBase(std::vector<std::string> &inTextDocs)
{
    unsigned int hardWareConcurrency = std::thread::hardware_concurrency();
    unsigned int threadNumbers = (inTextDocs.size() > hardWareConcurrency) ?  hardWareConcurrency: inTextDocs.size();
    unsigned int  blockSize = inTextDocs.size()/threadNumbers;
    std::cout << threadNumbers << " --- " << inTextDocs.size() << " --- " << blockSize << std::endl;

    size_t start = 0;

    std::thread* threads = new std::thread[threadNumbers];

    for(unsigned int i = 0;i < threadNumbers - 1;++i)
    {
        for(unsigned int j = start;j < (blockSize + start);++j)
        {
            if(!threads[i].joinable())
            {
                threads[i] = std::thread(textOperation, inTextDocs[j],j);
            }
            threads[i].join();
        }
        start += blockSize;

    }
    for(unsigned int j = start;j < inTextDocs.size();++j)
    {
        if(!threads[threadNumbers - 1].joinable())
            threads[threadNumbers - 1] = std::thread(textOperation, inTextDocs[j],j);
        threads[threadNumbers - 1].join();
    }
    SearchServer* searchServer = new SearchServer;
    auto dict = invertedIndex->getFreqDictionary();
    searchServer->getReadyDict(dict);
//-------------------------------------------
    std::vector<std::string>requestedWords;
    ConverterJSON* converterJson = new ConverterJSON;
    requestedWords = converterJson->GetRequests();
    unsigned int request_id = 0;
    for(auto at : requestedWords)
    {
        //std::cout << "this is requested word: " << at << " " << request_id << std::endl;
        auto result = searchServer->search(at,request_id);
        //searchServer->printWordFreq();

        if(result.size() == 0)
        {

            /*std::ofstream file_a("answers.json");
            nlohmann::json tempAnswers = {
                    {
                            "answers", {
                            request_id, {
                                    "result", "false"}
                    }
                    }
            };
            file_a << tempAnswers;
            file_a.close();*/
        }
        request_id++;
    }
    converterJson->putAnswers(answersVector);//????????????????
//---------------------------------------------
    delete converterJson;
    delete invertedIndex;
    delete searchServer;
}