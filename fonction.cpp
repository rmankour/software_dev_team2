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
    //std::cout << "value " << value << std::endl;
	//std::cout << "type " << type << std::endl;
    tmp->value_ = value;
    tmp->type_ = type;
    tmp->next_ = NULL;
    //std::cout << "Newvalue " << tmp->value_ << std::endl;
	//std::cout << "Newtype " << tmp->type_ << std::endl;


    if(head_ == NULL)
    {
        head_ = tmp;
        tail_ = tmp;
    }
    else
    {
        tail_->next_ = tmp;
        tail_ = tmp;
    }
}

fonction::fonction(int n){ //constructeur n nbr de variables
	//std::cout << "ctor"<< std::endl;
	n_ = n;
	sizef_ = std::rand()%n +1;// taille de la formule initiale
	//std::cout << "size " << sizef_ << std::endl;

	head_ = NULL;
    tail_ = NULL;

	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); // yes=1, no=0
		add_node(std::rand()%(n_+1), 2); // var
		add_node(std::rand()%2, 3); //and=1, or=0
	}
	add_node(std::rand()%2, 1); // yes=1, no=0
	add_node(std::rand()%(n_+1), 2); // var


	node* tmp = head_;
	while (tmp != NULL)
    {
        //std::cout << tmp->value_<< std::endl;
        tmp = tmp->next_;
    }
}


int fonction::getN(){
	return n_;
}

int fonction::getSizef(){
	return sizef_;
}

int* fonction::getFormule(){
	//std::cout << "getFormule" << std::endl;
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


fonction& fonction::operator=(fonction& fct)
{
	int tempSize = sizef_;
	n_ = fct.getN();
	sizef_ = fct.getSizef();
	node *tmp;
	tmp = head_;
	int* formuleFct = fct.getFormule();

	if (sizef_<=tempSize)// si la fonction actuelle est plus grande que la nouvelle
	{
		//std::cout << "sizef_<=tempSize" << std::endl;
		for(int i=0 ; i<(sizef_*3-1) ; i++){// on remplace les valeurs de node jusqu'à la fin de formuleFct
			tmp->value_ = formuleFct[i];
    		tmp->type_ = i%3 +1;
    		tmp = tmp->next_;
		}

		tail_ = tmp;

		node *tmpd;
		while(tmp != NULL){// on supprime les node restant
			tmpd = tmp;
			tmp = tmpd->next_;
			delete []tmpd;
		}
	}else{
		//std::cout << "sizef_>tempSize" << std::endl;
		for(int i=0 ; i<(tempSize*3-1) ; i++){// on remplace les valeurs de node jusqu'à la fin la fonction actuelle
			tmp->value_ = formuleFct[i];
			//std::cout << "formuleFct " << tmp->value_ << std::endl;
    		tmp->type_ = i%3 +1;
    		//std::cout << "type " << tmp->type_ << std::endl;
    		tmp = tmp->next_;
		}

		int val;
		int ty;
		for (int i = tempSize*3-1 ; i < sizef_*3-1 ; ++i) // création de nouveau nodes pour ce qu'il reste
		{
			//std::cout << "i " << i << std::endl;
			//std::cout << "formuleFct " << formuleFct[i] << std::endl;
			//std::cout << "(i%3 +1) " << (i%3 +1) << std::endl;
			val = formuleFct[i];
			ty = (i%3 +1);
			//std::cout << "val " << val << std::endl;
			//std::cout << "ty " << ty << std::endl;
			add_node(val, ty);
		}
	}

	//std::cout << "equal"<< std::endl;
	tmp = head_;
	while (tmp != NULL)
    {
        //std::cout << tmp->value_<< std::endl;
        tmp = tmp->next_;
    }

	return *this;

}


/*
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


