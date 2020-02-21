#include "Tree.h"

attrInfoStruct fillStruct(std::string name, std::vector<std::string> dec, std::vector<std::vector<int>> rows)
{
    attrInfoStruct tmpStruct;
    std::unordered_map<std::string,std::vector<int>> tmpMap;
    tmpStruct.attributeName = name;
    for(int j=0 ; j< dec.size();++j)
    {
        tmpMap.emplace(dec[j],rows[j]);
    }
    tmpStruct.decInfo=tmpMap;
    return tmpStruct;
}

std::unordered_map<std::string,std::vector<attrInfoStruct>> testFunc()
{
    std::vector<attrInfoStruct> testVec;
    std::unordered_map<std::string,std::vector<attrInfoStruct>> Attr;

    std::vector<std::string> dec({"1","0"});
    std::vector<std::vector<int>> rows;
    rows.insert(rows.end(), {8,10});
    rows.insert(rows.end(), {0,1,7});
    testVec.push_back(fillStruct("S",dec,rows));
    dec.clear();
    rows.clear();

    dec.insert(dec.end(),{"1"});
    rows.insert(rows.end(), {2,6,11,12});
    testVec.push_back(fillStruct("P",dec,rows));
    dec.clear();
    rows.clear();

    dec.insert(dec.end(),{"0","1"});
    rows.insert(rows.end(), {5,13});
    rows.insert(rows.end(), {3,4,9});
    testVec.push_back(fillStruct("D",dec,rows));
    dec.clear();
    rows.clear();

    Attr.emplace("attr1",testVec);
    testVec.clear();


    dec.insert(dec.end(),{"1","0"});
    rows.insert(rows.end(), {2,12});
    rows.insert(rows.end(), {0,1});
    testVec.push_back(fillStruct("G",dec,rows));
    dec.clear();
    rows.clear();

    dec.insert(dec.end(),{"0","1"});
    rows.insert(rows.end(), {7,13});
    rows.insert(rows.end(), {3,9,10,11});
    testVec.push_back(fillStruct("L",dec,rows));
    dec.clear();
    rows.clear();

    dec.insert(dec.end(),{"0","1"});
    rows.insert(rows.end(), {5});
    rows.insert(rows.end(), {4,6,8});
    testVec.push_back(fillStruct("Z",dec,rows));
    dec.clear();
    rows.clear();

    Attr.emplace("attr2",testVec);
    testVec.clear();

    dec.insert(dec.end(),{"1","0"});
    rows.insert(rows.end(), {2,3,11});
    rows.insert(rows.end(), {0,1,7,13});
    testVec.push_back(fillStruct("W",dec,rows));
    dec.clear();
    rows.clear();

    dec.insert(dec.end(),{"0","1"});
    rows.insert(rows.end(), {5});
    rows.insert(rows.end(), {4,6,8,9,10,12});
    testVec.push_back(fillStruct("N",dec,rows));
    dec.clear();
    rows.clear();

    Attr.emplace("attr3",testVec);
    testVec.clear();

    return Attr;
}

void informationGainCalculation(std::vector<float> &vector){
    Tree tree;
    std::vector<std::shared_ptr<Attribute>> vecAttr;
    DataMatrix readData;
    readData.loadData("entropyTest.txt", vecAttr);
    for(const auto& x : vecAttr){
        vector.push_back(tree.calculateEntropy(x->getAttributeSlave()));
    }

}

void treeTest(std::vector<std::string> & vector){
    Tree tree;
    std::vector<int> tmp;
    std::shared_ptr<Node> node;
    tree.loadData("entropyTest.txt");
    tree.learn();
    tree.getDecision("testVector.txt", vector);

}

