#ifndef PROJECT_MENAGER_ATTRIBUTE_H
#define PROJECT_MENAGER_ATTRIBUTE_H


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <unordered_map>
#include <memory>
#include <regex>
#include <algorithm>
#include <bits/stdc++.h>
#include <random>
#include <chrono>

struct attrInfoStruct
{
    std::string attributeName;
    std::unordered_map<std::string,std::vector<int>> decInfo;
};

class Attribute{
public:
    Attribute(const std::string colAttrName,std::vector<attrInfoStruct> slaveAttribute):
            colAttrName_(colAttrName),slaveAttribute_(slaveAttribute){};
    ~Attribute()= default;

    [[nodiscard]] std::vector<attrInfoStruct> getAttributeSlave() const;
    void setInformationGain(float informationGain);
    [[nodiscard]] float getInformationGain() const;
    [[nodiscard]] std::string getAttributeName() const;
    void changeStruct(std::vector<int> rows);
    [[nodiscard]] int getCntAttr() const;
    void deleteStruct(int index);
    std::vector<int> searchAllRows(std::string attrName);

private:
    const std::string colAttrName_{};
    std::vector<attrInfoStruct> slaveAttribute_{};
    float informationGain_{};

};

#endif
