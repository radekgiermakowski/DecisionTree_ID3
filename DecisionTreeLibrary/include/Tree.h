#ifndef PROJECT_MENAGER_TREE_H
#define PROJECT_MENAGER_TREE_H

#include "Node.h"

static const int MINIMAL_COMPARE_VALUE = -2;

class Tree{
public:
    Tree()= default;
    ~Tree()= default;

    void loadData(std::string fileName);
    void loadData(std::vector<std::vector<std::string>> &data);
    [[nodiscard]] float calculateEntropy(std::vector<attrInfoStruct> attributeStruct) const;
    std::string getDecision(std::vector<std::string> &test);
    void getDecision(std::string fileName,  std::vector<std::string> &result);
    [[nodiscard]] std::vector<std::shared_ptr<Attribute>> getAttrVec() const;
    void learn();

private:
    [[nodiscard]] bool checkLeaf_(std::shared_ptr<Node> root,std::string edgeName) const;
    void eraseAttribute_(std::vector<int> rows) const;
    static std::vector<attrInfoStruct> newAttrVector_(std::vector<int> rows,std::shared_ptr<Attribute> attr);
    static std::vector<int> intersection_(std::vector<int> &nums1, std::vector<int> &nums2);
    [[nodiscard]] std::shared_ptr<Attribute> maxInformationGain_() const;
    [[nodiscard]] std::vector<int> randomCol_(int parentIndex) const;
    bool checkCol_(std::vector<int> &columns,int &it) const;
    [[nodiscard]] int findParentIndex_(std::string parentName) const;
    [[nodiscard]] std::shared_ptr<Node> findRoot_(std::string parentName,std::string edge,std::vector<int> rows) const;
    [[nodiscard]] std::shared_ptr<Node> learnTree_(std::string parentName,std::string edge,std::vector<int> rows) const;

private:
    std::vector<std::shared_ptr<Attribute>> attrObjs_{};
    std::shared_ptr<Node> node_{};
    bool mixedCol_ = false;
};

#endif