#ifndef PROJECT_MENAGER_RANDOMFOREST_H
#define PROJECT_MENAGER_RANDOMFOREST_H
#include "Tree.h"
#include <utility>
#include <mutex>
#include <optional>
#include <functional>
#include <boost/optional.hpp>
#include <boost/algorithm/string.hpp>
#include <chrono>


class Forest{
public:

    explicit Forest(size_t numberTrees):
            numberTree_(numberTrees){};

    ~Forest()= default;

    void loadData(std::string fileName, std::vector<std::vector<std::string>> *vec = nullptr);
    void buildTree();
    void checkForestAccuracy(std::string learnFile , std::string testFile);
    std::vector<std::string> getDecision(std::vector<std::vector<std::string>> &testVectors);

private:

    void splitData_(std::vector<std::vector<std::string>> &allData);
    std::vector<int> randomRows_(int range);
    void buildTree_(std::vector<std::vector<std::string>> &data);
    std::vector<std::vector<std::string>> returnData_();
    static void separateTestDecisions_(std::vector<std::string> & decision, std::vector<std::vector<std::string>> &testVector , std::vector<std::vector<std::string>> inputData);

private:
    const int numberTree_{};
    std::vector<std::vector<std::vector<std::string>>> sortData_{};
    int indexData_{};
    std::mutex mutex_;
    std::vector<std::shared_ptr<Tree>> tree_;
};

#endif //PROJECT_MENAGER_RANDOMFOREST_H
