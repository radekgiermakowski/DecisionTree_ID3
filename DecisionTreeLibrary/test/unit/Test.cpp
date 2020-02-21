#include <iostream>
#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "TestFunc.h"

TEST_CASE ("Attribute Test !", "[vector]")
{
    Tree treeTest;
    treeTest.loadData("attrTest.txt");
    std::vector<std::shared_ptr<Attribute>> attrCreat =  treeTest.getAttrVec();
    std::unordered_map<std::string,std::vector<attrInfoStruct>> attrTest = testFunc();

    SECTION("CHECK CREATED COLUMNS")
    {
        int i=0;
        for(auto const & x : attrCreat)
        {
            auto search = attrTest.find(x->getAttributeName());
            REQUIRE(search!=attrTest.end());
        }
    }

    SECTION("CHECK ADDED ROWS TO COLUMNS")
    {
        for(auto const & x : attrCreat)
        {
            auto search = attrTest.find(x->getAttributeName());
            if(search != attrTest.end())
            {
                std::vector<attrInfoStruct> tmpOriginal = x->getAttributeSlave();
                std::vector<attrInfoStruct> tmpCopy = search->second;
                for(int i=0;i<tmpOriginal.size();++i)
                {
                    REQUIRE(tmpOriginal[i].decInfo == tmpCopy[i].decInfo);
                }
            }
        }
    }
}

TEST_CASE("Information Gain Test", "[vector]") {
    std::vector<float> vec1 = {0.2467, 0.0292, 0.1518, 0.0481};
    std::vector<float> vec2;
    informationGainCalculation(vec2);
    REQUIRE(vec1[0] == Approx(vec2[0]).epsilon(0.0009));
    REQUIRE(vec1[1] == Approx(vec2[1]).epsilon(0.0009));
    REQUIRE(vec1[2] == Approx(vec2[2]).epsilon(0.0009));
    REQUIRE(vec1[3] == Approx(vec2[3]).epsilon(0.0009));
}


TEST_CASE("Tree test", "[vector]") {
    std::vector<std::string> decisions;

    treeTest(decisions);
    REQUIRE(decisions[0] == "0");
    REQUIRE(decisions[1] == "0");
    REQUIRE(decisions[2] == "1");
    REQUIRE(decisions[3] == "1");
    REQUIRE(decisions[4] == "1");
    REQUIRE(decisions[5] == "0");
    REQUIRE(decisions[6] == "1");
    REQUIRE(decisions[7] == "0");
    REQUIRE(decisions[8] == "1");
    REQUIRE(decisions[9] == "1");
    REQUIRE(decisions[10] == "1");
    REQUIRE(decisions[11] == "1");
    REQUIRE(decisions[12] == "1");
    REQUIRE(decisions[13] == "0");
}
