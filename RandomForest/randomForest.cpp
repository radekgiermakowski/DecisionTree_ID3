#include "randomForest.h"
#include "threadPool.h"

void Forest::loadData(std::string fileName, std::vector<std::vector<std::string>>  *vec){
    std::ifstream file(fileName, std::ifstream::in);
    if(file.good()){
        std::vector<std::vector<std::string>> allData;
        std::string line;
        std::vector<std::string> vectorLine;
        while(getline(file,line)){
            boost::split(vectorLine, line, boost::is_any_of(","));
            allData.push_back(vectorLine);
            vectorLine.clear();
        }
        if(vec!= nullptr)
            *vec = allData;
        splitData_(allData);
        file.close();
    }
    else{
        perror("Error open file !");
        abort();
    }
}

void Forest::splitData_(std::vector<std::vector<std::string>> &allData){
    int range = allData.size();
    int j=0;
    for(int i=0; i<numberTree_; i++){
        std::vector<int> rows = randomRows_(range);
        std::vector<std::vector<std::string>> tmp;
        for(auto const &x : rows)
            tmp.push_back(allData[x]);
        sortData_.push_back(tmp);
    }

}


std::vector<int> Forest::randomRows_(int range){
    std::vector<int> rows;

    std::uniform_int_distribution<int> dice(0, range-1);
    std::random_device rd1;

    for(int i=0; i<(range/numberTree_); ++i){
        int r = dice(rd1);
        rows.push_back(r);
    }
    return rows;
}

void Forest::buildTree_(std::vector<std::vector<std::string>> &data){
    std::shared_ptr<Tree> tree(new Tree);
    tree->loadData(data);
    std::vector<int> tmp;
    tree->learn();
    tree_.push_back(tree);
}



void Forest::buildTree(){
    std::unique_ptr<ThreadPool> pool(new ThreadPool(numberTree_));
    for(size_t i = 0 ; i< numberTree_; ++i){
        mutex_.lock();
        std::vector<std::vector<std::string>> tmp = returnData_();
        pool->enqueue(boost::bind(&Forest::buildTree_,this,tmp));
        indexData_++;
        mutex_.unlock();
    }

    while(tree_.size()!=numberTree_){}

}

std::vector<std::vector<std::string>> Forest::returnData_(){
    return sortData_[indexData_];
}

void Forest::checkForestAccuracy(std::string learnFile , std::string testFile) {
    std::vector<std::vector<std::string>> inputData;
    std::vector<std::vector<std::string>> testVectors;
    std::vector<std::string> decisions;
    int iterator = 0;
    int goodDecision = 0;
    loadData(learnFile);
    loadData(testFile,&inputData);

    separateTestDecisions_(decisions, testVectors , inputData);
    buildTree();

    for(auto &x : getDecision(testVectors)){

        if( x == decisions[iterator])
            goodDecision+=1;
        ++iterator;
    }
    std::cout<<"Number of tests: "<<iterator<<std::endl<<"Number of correct results : "<<goodDecision<<std::endl;
    auto res = (static_cast<float>(goodDecision)/ static_cast<float>(iterator))*100;
    std::cout<<"Accuracy : "<<res<<"%"<<std::endl;

}

void Forest::separateTestDecisions_(std::vector<std::string> &decision,
                                    std::vector<std::vector<std::string>> &testVector,
                                    std::vector<std::vector<std::string>> inputData) {
    for(auto& x : inputData){
        decision.push_back(x[0]);
        x.erase(x.begin());
        testVector.push_back(x);
    }

}

std::vector<std::string> Forest::getDecision(std::vector<std::vector<std::string>> &testVectors){
    std::unordered_map<std::string , int> decision;
    std::vector<std::string> checkDec;
    int maxValue = 0;
    std::string return_dec;
    for(auto  & vec : testVectors)
    {
        for(auto  &x : tree_){
            std::string tmpDec = x->getDecision(vec);
            auto search_decision = decision.find(tmpDec);
            if(search_decision != decision.end() ){
                ++decision[tmpDec];
            }
            else
                decision.insert({tmpDec , 1});
        }
        for( auto &x : decision){
            if( x.second > maxValue) {
                return_dec = x.first;
                maxValue = x.second;
            }
        }
        maxValue = 0;
        decision.clear();
        checkDec.push_back(return_dec);
    }
    return checkDec;
}