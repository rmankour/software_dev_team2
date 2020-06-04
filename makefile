objects = run_tests test_file_geneticAlgo.o exec.o run_test_exec.o exec_test.o fonction.o run_test_exec
CXXFLAGS= -Wall


exec_test.o: gtest_file_construction.cpp construction.cpp main.cpp
	g++ $(CXXFLAGS) -c gtest_file_construction.cpp -o exec_test.o -Igoogletest-release-1.10.0/googletest/include/ -std=c++11

run_test_exec: exec_test.o
	g++ $(CXXFLAGS) -o run_test_exec exec_test.o googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a -pthread
	./run_test_exec

exec.o: fonction.o	#construction.cpp main.cpp
	g++ $(CXXFLAGS)  construction.cpp main.cpp -o exec.o -Igoogletest-release-1.10.0/googletest/include/ -std=c++11
	 
run_tests: test_file_geneticAlgo.o
	g++ $(CXXFLAGS) -o run_tests test_file_geneticAlgo.o googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a
	./run_tests
	
test_file_geneticAlgo.o: test_file_geneticAlgo.cpp
	g++ $(CXXFLAGS) -c test_file_geneticAlgo.cpp -o test_file_geneticAlgo.o -Igoogletest-release-1.10.0/googletest/include/ -std=c++11

fonction.o: fonction.cpp
	g++ -c fonction.cpp -o fonction.o

clean:
	rm $(objects)
