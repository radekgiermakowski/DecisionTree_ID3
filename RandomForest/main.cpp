#include "randomForest.h"



int main(){
    std::cout<<std::endl;
    std::cout<<"----------------------------------------------------------------------------------------------------------"<<std::endl;
    std::cout<<"Application showing the operation of a Random Forest. The application uses the created static library"<<std::endl;
    std::cout<<"The data set consists of 6000 records"<<std::endl;
    std::cout<<"It classifies mushrooms as edible or inedible on the basis of their 22 characteristics"<<std::endl;
    std::cout<<"Please enter the number of decision trees:"<<std::endl;
    int numberTree=0;
    std::cin>>numberTree;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    std::shared_ptr<Forest> randomForest(new Forest(numberTree));
    randomForest->checkForestAccuracy("agaricus-lepiota.data", "testFile.data");

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time of calculation = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
}
