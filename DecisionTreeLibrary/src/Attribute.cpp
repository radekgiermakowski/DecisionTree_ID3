#include "Attribute.h"


std::vector<attrInfoStruct> Attribute::getAttributeSlave() const{
    return slaveAttribute_;
}

void Attribute::setInformationGain(float informationGain){
    informationGain_ = informationGain;
}

float Attribute::getInformationGain() const{
    return informationGain_;
}

std::string Attribute::getAttributeName() const{
    return colAttrName_;
}

void Attribute::changeStruct(std::vector<int> rows){
    std::vector<int> tmp;
    std::vector<std::string> eraseName;
    std::vector<int> indexEmptyStruct;
    int itr=0;
    for(auto &str: slaveAttribute_){
        for(auto &x : str.decInfo){
            auto it = std::set_intersection(rows.begin(),rows.end(),x.second.begin(),x.second.end(), std::back_inserter(tmp));

            for(auto inVec : tmp){
                x.second.erase(std::remove(x.second.begin(), x.second.end(), inVec), x.second.end());
            }
            if(x.second.empty())
                eraseName.push_back(x.first);
        }
        for(auto const &x : eraseName)
            str.decInfo.erase(x);
        eraseName.clear();
        if(str.decInfo.empty())
            indexEmptyStruct.push_back(&str-&slaveAttribute_[0]);
    }
    for(auto erase : indexEmptyStruct)
        slaveAttribute_.erase(slaveAttribute_.begin()+ erase);


}

int Attribute::getCntAttr() const{
    std::unordered_map<std::string,int> tmpMap;
    for(auto const &x : slaveAttribute_){
        auto it = tmpMap.find(x.attributeName);
        if( it == tmpMap.end()){
            std::pair<std::string,int> tmp(x.attributeName,1);
            tmpMap.insert(tmp);
        } else
            it->second += 1;
    }
    return tmpMap.size();
}

void Attribute::deleteStruct(int index){
    auto it = slaveAttribute_.begin();
    slaveAttribute_.erase(it+index);
}

std::vector<int> Attribute::searchAllRows(std::string attrName){
    std::vector<int> allRows;
    for (auto const &x: slaveAttribute_){
        if (x.attributeName == attrName)
            for (auto const &y: x.decInfo){
                for (auto z : y.second)
                    allRows.push_back(z);
            }
    }
    return allRows;
}