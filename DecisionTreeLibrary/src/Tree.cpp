#include "Tree.h"
#include <cmath>


float Tree::calculateEntropy(std::vector<attrInfoStruct> attributeStruct) const{
    int vectorLength = attributeStruct.size();
    int totalDecision = 0;
    std::unordered_map<std::string, float > totalAttributeDecisions; 
    std::unordered_map<std::string, float > totalDecisionNumbers; 
    for( int i = 0 ; i < vectorLength ; i++){

        for( auto x: attributeStruct[i].decInfo){
            totalDecision += x.second.size();
        }
        auto search = totalAttributeDecisions.find(attributeStruct[i].attributeName);

        int tmpDecNum = 0;
        for( auto x: attributeStruct[i].decInfo){
            tmpDecNum += x.second.size();
            auto searchDecision = totalDecisionNumbers.find(x.first);
            if(searchDecision != totalDecisionNumbers.end() ){
                int value = searchDecision->second + x.second.size();
                totalDecisionNumbers.insert_or_assign(x.first , value);
            }
            else
                totalDecisionNumbers.insert({x.first , x.second.size()});
        }
        if(search != totalAttributeDecisions.end()){
            int value = search->second + tmpDecNum; 
            totalAttributeDecisions.insert_or_assign(attributeStruct[i].attributeName, value );
        }
        else
            totalAttributeDecisions.insert({attributeStruct[i].attributeName, tmpDecNum}); 
    }
    float entropy = 0.;
    for( int i = 0 ; i < vectorLength ; i++){

        auto search = totalAttributeDecisions.find(attributeStruct[i].attributeName);
        float found =  (search->second ); 
        for( auto x: attributeStruct[i].decInfo) {
            int numberOcc = x.second.size();
            entropy -=(found / totalDecision) * ((numberOcc / found) * log2f((numberOcc / found))); 

        }
    }
    float information = 0.0;
    for( auto& iterator : totalDecisionNumbers){
        information -= (iterator.second/totalDecision)*log2f(iterator.second/totalDecision);
    }
    return information - entropy;
}



void Tree::loadData(std::string fileName) {
    DataMatrix readData;
    readData.loadData(fileName,attrObjs_);
    mixedCol_ = true;
}

void Tree::loadData(std::vector<std::vector<std::string> > &data){
    DataMatrix readData;
    readData.loadData(data,attrObjs_);
    mixedCol_ = false;
}

void Tree::eraseAttribute_(std::vector<int> rows) const{
    for(auto &x : attrObjs_){
        x->changeStruct(rows);
    }
}


bool Tree::checkLeaf_(std::shared_ptr<Node> root,std::string edgeName) const{
    int index=0;
    for(auto &x: root->getAttributeInfo()){
        if(x.attributeName == edgeName){
            if(x.decInfo.size()>1)
                return false;
            else{
                auto child = std::make_shared<Node>(x.decInfo.begin()->first,edgeName,true,x.decInfo.begin()->second);
                root->addChild(child);
                root->callDeleteStruct(index);
                eraseAttribute_(x.decInfo.begin()->second);
                return true;
            }
        }
        index++;
    }
    return false;
}

std::shared_ptr<Attribute> Tree::maxInformationGain_() const{
    float tmp = MINIMAL_COMPARE_VALUE;
    int index=0;
    for(auto &x: attrObjs_){
        if(x->getInformationGain() > tmp){
            tmp = x->getInformationGain();
            index = &x - &attrObjs_[0];
        }
        else if(x->getInformationGain() == tmp){
            if(attrObjs_[index]->getCntAttr() > attrObjs_[&x-&attrObjs_[0]]->getCntAttr())
                index = &x - &attrObjs_[0];
        }
    }
    return attrObjs_[index];
}


