#include "../include/invertedIndex.h"
#include "../include/converter.h"

int invertIndex(std::vector<std::string> &docs)
{
    InvertedIndex* invertedIndex = new InvertedIndex;

    for(auto it : docs)
    {
        std::istringstream docStream(it);
        while (docStream)
        {
            std::string tempWord;
            docStream >> tempWord;
            invertedIndex->getDocs(tempWord);
        }
    }
    //invertedIndex->showDocs();
    //
    Entry entry;

    entry = {1,1};
    invertedIndex->fillFreqDict(docs);
    invertedIndex->printMap();


    delete invertedIndex;
    return 0;
}