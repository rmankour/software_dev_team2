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



TEST(GTestTests, fonctionConstructor_test){
	//std::cout << "size " << size1 << std::endl;
	//std::cout << "f1(5) ";
	fonction f1(5);
	int* formule1 = f1.getFormule();
	int size1 = f1.getSizef(); 
	int n1 = f1.getN();

	//std::cout << "var = ";
	for (int i = 0; i < size1-1; i++)
    {
    	//std::cout << "i = " << i <<std::endl;
    	EXPECT_TRUE(formule1[3*i] == 0 || formule1[3*i] == 1);
    	//std::cout << formule1[3*i] << std::endl;
    	EXPECT_TRUE(formule1[3*i+1] >= 0 && formule1[3*i+1] < n1);
    	//std::cout << formule1[3*i+1] << " ";
    	EXPECT_TRUE(formule1[3*i+2] == 0 || formule1[3*i+2] == 1);
    	//std::cout << formule1[3*i+2] << std::endl;
    }
    EXPECT_TRUE(formule1[3*(size1 -1)] == 0 || formule1[3*(size1 -1)] == 1);
    //std::cout << formule1[3*(size1 -1)] << std::endl;
    EXPECT_TRUE(formule1[3*(size1 -1)+1] >= 0 && formule1[3*(size1 -1)+1] < n1);
    //std::cout << formule1[3*(size1 -1)+1] << std::endl;
}

TEST(GTestTests, fonctionGetN_test){
	fonction f1b(30);
	EXPECT_EQ(f1b.getN(), 30);
}



TEST(GTestTests, fonctionOperatorInfEqSup_test){
	//std::cout << "gtestI=S" << std::endl;

	//std::cout << "f2(20) ";
	fonction f2(20);
	int size2 = f2.getSizef();
	int n2 = f2.getN();
	int* formule2 = f2.getFormule();
	/*std::cout<<"f2.getFormule = ";
	for (int i = 0; i < size2*3-1; ++i)
	{
		std::cout << formule2[i] << " ";
	}
	std::cout << "\n" << std::endl;*/

	//std::cout << "f3(2) ";
	fonction f3(2);
	

	//std::cout << "f3=f2; ";
	f3 = f2;
	//std::cout<<"end f3=f2" << std::endl;
	int size3 = f3.getSizef(); 
	int n3 = f3.getN();
	int* formule3 = f3.getFormule();
	/*std::cout<<"f3.getFormule = ";
	for (int i = 0; i < size3*3-1; ++i)
	{
		std::cout << formule3[i] << " ";
	}
	std::cout << std::endl;*/
	
	EXPECT_EQ(size2, size3);
	//std::cout << "size2=size3 ";
	EXPECT_EQ(n3, n2);
	//std::cout << "n2=n3\n" << std::endl;


	
	//std::cout<<"for1" << std::endl;
	for (int i = 0; i < size3*3-1; ++i)
	{	
		//std::cout << "i3 = " << i << std::endl;
		EXPECT_EQ(formule2[i], formule3[i]);
	}
	//std::cout<<"=finished" << std::endl;

}

/*TEST(GTestTests, fonctionOperatorSupEqInf_test){
	std::cout << "gtestS=I" << std::endl;

	std::cout << "f4(2) ";
	fonction f4(2);
	int size4 = f4.getSizef();
	int n4 = f4.getN();
	int* formule4 = f4.getFormule();
	std::cout<<"f4.getFormule = ";
	for (int i = 0; i < size4*3-1; ++i)
	{
		std::cout << formule4[i] << " ";
	}
	std::cout << "\n" << std::endl;

	std::cout << "f5(20) ";
	fonction f5(20);	
	

	std::cout << "f5=f4; ";
	f5 = f4;
	std::cout<<"end f5=f4" << std::endl;
	int size5 = f5.getSizef(); 
	int n5 = f5.getN();
	int* formule5 = f5.getFormule();
	std::cout<<"f5.getFormule = ";
	for (int i = 0; i < size5*3-1; ++i)
	{
		std::cout << formule5[i] << " ";
	}
	std::cout << std::endl;
	
	EXPECT_EQ(size5, size4);
	std::cout << "size5=size4 ";
	EXPECT_EQ(n5, n4);
	std::cout << "n5=n4\n" << std::endl;

	
	std::cout<<"for1" << std::endl;
	for (int i = 0; i < size5*3-1; ++i)
	{	
		//std::cout << "i3 = " << i << std::endl;
		EXPECT_EQ(formule4[i], formule5[i]);
	}

	std::cout<<"=finished" << std::endl;

}*/


fonction f5(5);
TEST(GTestTests, fonctionMutation_test){
	//std::cout<<"mut" << std::endl;
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
}

