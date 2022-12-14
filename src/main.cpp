#include "../include/converter.h"
#include "../include/invertedIndex.h"
#include "../include/searchServer.h"
#include <unordered_set>

int main() {
    std::string searchRequest;
    std::vector<std::string> searchRequests;
    std::vector<std::vector<std::pair<int, float>>>answersVector;
    auto  converter = new ConverterJSON;
    auto invIndex = new InvertedIndex;
    auto searchServer = new SearchServer;

    std::vector<std::string>startCheck;
    std::vector<std::string>textDocument;
    std::vector<std::string>requestedWords;

    try {
        startCheck = converter->startApp();
    }
    catch (std::exception& x) {
        std::cout << x.what() <<  std::endl;
        return 0;
    }
    std::cout  << startCheck[1] << " " << startCheck[2]  <<  " is started" << std::endl;

    try
    {
        textDocument = converter->GetTextDocuments(textDocument);
    }
    catch (std::exception& x) {
        std::cout << x.what() <<  std::endl;
        return 0;
    }

    int responsesLimit = converter->GetResponsesLimit();
    std::cout  << textDocument.size() << " docs are loaded, responses limit is: "
               << responsesLimit << std::endl;

    converter->putAnswers(answersVector);

    UpdateDocumentBase(textDocument);
    int j = 0;
    while (searchRequest != "-1")
    {
        std::cout << "Enter search request or -1 to exit: " << std::endl;
        std::getline(std::cin, searchRequest);
        if(searchRequest != "-1")
            searchRequests.push_back(searchRequest);
        ++j;
    }
    std::ofstream file("request.json");
    nlohmann::json tempRequest = {"requests:",searchRequests};
    file << tempRequest;
    file.close();

    requestedWords = converter->GetRequests();
    for(auto at : requestedWords)
    {
        searchServer->search(at);
    }

    std::cout << "Good luck with your project!";
    delete converter;
    delete invIndex;
    delete searchServer;
    return 0;
}