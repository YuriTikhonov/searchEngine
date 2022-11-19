#include "../include/converter.h"

int main() {

    std::vector<std::string>textDocumentsPaths;
    std::vector<std::vector<std::pair<int, float>>>answersVector;
    /*
    std::ofstream file("config.json");
    nlohmann::json temp = {
            {"config", {
                               "name", "SearchEngine",
                               "version", "0.1",
                               "maxResponses", 5
                       }},
            { "files", {
                               "../resources/file001.txt",
                                       "../resources/file002.txt",
                               "../resources/file003.txt",
                                          "../resources/file004.txt"

                       }}
    };
    file << temp;
    file.close();


     std::ofstream file("request.json");
    nlohmann::json tempRequest = {
     {
"requests", {
             "some words..",
             "some words..",
             "some words..",
             "some words.."
     }
}
     };
     file << tempRequest;
    file.close();


 std::ofstream file("answers.json");
    nlohmann::json tempAnswers = {
 {
"answers", {
"request001", {
"result", "true",
"relevance", {
"docid", 0, "rank", 0.989,
"docid", 1, "rank" , 0.897,
"docid", 2, "rank" , 0.750,
"docid", 3, "rank" , 0.670,
"docid", 4, "rank" , 0.561
}
},
"request002", {
"result", "true",
"docid", 0, "rank" , 0.769
},
"request003", {
"result", "false"}
}
}
};
 file << tempAnswers;
    file.close();
*/
    //--------------------------------

    auto  converter = new ConverterJSON;

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
    std::cout  << textDocument.size() << " docs are loaded, responses limit is: " << responsesLimit << std::endl;
    requestedWords = converter->GetRequests();

    for(auto at : requestedWords)
     {
        std::cout << at << std::endl;
     }
    converter->putAnswers(answersVector);
    std::cout << "Good luck with your project!";
    delete converter;
    return 0;
}
