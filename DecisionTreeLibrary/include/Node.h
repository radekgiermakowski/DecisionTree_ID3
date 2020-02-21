#ifndef PROJECT_MENAGER_NODE_H
#define PROJECT_MENAGER_NODE_H

#include "ReadFile.h"

class Node{
public:
    Node(std::string name, std::vector<std::shared_ptr<Attribute>> attr, int index,std::string edge):
        name_(name),attr_(attr),index_(index),edge_(edge){};

    Node(std::string name,std::string edge,bool leaf,std::vector<int> deleteRows):
        name_(name),edge_(edge),leaf_(leaf),deleteRows_(deleteRows){};

    ~Node()= default;

    int findIndex(std::string &attrName) const;
    void deleteColumn(int index);

    [[nodiscard]] std::string getName() const;
    std::vector<attrInfoStruct> getAttributeInfo();
    void addChild(std::shared_ptr<Node> child);
    void callDeleteStruct(int index);
    [[nodiscard]] std::shared_ptr<Attribute> getAttr() const;
    void setIndex(int index);
    std::string getDecision(std::vector<std::string> &test, std::shared_ptr<Node> &node) const;
    int nameToIndex();


private:
    std::string name_;
    std::vector<std::shared_ptr<Node>> child_;
    std::vector<std::shared_ptr<Attribute>> attr_;
    int index_;
    std::string edge_;
    bool leaf_;
    std::vector<int> deleteRows_;
};
#endif
