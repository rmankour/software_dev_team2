#include "fonction.h"
#include <cstdlib>
#include <iostream>

fonction::fonction()
{
	
}
fonction::fonction(int n){ //constructeur n nbr de variables
	n_ = n;
	sizef_ = std::rand()%n +1;// taille de la formule initiale
	rankYN_ = new int[sizef_]; //yes=1, no=0
	rankAO_ = new int[sizef_-1]; //and=1, or=0
	rankVar_ = new int[sizef_];
	sizeYN_ = sizef_;
	sizeAO_ = sizef_-1;
	sizeVar_ = sizef_;
	formule_ = formule();

	//std::cout << "init var" << std::endl;

	for(int i=0 ; i<sizeYN_ ; i++){ //fills rankYN w/ 1 (yes) or 0 (no)
		rankYN_[i] = std::rand()%2;
	}
	//std::cout << "rankYN_" << std::endl;

	for(int i=0 ; i<sizeAO_ ; i++){ //fills rankYN w/ 1 (and) or 0 (or)
		rankAO_[i] = std::rand()%2;
	}
	//std::cout << "rankAO_" << std::endl;

	for(int i=0 ; i<sizeVar_ ; i++){ //fills rankVar w/ indexes corresponding to variables
		rankVar_[i] = std::rand()%(n_+1);
	}

	/*int used[sizef_];
	int sizeUsed = 0;
	int rank;
	bool free;

	for(int i = 0 ; i<sizef_ ; i++){ //randomised order attribution for variables
		used[i] = -1;
		//std::cout << "used["<<i<<"] = " << used[i] << std::endl;
		do{
			free = true;
			//std::cout << "free = " << free << std::endl;
			rank = std::rand()%(sizef_);
			//std::cout << "rank = " << rank << std::endl;
			if(sizeUsed>0){
				//std::cout << "sizeUsed>0 = true" << std::endl;
				for(int j = 0 ; j<sizeUsed ; j++){ //checks that the rank is not already used

					if(used[j] == rank){
						//std::cout << "used["<<j<<"] == rank = true" << std::endl;
						free = false;
						//std::cout << "free = " << free << std::endl;
						//std::cout << "j=" << j << " ";
						break;
					}
					

				}
			}
		}while(!free);
		used[sizeUsed] = rank;
		//std::cout << "used["<<sizeUsed<<"] = " << used[sizeUsed] << std::endl;
		sizeUsed++;
		//std::cout << "sizeUsed = " << sizeUsed << std::endl;
		rankVar_[rank] = i;
		//std::cout << "rankVar_["<<rank<<"] = " << rankVar_[rank] << std::endl;
	}*/

	//std::cout << "rankVar_" << std::endl;
	/*for (int i = 0; i < sizef_; ++i)
	{
		std::cout << rankVar_[i]<< "\n";
	}*/
	//std::cout << std::endl;

	/*std::cout << "used" << std::endl;
	for (int i = 0; i < n_; ++i)
	{
		std::cout << used[i]<< "\n";
	}
	std::cout << std::endl;*/

}

int* fonction::getRankYN(){
	return rankYN_;
}

int* fonction::getRankAO(){
	return rankAO_;
}

int* fonction::getRankVar(){
	return rankVar_;
}

int fonction::getN(){
	return n_;
}

int fonction::getSizef(){
	return sizef_;
}

int* fonction::getformule(){
	return formule_;
}

fonction::~fonction(){ //destructeur
	delete []rankYN_;
	rankYN_ = nullptr;
	delete []rankAO_;
	rankAO_ = nullptr;
	delete []rankVar_;
	rankVar_ = nullptr;
	delete []formule_;
    formule_ = nullptr;
}

