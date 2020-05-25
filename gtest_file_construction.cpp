#include "gtest/gtest.h"
//#include "construction.cpp"
#include "fonction.cpp"
#include <string>
#include <iostream>

/* the makefile should directly compile then execute the program, and finaly clean the compiling intermediaries and the executable*/
/* run make clean to get rid of intermediate files */

// Basic GTest

TEST(GTestTests, basic_test) {

    EXPECT_TRUE(true);
}

/*TEST(GTestTests, test_dataManage_lectureCaseTab)
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

}*/

fonction f1(20);
TEST(GTestTests, fonctionConstructor_test){
	for(int i=0 ; i<20 ; i++){
		EXPECT_TRUE(f1.getRankYN()[i] == 0 || f1.getRankYN()[i] == 1);
	}
}

TEST(GTestTests, fonctionGetN_test){
	EXPECT_EQ(f1.getN(), 20);
}

TEST(GTestTests, fonctionCopyConstructor_test){
	fonction f2 = f1;

	int* f1YN = f1.getRankYN();
	int* f1AO = f1.getRankAO();
	int* f1Var = f1.getRankVar();
	int* f2YN = f2.getRankYN();
	int* f2AO = f2.getRankAO();
	int* f2Var = f2.getRankVar();

	for (int i = 0; i < f1.getN()-1; ++i)
	{
		EXPECT_EQ(f1YN[i], f2YN[i]);
		EXPECT_EQ(f1AO[i], f2AO[i]);
		EXPECT_EQ(f1Var[i], f2Var[i]);
	}

	EXPECT_EQ(f1YN[f1.getN()-1], f2YN[f1.getN()-1]);
	EXPECT_EQ(f1Var[f1.getN()-1], f2Var[f1.getN()-1]);

	delete []f1YN;
	f1YN = nullptr;
	delete []f1AO;
	f1AO = nullptr;
	delete []f1Var;
	f1Var = nullptr;
	delete []f2YN;
	f2YN = nullptr;
	delete []f2AO;
	f2AO = nullptr;
	delete []f2Var;
	f2Var = nullptr;
}


fonction f3(2);
TEST(GTestTests, fonctionOperatorEq_test){
	f3 = f1;

	int* f1YN = f1.getRankYN();
	int* f1AO = f1.getRankAO();
	int* f1Var = f1.getRankVar();
	int* f3YN = f3.getRankYN();
	int* f3AO = f3.getRankAO();
	int* f3Var = f3.getRankVar();

	for (int i = 0; i < f1.getN()-1; ++i)
	{
		EXPECT_EQ(f1YN[i], f3YN[i]);
		EXPECT_EQ(f1AO[i], f3AO[i]);
		EXPECT_EQ(f1Var[i], f3Var[i]);
	}

	EXPECT_EQ(f1YN[f1.getN()-1], f3YN[f1.getN()-1]);
	EXPECT_EQ(f1Var[f1.getN()-1], f3Var[f1.getN()-1]);

	delete []f1YN;
	f1YN = nullptr;
	delete []f1AO;
	f1AO = nullptr;
	delete []f1Var;
	f1Var = nullptr;
	delete []f3YN;
	f3YN = nullptr;
	delete []f3AO;
	f3AO = nullptr;
	delete []f3Var;
	f3Var = nullptr;
}

