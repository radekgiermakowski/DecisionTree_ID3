#include "Node.h"

std::vector<attrInfoStruct> Node::getAttributeInfo(){
    return getAttr()->getAttributeSlave();
}

void Node::addChild(std::shared_ptr<Node> child){
    child_.push_back(child);
}

void Node::callDeleteStruct(int index){
    getAttr()->deleteStruct(index);
}

std::string Node::getName() const{
    return name_;
}

std::shared_ptr<Attribute> Node::getAttr() const{
    auto attr = attr_[index_];
    return attr;
}


int Node::findIndex(std::string &attrName) const{
    int index = 0;

    for(auto const &x : attr_){
        if(x->getAttributeName() == attrName){
            break;
        }
        ++index;
    }
    return index;
}

int Node::nameToIndex(){
    size_t last_index = name_.find_last_not_of("0123456789");
    std::string result = name_.substr(last_index + 1);
    int index = std::atoi(result.c_str());
    return index;
}


void Node::deleteColumn(int index){
    if(!attr_.empty())
        attr_.erase(attr_.begin()+index);
}

void Node::setIndex(int index){
    index_ = index;
}

std::string Node::getDecision(std::vector<std::string> &test, std::shared_ptr<Node> &node) const{
    std::string result;
    if(node->leaf_ != 1){
        for(auto  &x : node->child_){
            if(x->edge_ == test[node->nameToIndex()-1]){
                result = getDecision(test , x);
            }
        }
    }
    else
        result = node->name_;
    return result;
}