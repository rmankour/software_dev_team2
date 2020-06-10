#include "gtest/gtest.h"
//#include "construction.cpp"
#include "fonction.cpp"
#include <string>
#include <iostream>
#include <algorithm> 

/* the makefile should directly compile then execute the program, and finaly clean the compiling intermediaries and the executable*/
/* run make clean to get rid of intermediate files */

// Basic GTest

TEST(GTestTests, basic_test) {

    EXPECT_TRUE(true);
}

fonction f1(5);
int* formule1 = f1.getFormule();
int size1 = f1.getSizef(); 

int n1 = f1.getN();

TEST(GTestTests, fonctionConstructor_test){
	//std::cout << "size " << size1 << std::endl;
	//std::cout << "n " << n1 << std::endl;

	for (int i = 0; i < size1-1; i++)
    {
    	//std::cout << "i = " << i <<std::endl;
    	EXPECT_TRUE(formule1[3*i] == 0 || formule1[3*i] == 1);
    	//std::cout << formule1[3*i] << std::endl;
    	EXPECT_TRUE(formule1[3*i+1] >= 0 && formule1[3*i+1] < n1);
    	//std::cout << formule1[3*i+1] << std::endl;
    	EXPECT_TRUE(formule1[3*i+2] == 0 || formule1[3*i+2] == 1);
    	//std::cout << formule1[3*i+2] << std::endl;
    }
    EXPECT_TRUE(formule1[3*(size1 -1)] == 0 || formule1[3*(size1 -1)] == 1);
    //std::cout << formule1[3*(size1 -1)] << std::endl;
    EXPECT_TRUE(formule1[3*(size1 -1)+1] >= 0 && formule1[3*(size1 -1)+1] < n1);
    //std::cout << formule1[3*(size1 -1)+1] << std::endl;

}

TEST(GTestTests, fonctionGetN_test){
	EXPECT_EQ(f1.getN(), 5);
}



TEST(GTestTests, fonctionOperatorEq_test){
	std::cout << "f3" << std::endl;
	fonction f3(5);
	std::cout << "f4" << std::endl;
	fonction f4(4);
	std::cout << "gtest=" << std::endl;
	f3 = f1;
	std::cout<<"f3=f1" << std::endl;
	int* formule3 = f3.getFormule();
	std::cout<<"f3.getFormule" << std::endl;
	int size3 = f3.getSizef(); 
	int n3 = f3.getN();
	EXPECT_EQ(size1, size3);
	EXPECT_EQ(n1, n3);

	/*std::cout << "f4" << std::endl;
	f4 = f1;
	std::cout << "end f4=f1;"<< std::endl;
	int* formule4 = f4.getFormule();
	//std::cout << "end f4.getFormule();"<< std::endl;
	int size4 = f4.getSizef(); 
	int n4 = f4.getN();
	EXPECT_EQ(size1, size4);
	EXPECT_EQ(n1, n4);*/

	std::cout<<"for1" << std::endl;

	for (int i = 0; i < size3*3-1; ++i)
	{	
		//std::cout << "i3 = " << i << std::endl;
		EXPECT_EQ(formule1[i], formule3[i]);
	}

	/*for (int i = 0; i < size4*3-1; ++i)
	{
		//std::cout << "i4 = " << i << std::endl;
		EXPECT_EQ(formule1[i], formule4[i]);
	}*/

	std::cout<<"=finished" << std::endl;

}

/*
fonction f5(63);
TEST(GTestTests, fonctionMutation_test){
	std::cout<<"mut" << std::endl;
	int size0 = f5.getSizef(); 
	int* formule0 = new int[size0*3-1];
	for (int i = 0; i < size0*3-1; ++i)
	{
		formule0[i] = f5.getFormule()[i];
	}
	f5.mutation();
	int* formule1 = f5.getFormule();
	int size1 = f5.getSizef(); 

	bool mutTest = (size0!=size1);

	for (int i = 0; i < std::min(size0, size1)*3-1; ++i)
	{
		
		mutTest = mutTest or formule0[i]!=formule1[i];
	}

	EXPECT_TRUE(mutTest);


	delete []formule0;
	delete []formule1;

	f3.affichage();
}
*/
