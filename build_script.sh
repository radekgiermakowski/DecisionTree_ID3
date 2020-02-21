dir=$pwd

if [[ $# -lt 1 ]]
then
	echo "A correct call of the application should include : app/tests"
	exit 1
fi

#build directory
cd DecisionTreeLibrary
if [ -d "cmake-build-debug" ]
then
	echo "cmake-build-debug exist"
	
else
	mkdir cmake-build-debug
fi

#build directory
cd ..
cd DecisionTreeLibrary
mkdir cmake-build-debug

cd cmake-build-debug
cmake ..
make

#build app
cd ..
cd ..
cd RandomForest

if [ -d "cmake-build-debug" ]
then
	echo "cmake-build-debug exist"
else
	mkdir cmake-build-debug
fi


mkdir cmake-build-debug

cd cmake-build-debug
cmake ..
make


if [[ $1 == app ]]
then
	./forest
else	
	cd ..
	cd ..
	cd DecisionTreeLibrary/cmake-build-debug/test
	if [[ $2 = "s" ]]
	then
		./test -s
	else
		./test
		echo "To run tests with a detailed description, call the program: ./build_script/test s"
	fi
fi


