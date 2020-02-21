#include "ReadFile.h"


void DataMatrix::ReadFile(std::string nameFile,std::vector<std::shared_ptr<Attribute>> &vecAttr) {
    std::ifstream file(nameFile, std::ifstream::in);
    std::vector<std::vector<std::string>> tmpFile;
    if(file.good()){
        std::string token;
        std::string line;
        std::vector<std::string> vectorLine;
        while(getline(file,line)){
            extractAttributes_(line,vectorLine);
            tmpFile.push_back(vectorLine);
            vectorLine.clear();
        }
        file.close();
    }
    else {
        perror("Error opening file");
        abort();
    }
    parseColumn_(tmpFile,vecAttr);

}

void DataMatrix::parseColumn_(std::vector<std::vector<std::string>> &data, std::vector<std::shared_ptr<Attribute>> &vecAttr){
    int colNumber = data[0].size();
    int rowNumber = data.size();
    std::vector<attrInfoStruct> tmpAttr;

    std::string dec;
    std::string name;

    for(int j = 1 ; j < colNumber;j++){
        for(int i = 0; i<rowNumber; i++){
            if(tmpAttr.empty()){
                attrInfoStruct tmpStr;
                tmpStr.attributeName = data[i][j];
                std::vector<int> tmpVec1;
                tmpVec1.push_back(i);
                tmpStr.decInfo.emplace(data[i][0],tmpVec1);
                tmpAttr.push_back(tmpStr);
            }
            else{
                dec = data[i][0];
                name = data[i][j];

                if(findAttribute_(tmpAttr,dec,name,i) == 0){
                    attrInfoStruct tmpStr;
                    tmpStr.attributeName = name;
                    std::vector<int> tmpVec(1);
                    tmpVec.clear();
                    tmpVec.push_back(i);
                    tmpStr.decInfo.emplace(dec,tmpVec);
                    tmpAttr.push_back(tmpStr);
                }
            }
        }
        std::string attrName = "attr" + std::to_string(j);
        std::shared_ptr<Attribute> attr(new Attribute(attrName,tmpAttr));
        vecAttr.push_back(attr);
        tmpAttr.clear();
    }

}

void DataMatrix::extractAttributes_(std::string line, std::vector<std::string> &addLine){
    std::stringstream cut(line);
    std::string tmp;
    while(getline(cut,tmp,',')){
        addLine.push_back(tmp);
    }
}

bool DataMatrix::findAttribute_(std::vector<attrInfoStruct> &attr, std::string dec, std::string name,int row){
    for(auto &x: attr){
        if(x.attributeName == name){
            auto it = x.decInfo.find(dec);
            if(it != x.decInfo.end()){
                it->second.push_back(row);
                return true;
            }
            else{
                std::vector<int> tmpVec;
                tmpVec.push_back(row);
                x.decInfo.emplace(dec,tmpVec);
                return true;
            }
        }
    }
    return false;
}


void DataMatrix::loadData(std::string nameFile,std::vector<std::shared_ptr<Attribute>> &vecAttr){
    ReadFile(nameFile,vecAttr);
}

void DataMatrix::loadData(std::vector<std::vector<std::string> > &data, std::vector<std::shared_ptr<Attribute> > &vecAttr){
    parseColumn_(data,vecAttr);
}