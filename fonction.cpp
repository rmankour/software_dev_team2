#include "fonction.h"
#include <cstdlib>
#include <iostream>

fonction::fonction(int n){ //constructeur n nbr de variables
	n_ = n;
	rankYN_ = new int[n]; //yes=1, no=0
	rankAO_ = new int[n-1]; //and=1, or=0
	rankVar_ = new int[n];
	sizeYN_ = n;
	sizeAO_ = n-1;
	sizeVar_ = n;

	//std::cout << "init var" << std::endl;

	for(int i=0 ; i<sizeYN_ ; i++){ //fills rankYN w/ 1 (yes) or 0 (no)
		rankYN_[i] = std::rand()%2;
	}
	//std::cout << "rankYN_" << std::endl;

	for(int i=0 ; i<sizeAO_ ; i++){ //fills rankYN w/ 1 (and) or 0 (or)
		rankAO_[i] = std::rand()%2;
	}
	//std::cout << "rankAO_" << std::endl;

	int used[n];
	int sizeUsed = 0;
	int rank;
	bool free;

	for(int i = 0 ; i<n ; i++){ //randomised order attribution for variables
		used[i] = -1;
		
		do{
			free = true;
			rank = std::rand()%(n_+1);
			//std::cout << "rank=" << rank << " ";
			if(sizeUsed>0){
				for(int j = 0 ; j<sizeUsed ; j++){ //checks that the rank is not already used
					if(used[j] == rank){
						free = false;
						//std::cout << "j=" << j << " ";
						break;
					}
					

				}
			}
		}while(!free);
		used[sizeUsed] = rank;
		sizeUsed++;
		rankVar_[rank] = i;
		//std::cout << "HIIIII=" << i << " ";
	}
	//std::cout << "rankVar_" << std::endl;



}

int* fonction::getRankYN(){
	return rankYN_;
}

fonction::~fonction(){ //destructeur
	delete []rankYN_;
	rankYN_ = nullptr;
	delete []rankAO_;
	rankAO_ = nullptr;
	delete []rankVar_;
	rankVar_ = nullptr;
}