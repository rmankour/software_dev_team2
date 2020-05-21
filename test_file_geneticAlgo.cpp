#include "gtest/gtest.h"
#include "fonction.cpp"

/* the makefile should directly compile then execute the program, and finaly clean the compiling intermediaries and the executable*/
/* run make clean to get rid of intermediate files */

// Basic GTest
TEST(GTestTests, basic_test) {

    EXPECT_TRUE(true);
}

fonction f1(20);
TEST(GTestTests, fonctionConstructor_test){
	for(int i=0 ; i<20 ; i++){
		EXPECT_TRUE(f1.getRankYN()[i] == 0 || f1.getRankYN()[i] == 1);
	}
}
