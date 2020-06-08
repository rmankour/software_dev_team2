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

void fonction::del_node_suiv(node* preced)
{
	node* temp;
    temp = preced->next_;
    preced->next_ = temp->next_;
    delete temp;
}

node* fonction::access_node(int index)
{
	node* tmp;
	tmp = head_;
	for(int i = 0 ; i <= index ; i++)
	{
		tmp = tmp->next_;
	}
	return tmp;
}

void fonction::add_after_node(node *a, int value, int type)
    {
        node* p = new node;
        p->value_ = value;
        p->type_ = type;

        p->next_ = a->next_;
        a->next_ = p;

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
	delete []formule_;
}


fonction& fonction::operator=(fonction& fct)
{
	delete []formule_;

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



void fonction::mutation(){
	// La mutation concerne yes/no(0), and/or(1), inversion(2), deletion(3), insertion(4) ?
	int mutType = std::rand()%5;
	int mutRank = -1;
	int mutVar = -1;

	switch (mutType)
	{
		case 0: {// Mutation sur yes/no
			//std::cout << "mutYN" << std::endl;
			mutRank = std::rand()%(sizef_+1)*3; // quel rang concerne la mutation ?
			node *tmp;
			tmp = access_node(mutRank);
			tmp->value_ = std::abs((tmp->value_)-1); // inversion 0 <-> 1 
       	}break;
	    case 1: {// Mutation sur and/or
	    	//std::cout << "mutAO" << std::endl;
	    	mutRank = std::rand()%(sizef_)*3+2; // quel rang concerne la mutation ?
	    	node *tmp;
			tmp = access_node(mutRank);
			tmp->value_ = std::abs((tmp->value_)-1); // inversion 0 <-> 1 
       	}break;
	    case 2:{ // Inversion sur Var
	    	//std::cout << "mutVar" << std::endl;
	    	mutRank = std::rand()%(sizef_+1)*3+1; // quels rang sont à échanger ?
	    	//std::cout << mutRank << std::endl;
	    	do 
	    	{
	    		mutVar = std::rand()%(sizef_+1)*3+1; // quels rang sont à échanger ?
	    		//std::cout << mutVar << std::endl;
	    	}while(mutRank==mutVar);

	    	/*for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;

	    	std::cout << "mutRank = " << mutRank << std::endl;
	    	std::cout << "mutVar = " << mutVar << std::endl;*/

	    	node *tmpRank;
			tmpRank = access_node(mutRank);
			node* tmpVar;
			tmpVar = access_node(mutVar);
	    	// switch the two var 
	    	int temp = tmpRank->value_;
	    	//std::cout << "temp = " << temp << std::endl;
	    	tmpRank->value_ = tmpVar->value_;
	    	//std::cout << "tmpRank->value_ = " << tmpRank->value_ << std::endl;
	    	tmpVar->value_ = temp;
	    	//std::cout << "tmpVar->value_  = " << tmpVar->value_  << std::endl;

	    	/*for (int i = 0; i < sizef_; ++i)
			{
				std::cout << rankVar_[i]<< "\n";
			}
			std::cout << std::endl;*/

	    }break;
	    case 3:{ // délétion sur Var
	    	mutRank = std::rand()%(sizef_)*3; // quelle est la variable concernée ?
	    	node *tmp;
			tmp = access_node(mutRank-1);
			// supression des 3 noeuds consecutifs (yes/no, var, and/or)
			del_node_suiv(tmp);
			del_node_suiv(tmp);
			if (mutRank!=sizef_)
			{
				del_node_suiv(tmp);
			}
	    }break;
	    case 4:{ // insertion sur Var
	    	mutVar = std::rand()%(n_+1); // quelle variable va-t-on ajouter ?
	    	mutRank = std::rand()%(sizef_)*3; // à quel rang est elle insérée ?
	    	if (mutRank == 0)
	    	{
	    		node* p = new node;
		        p->value_ = std::rand()%2;
		        p->type_ = 1;

		        p->next_ = head_->next_;
		        head_ = p;
		        add_after_node(p, std::rand()%2, 3);
		        add_after_node(p, mutVar, 2);
	    	}
	    	node *tmp;
	    	tmp = access_node(mutRank);
	    	add_after_node(tmp, std::rand()%2, 3);
	    	add_after_node(tmp, mutVar, 2);
	    	add_after_node(tmp, std::rand()%2, 1);

	    }break;
	    default:{ // code to be executed if mutType doesn't match any cases
	    	//std::cout << "ERROR" << std::endl;
	    }
	}


}

/*

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


