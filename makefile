objects = run_tests test_file_geneticAlgo.o fonction.o
CXXFLAGS= -Wall

run_tests: test_file_geneticAlgo.o
	g++ -o run_tests test_file_geneticAlgo.o googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a -pthread
	./run_tests

test_file_geneticAlgo.o: test_file_geneticAlgo.cpp
	g++ $(CXXFLAGS) -c test_file_geneticAlgo.cpp -o test_file_geneticAlgo.o -Igoogletest-release-1.10.0/googletest/include/ -std=c++11

fonction.o: fonction.cpp
	g++ -c fonction.cpp -o fonction.o

clean:
	rm $(objects)