fonction& fonction::operator=(fonction& fct)
{
	rankYN_ = nullptr;
	rankAO_ = nullptr;
	rankVar_ = nullptr;

	n_ = fct.getN();
	sizef_ = fct.getSizef();
	rankYN_ = new int[sizef_]; //yes=1, no=0
	rankAO_ = new int[sizef_-1]; //and=1, or=0
	rankVar_ = new int[sizef_];
	sizeYN_ = sizef_;
	sizeAO_ = sizef_-1;
	sizeVar_ = sizef_;

	int* tempYN = fct.getRankYN();
	int* tempAO = fct.getRankAO();
	int* tempVar = fct.getRankVar();

	for(int i=0 ; i<sizeYN_ ; i++){ //fills rankYN
		rankYN_[i] = tempYN[i];
	}

	for(int i=0 ; i<sizeAO_ ; i++){ //fills rankYN
		rankAO_[i] = tempAO[i];
	}

	for(int i=0 ; i<sizeVar_ ; i++){ //fills rankVar
		rankVar_[i] = tempVar[i];
	}
	/*
	delete []tempYN;
	tempYN = nullptr;
	delete []tempAO;
	tempAO = nullptr;
	delete []tempVar;
	tempVar = nullptr;
*/
	return *this;

	//fonction returnedfunc = fct;
	//return returnedfunc;

}

void fonction::mutation(){
	// La mutation concerne YN(0), AO(1), Var(2) ?
	int mutType = std::rand()%3;
	int mutRank = -1;
	int mutVar = -1;

	switch (mutType)
	{
		case 0: {// Mutation sur YN
			//std::cout << "mutYN" << std::endl;
			mutRank = std::rand()%(sizeYN_+1); // quel rang concerne la mutation ?
			rankYN_[mutRank] = std::abs(rankYN_[mutRank]-1); // inversion 0 <-> 1 
       	}break;
	    case 1: {// Mutation sur AO
	    	//std::cout << "mutAO" << std::endl;
	    	mutRank = std::rand()%(sizeAO_+1); // quel rang concerne la mutation ?
	    	rankAO_[mutRank] = std::abs(rankAO_[mutRank]-1); // inversion 0 <-> 1
       	}break;
	    case 2:{ // Mutation sur Var
	    	//std::cout << "mutVar" << std::endl;
	    	mutRank = std::rand()%(sizeVar_+1); // quels rang sont à échanger ?
	    	//std::cout << mutRank << std::endl;
	    	do 
	    	{
	    		mutVar = std::rand()%(sizeVar_+1); // quels rang sont à échanger ?
	    		//std::cout << mutVar << std::endl;
	    	}while(mutRank==mutVar);

	    	/*for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;

	    	std::cout << "mutRank = " << mutRank << std::endl;
	    	std::cout << "mutVar = " << mutVar << std::endl;*/

	    	// switch the two var in rankVar_
	    	int temp = rankVar_[mutVar];
	    	//std::cout << "temp = " << temp << std::endl;
	    	rankVar_[mutVar] = rankVar_[mutRank];
	    	//std::cout << "rankVar_[mutVar] = " << rankVar_[mutVar] << std::endl;
	    	rankVar_[mutRank] = temp;
	    	//std::cout << "rankVar_[mutRank] = " << rankVar_[mutRank] << std::endl;

	    	/*for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;*/

	    }break;
	    default:{ // code to be executed if mutType doesn't match any cases
	    	//std::cout << "ERROR" << std::endl;
	    }
	}


}

// affiche la formule d'une fonction
// sur une ligne on a une formule avec dans l'ordre YN Var AO 
void fonction::affichage(){

	for (int i = 0; i < sizef_-1; ++i)
    {
    	std::cout << "  " << getRankYN()[i];
        std::cout << "  " << getRankVar()[i];
        std::cout << "  " << getRankAO()[i] << "    ";

    }

	std::cout << "  " << getRankYN()[sizef_-1];
    std::cout << "  " << getRankVar()[sizef_-1] << "  \n";


}

///*
int* fonction::formule(){
	formule_ = new int[sizef_*3-1];

	for (int i = 0; i < sizef_ -1; i++)
    {
    	formule_[3*i] = getRankYN()[i];
    	formule_[3*i+1] = getRankVar()[i];
    	formule_[3*i+2] = getRankAO()[i];

    }

    formule_[3*(sizef_ -1)] = getRankYN()[sizef_ -1];
	formule_[3*(sizef_ -1)+1] = getRankVar()[sizef_ -1];

	return formule_;
}//*/