std::shared_ptr<Node> Tree::findRoot_(std::string parentName,std::string edge,std::vector<int> rows) const{
    std::vector<int> useCol;
    std::vector<std::shared_ptr<Attribute>> tmpAttrVec;
    if(mixedCol_)
        useCol = randomCol_(findParentIndex_(parentName));
    int it=0;
    if(parentName.empty())
        for(auto &x : attrObjs_){
            if((!checkCol_(useCol,it)) && mixedCol_)
                x->setInformationGain(-1);
            else
                x->setInformationGain(calculateEntropy(x->getAttributeSlave()));
            tmpAttrVec = attrObjs_;
            ++it;
        }
    else
    {
        for(auto &x : attrObjs_){
            tmpAttrVec.push_back(std::make_shared<Attribute>(x->getAttributeName(),newAttrVector_(rows,x)));
            if((!checkCol_(useCol,it)) && mixedCol_)
                x->setInformationGain(-1);
            else
                x->setInformationGain(calculateEntropy(tmpAttrVec[&x-&attrObjs_[0]]->getAttributeSlave()));
            ++it;
        }
    }
    auto attr = maxInformationGain_();
    auto attrName = attr->getAttributeName();
    auto node = std::make_shared<Node>(attrName,tmpAttrVec,0,edge);

    if(!parentName.empty())
        node->deleteColumn(node->findIndex(parentName));

    node->setIndex(node->findIndex(attrName));

    return node;
}

std::shared_ptr<Node> Tree::learnTree_(std::string parentName,std::string edge,std::vector<int> passRows) const{
    auto root = findRoot_(parentName,edge,passRows);
    for(auto const &x : root->getAttr()->getAttributeSlave()){
        bool check = checkLeaf_(root,x.attributeName);
        if(!check){
            auto rows  = root->getAttr()->searchAllRows(x.attributeName);
            root->addChild(learnTree_(root->getName(),x.attributeName,rows));
        }
    }
    return root;
}



std::vector<attrInfoStruct>  Tree::newAttrVector_(std::vector<int> rows,std::shared_ptr<Attribute> attr){
    std::vector<int> comm;
    attrInfoStruct tmpStruct{};
    std::vector<attrInfoStruct> tmpStructVector{};
    std::unordered_map<std::string,std::vector<int>> tmpMap;


    for(auto const &x : attr->getAttributeSlave()){
        for(auto y : x.decInfo){
            comm = intersection_(rows,y.second);
            if(!comm.empty()){
                tmpMap.emplace(y.first,comm);
            }
            comm.clear();
        }
        if(!tmpMap.empty()){
            tmpStruct.attributeName = x.attributeName;
            tmpStruct.decInfo = tmpMap;
            tmpStructVector.push_back(tmpStruct);
            tmpMap.clear();
        }
    }
    return tmpStructVector;
}


std::vector<int> Tree::intersection_(std::vector<int> &nums1, std::vector<int> &nums2){
    std::unordered_set<int> m(nums1.begin(), nums1.end());
    std::vector<int> res;
    for (auto a : nums2)
        if (m.count(a)){
            res.push_back(a);
            m.erase(a);
        }
    return res;
}


std::vector<int> Tree::randomCol_(int parentIndex ) const{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<int> values;
    int i = 0;
    for(auto &x : attrObjs_){
        if(i != parentIndex){
            values.push_back(i);
        }
        ++i;
    }
    std::shuffle(values.begin(), values.end(), std::default_random_engine(seed));
    i = sqrt(i);
    values.resize(i);
    return values;
}

bool Tree::checkCol_(std::vector<int> &columns, int &it) const{
    return find(columns.begin(), columns.end(),it) != columns.end();
}


int Tree::findParentIndex_(std::string parentName) const{
    int index = 0;
    for( auto const &x : attrObjs_){
        if(x->getAttributeName() == parentName){
            return index;
        }
        ++index;
    }
    return -1;
}

std::string Tree::getDecision(std::vector<std::string> &test){
    std::string dec = node_->getDecision(test,node_);
    return dec;
}

void Tree::getDecision(std::string fileName, std::vector<std::string> &result){
    std::ifstream file(fileName, std::ifstream::in);
    std::vector<std::vector<std::string>> tmpFile;
    if(file.good()){
        std::string token;
        std::string line;
        std::vector<std::string> vectorLine;
        while(getline(file,line)){
            std::stringstream cut(line);
            std::string tmp;
            while(getline(cut,tmp,',')){
                vectorLine.push_back(tmp);
            }
            tmpFile.push_back(vectorLine);
            vectorLine.clear();
        }
        file.close();
        for(auto &x : tmpFile){
            result.push_back(getDecision(x));
        }
    }
    else {
        perror("Error opening file");
        abort();
    }
}

std::vector<std::shared_ptr<Attribute> > Tree::getAttrVec() const{
    return attrObjs_;
}

void Tree::learn(){
    node_ = learnTree_("","",std::vector<int>());
}