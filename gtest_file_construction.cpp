#include "gtest/gtest.h"
#include "construction.cpp"
#include "fonction.cpp"
#include <string>
#include <iostream>

/* the makefile should directly compile then execute the program, and finaly clean the compiling intermediaries and the executable*/
/* run make clean to get rid of intermediate files */

// Basic GTest

TEST(GTestTests, basic_test) {

    EXPECT_TRUE(true);
}

TEST(GTestTests, test_dataManage_lectureCaseTab)
{
	construction obj(0,0,"gene.csv");
	obj.dataManage();
	std::string chartest = "";
	std::string expectedchar = "110101001011011001000011010011010100111111101011100001101001101111010111101011111011110011111001100100111111110100100011";

	for(size_t j=0; j<obj.get_nbcol(); j++)
	{
		if ((obj.lectureCaseTab(obj.get_nblig()-1,j)==false))
		{
			chartest += "0";
		}
		else chartest+="1";
	}
	EXPECT_EQ(chartest,expectedchar);

}

fonction f1(20);
TEST(GTestTests, fonctionConstructor_test){
	for(int i=0 ; i<20 ; i++){
		EXPECT_TRUE(f1.getRankYN()[i] == 0 || f1.getRankYN()[i] == 1);
	}
}
