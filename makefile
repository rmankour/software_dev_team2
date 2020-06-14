objects = exec_test.o run_test_exec
CXXFLAGS= -Wall

run_test_exec: exec_test.o
	g++ $(CXXFLAGS) -o run_test_exec exec_test.o googletest-release-1.10.0/build/lib/libgtest.a googletest-release-1.10.0/build/lib/libgtest_main.a -pthread
	./run_test_exec

exec_test.o: gtest_file_construction.cpp construction.cpp main.cpp
	g++ $(CXXFLAGS) -c gtest_file_construction.cpp -o exec_test.o -I googletest-release-1.10.0/googletest/include/ -std=c++11


clean:
	rm $(objects)
