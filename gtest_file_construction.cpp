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
	for(int i=0 ; i<(f1.getSizef()-1) ; i++){
		EXPECT_TRUE(f1.getRankYN()[i] == 0 || f1.getRankYN()[i] == 1);
		EXPECT_TRUE(f1.getRankAO()[i] == 0 || f1.getRankAO()[i] == 1);
		EXPECT_TRUE(f1.getRankVar()[i] >= 0 && f1.getRankYN()[i] < f1.getN());
	}
	EXPECT_TRUE(f1.getRankYN()[f1.getSizef()-1] == 0 || f1.getRankYN()[f1.getSizef()-1] == 1);
	EXPECT_TRUE(f1.getRankVar()[f1.getSizef()-1] >= 0 && f1.getRankYN()[f1.getSizef()-1] < f1.getN());
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


fonction f3(5);
/*TEST(GTestTests, fonctionOperatorEq_test){
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
}*/


TEST(GTestTests, fonctionMutation_test){
	int n = f3.getN();
	int* YN0 = new int[n];
	int* AO0 = new int[n-1];
	int* Var0 = new int[n];
	for(int i=0 ; i<n; i++){ //fills rankYN
		YN0[i] = f3.getRankYN()[i];
	}

	for(int i=0 ; i<n-1 ; i++){ //fills rankYN
		AO0[i] = f3.getRankAO()[i];
	}

	for(int i=0 ; i<n; i++){ //fills rankVar
		Var0[i] = f3.getRankVar()[i];
	}
	f3.mutation();
	int* YN1 = f3.getRankYN();
	int* AO1 = f3.getRankAO();
	int* Var1 = f3.getRankVar();

	bool mutTest = false;

	for (int i = 0; i < n-1; ++i)
	{
		
		mutTest = mutTest or YN0[i]!=YN1[i] or AO0[i]!=AO1[i] or Var0[i]!=Var1[i];
	}

	mutTest = mutTest or YN0[n-1]!=YN1[n-1] or Var0[n-1]!=Var1[n-1];

	EXPECT_TRUE(mutTest);

/*
	delete [] YN0;
	YN0 = nullptr;
	delete [] AO0;
	AO0 = nullptr;
	delete [] Var0;
	Var0 = nullptr;
	delete [] YN1;
	YN1 = nullptr;
	delete [] AO1;
	AO1 = nullptr;
	delete [] Var1;
	Var1 = nullptr;
	*/
}


TEST(GTestTests, fonctionGetFormule_test){

	int* formule1 = f1.getFormule();
	int size1 = f1.getSizef(); 
	int n1 = f1.getN();

	for (int i = 0; i < size1-1; i++)
    {
    	//std::cout << "i = " << i <<std::endl;
    	EXPECT_TRUE(formule1[3*i] == 0 || formule1[3*i] == 1);
    	//std::cout << formule1[3*i] << std::endl;
    	EXPECT_TRUE(formule1[3*i+1] >= 0 && formule1[3*i+1] < n1);
    	EXPECT_TRUE(formule1[3*i+2] == 0 || formule1[3*i+2] == 1);
    }
    EXPECT_TRUE(formule1[3*(size1 -1)] == 0 || formule1[3*(size1 -1)] == 1);
    EXPECT_TRUE(formule1[3*(size1 -1)+1] >= 0 && formule1[3*(size1 -1)+1] < n1);
}

