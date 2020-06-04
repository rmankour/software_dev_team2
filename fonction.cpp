#include "fonction.h"
#include <cstdlib>
#include <iostream>

fonction::fonction()
{
	head_ = NULL;
    tail_ = NULL;
}

node* fonction::gethead()
{
    return head_;
}

void fonction::add_node(int value, int type)
{
    node *tmp = new node;
    tmp->value_ = value;
    tmp->type_ = type;
    tmp->next_ = NULL;

    if(head_ == NULL)
    {
        head_ = tmp;
        tail_ = tmp;
    }
    else
    {
        tail_->next_ = tmp;
        tail_ = tail_->next_;
    }
}

fonction::fonction(int n){ //constructeur n nbr de variables
	n_ = n;
	sizef_ = std::rand()%n +1;// taille de la formule initiale

	head_ = NULL;
    tail_ = NULL;

	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); // yes=1, no=0
		add_node(std::rand()%(n_+1), 2); // var
		add_node(std::rand()%2, 3); //and=1, or=0
	}
	add_node(std::rand()%2, 1); // yes=1, no=0
	add_node(std::rand()%(n_+1), 2); // var
}


int fonction::getN(){
	return n_;
}

int fonction::getSizef(){
	return sizef_;
}

int* fonction::getFormule(){
	formule_ = new int[sizef_*3-1];

	node *tmp;
    tmp = head_;

    int i = 0;
    while (tmp != NULL)
    {
        //std::cout << tmp->value_<< std::endl;
        formule_[i] = tmp->value_;
        tmp = tmp->next_;
        i++;
    }

	return formule_;
}

fonction::~fonction(){ //destructeur
	node *tmp;
	node *tmpd;
	tmp = head_;
	while(tmp != NULL){
		tmpd = tmp;
		tmp = tmpd->next_;
		delete []tmpd;
	}
}

/*
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
	
	delete []tempYN;
	tempYN = nullptr;
	delete []tempAO;
	tempAO = nullptr;
	delete []tempVar;
	tempVar = nullptr;

	return *this;

	//fonction returnedfunc = fct;
	//return returnedfunc;

}

void fonction::mutation(){
	// La mutation concerne YN(0), AO(1), inversion(2), deletion(3), insertion(4) ?
	int mutType = std::rand()%5;
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
	    case 2:{ // Inversion sur Var
	    	//std::cout << "mutVar" << std::endl;
	    	mutRank = std::rand()%(sizeVar_+1); // quels rang sont à échanger ?
	    	//std::cout << mutRank << std::endl;
	    	do 
	    	{
	    		mutVar = std::rand()%(sizeVar_+1); // quels rang sont à échanger ?
	    		//std::cout << mutVar << std::endl;
	    	}while(mutRank==mutVar);

	    	for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;

	    	std::cout << "mutRank = " << mutRank << std::endl;
	    	std::cout << "mutVar = " << mutVar << std::endl;

	    	// switch the two var in rankVar_
	    	int temp = rankVar_[mutVar];
	    	//std::cout << "temp = " << temp << std::endl;
	    	rankVar_[mutVar] = rankVar_[mutRank];
	    	//std::cout << "rankVar_[mutVar] = " << rankVar_[mutVar] << std::endl;
	    	rankVar_[mutRank] = temp;
	    	//std::cout << "rankVar_[mutRank] = " << rankVar_[mutRank] << std::endl;

	    	for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;

	    }break;
	    case 3:{ // délétion sur Var

	    }break;
	    case 4:{ // insertion sur Var

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
*/


