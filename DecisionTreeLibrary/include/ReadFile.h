#ifndef DECISIONTREE_READFILE_H
#define DECISIONTREE_READFILE_H

#include "Attribute.h"


class DataMatrix{
public:
    DataMatrix() = default;
    ~DataMatrix() = default;

    void loadData(std::string nameFile,std::vector<std::shared_ptr<Attribute>> &vecAttr);
    void loadData(std::vector<std::vector<std::string>> &data,std::vector<std::shared_ptr<Attribute>> &vecAttr);
    void ReadFile(std::string nameFile,std::vector<std::shared_ptr<Attribute>> &vecAttr);

private:
    static void extractAttributes_(std::string line, std::vector<std::string> &addLine);
    static bool findAttribute_(std::vector<attrInfoStruct> &attr,std::string dec,std::string name,int row);
    static void parseColumn_(std::vector<std::vector<std::string>> &data,std::vector<std::shared_ptr<Attribute>> &vecAttr);

};

#endif //DECISIONTREE_READFILE_H
