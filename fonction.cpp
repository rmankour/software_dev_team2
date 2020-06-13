#include "fonction.h"
#include <cstdlib>
#include <string>
#include <iostream>

fonction::fonction()
{

	head_ = NULL;
    tail_ = NULL;
    int n = 2;
    n_ = n;
	sizef_ = std::rand()%n_ +1;// taille de la formule initiale

	//std::cout << "size " << sizef_ << std::endl;

	head_ = NULL;
    tail_ = NULL;

	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); // yes=1, no=0
		add_node(std::rand()%(n_), 2); // var
		add_node(std::rand()%2, 3); //and=1, or=0
	}
	add_node(std::rand()%2, 1); // yes=1, no=0
	add_node(std::rand()%(n_), 2); // var


	node* tmp = head_;
	while (tmp != NULL)
    {
        //std::cout << tmp->value_<< std::endl;
        tmp = tmp->next_;
    }


    formule_ = new int[sizef_*3-1];
	Formule();
}

node* fonction::gethead()
{
    return head_;
}

void fonction::add_node(int value, int type)
{
    node *tmp = new node;
    //std::cout << tmp << " ";
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
	for(int i = 0 ; i < index ; i++)
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

fonction::fonction(int n){ //n nombre de gènes dans le tab2d
	//std::cout << "ctor"<< std::endl;
	srand(time(NULL));
	n_ = n-1; // on veut choisir parmi les n-1 premiers genes dans tab2d
	sizef_ = 4;// nombre de genes de la formule initiale
	//std::cout << "size " << sizef_ << std::endl;

	head_ = NULL;
    tail_ = NULL;

	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); // yes=1, no=0
		add_node(std::rand()%n_, 2); // var
		add_node(std::rand()%2, 3); //and=1, or=0
	}
	add_node(std::rand()%2, 1); // yes=1, no=0
	add_node(std::rand()%(n_), 2); // var


	/*node* tmp = head_;
	while (tmp != NULL)
    {
        std::cout << tmp->value_<< " ";
        tmp = tmp->next_;
    }
    std::cout << std::endl;*/

    /*node* tmp1 = head_;
    std::cout << tmp1 << " ";
	while (tmp1 != NULL)
    {
        std::cout << tmp1->next_<< " ";
        tmp1 = tmp1->next_;
    }
    std::cout << std::endl;*/

    formule_ = new int[sizef_*3-1];
    Formule();
    //std::cout << "ctorEnd"<< std::endl;

}


int fonction::getN(){
	return n_;
}

int fonction::getSizef(){
	return sizef_;
}

void fonction::Formule(){
	//std::cout << "fonction::Formule" << std::endl;
	//delete []formule_; // pause pb
	//std::cout << "delete []formule_;" << std::endl;
	//formule_ = new int[sizef_*3-1];
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
}

int* fonction::getFormule(){
	//std::cout << "fonction::getFormule" << std::endl;
	Formule();
	//std::cout<<"Formule()" << std::endl;
	return formule_;
}

fonction::~fonction(){ //destructeur
	//std::cout << "destructor" << std::endl;
	node* current = head_;

	int i = 0;
	while( current != 0 ) {
		node* next = current;
		try{
			next = current->next_;
		}
	    catch (...)  { 
        	std::cout << "Exception next = current->next_ " << i << " "; 
    	} 
	    try{
	    	delete current;
	    }
	    catch (...)  { 
        	std::cout << "Exception delete current" << i << " "; 
    	} 
	    	current = next;
    	i++;
	}
	head_ = NULL;
	//std::cout << "linked list destructed" << std::endl;

	try  { 
		delete []formule_;
    } 
	catch (...)  { 
        std::cout << "Exception delete []formule_\n"; 
    } 

    //std::cout << "delete formule ok" << std::endl;

	/*if(formule_)
	{
		std::cout << "delete []formule_;";
		delete []formule_;
		std::cout << "OK" << std::endl;
	}*/
}


fonction& fonction::operator=(fonction& fct)
{
	
	//std::cout << "op=" << std::endl;

	int SizeLeft = sizef_;
	n_ = fct.getN();
	sizef_ = fct.getSizef();
	node *tmp;
	tmp = head_;
	int* formuleFct = fct.getFormule();

	//std::cout << "print this" << std::endl;
	/*node* tmpa = head_;
	int i = 0;
	std::cout << tmpa << std::endl;
	while (tmpa != NULL)
    {	
    	std::cout << "i" << i << std::endl;
        std::cout << tmpa->value_<< " ";
        tmpa = tmpa->next_;
        std::cout << tmpa << std::endl;
        i++;
    }*/

	if (sizef_<SizeLeft)// si la fonction actuelle est plus grande que la nouvelle
	{
		
		//std::cout << "sizef_<=SizeLeft (if)" << std::endl;

		//std::cout << "sizef_*3-1" << sizef_*3-1 << std::endl;   
		for(int i=0 ; i<(sizef_*3-1) ; i++){// on remplace les valeurs de node jusqu'à la fin de formuleFct
		//	std::cout << "i" << i << std::endl;
		//	std::cout << "tmp " << tmp << std::endl;
		//	std::cout << "tmp val " << tmp->value_ << std::endl;
			tmp->value_ = formuleFct[i];
		//	std::cout << "new tmp val " << tmp->value_ << std::endl;
    		tmp->type_ = i%3 +1;
    	//	std::cout << "type " << tmp->type_ << std::endl;
    		tmp = tmp->next_;
    	//	std::cout << "tmp = next " << tmp << std::endl;
		}
		//std::cout << "values remplaced" << std::endl;

		tail_ = access_node(sizef_*3-2);
		tail_->next_ = NULL;
		//std::cout << "tail_ = tmp;" << std::endl;

		node* tmpA;
		tmpA = tmp->next_;
		
		node* tmpd;
		tmpd = tmpA;
		int i = sizef_*3-1;
		//std::cout << "tmpd init " << tmpd << std::endl;
		//std::cout << "tmp before deletion " << tmp << std::endl;
		while(tmpA != NULL){// on supprime les node restant
		//	std::cout << "tmpd boucle " << tmpd << std::endl;
		//	std::cout << "tmp boucle " << tmp << std::endl;
			try{
				tmpd = tmpA;
			//	std::cout << "tmpd = tmp " << tmpd << std::endl;
				tmpA = tmpd->next_;
			//	std::cout << "tmp = next " << tmp << std::endl;
				delete tmpd;
			//	std::cout << "tmpd delete " << tmpd << std::endl;
			}
			catch(...){
			//	std::cout << "Exception de délétion pour i = " << i << std::endl;
			}
			i++;
		}

		//std::cout << "while exited" << std::endl;



	}else if (sizef_==SizeLeft)
	{
		//std::cout << "sizef_==SizeLeft (if)" << std::endl;
		for(int i=0 ; i<(sizef_*3-1) ; i++){// on remplace les valeurs de node jusqu'à la fin de formuleFct
			//std::cout << "i" << i << std::endl;
			//std::cout << "tmp " << tmp << std::endl;
			//std::cout << "tmp val " << tmp->value_ << std::endl;
			tmp->value_ = formuleFct[i];
			//std::cout << "new tmp val " << tmp->value_ << std::endl;
    		tmp->type_ = i%3 +1;
    		//std::cout << "type " << tmp->type_ << std::endl;
    		tmp = tmp->next_;
    		//std::cout << "tmp = next " << tmp << std::endl;
		}
	}else{
		//std::cout << "sizef_>SizeLeft (else)" << std::endl;
		//std::cout << "on remplace les valeurs de node jusqu'à la fin la fonction actuelle" <<std::endl;
		for(int i=0 ; i<(SizeLeft*3-1) ; i++){// on remplace les valeurs de node jusqu'à la fin la fonction actuelle
			//std::cout << tmp << " ";
			tmp->value_ = formuleFct[i];
			//std::cout << "formuleFct " << tmp->value_ << std::endl;
    		tmp->type_ = i%3 +1;
    		//std::cout << "type " << tmp->type_ << std::endl;
    		tmp = tmp->next_;
		}

		int val;
		int ty;
		//std::cout << "création de nouveau nodes pour ce qu'il reste" <<std::endl;
		for (int i = SizeLeft*3-1 ; i < sizef_*3-1 ; ++i) // création de nouveau nodes pour ce qu'il reste
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



	/*//std::cout << "equal"<< std::endl;
	tmp = head_;
	while (tmp != NULL)
    {
        //std::cout << tmp->value_<< std::endl;
        tmp = tmp->next_;
    }*/
	try{
    	delete []formule_;
        formule_ = new int[sizef_*3-1];
        Formule();
    	//std::cout << "\nFormule updated\n" << std::endl;
    }catch(...){
    	std::cout << "Exception Formule Maj" << std::endl;
    }

    return *this;

}



void fonction::mutation(){
	// La mutation concerne yes/no(0), and/or(1), inversion(2), deletion(3), insertion(4) ?
	int mutType = -1;
	do{
		mutType = std::rand()%5;
	}while((sizef_ == 1 && (mutType == 1 || mutType == 3)) || (sizef_ <= 2 && mutType == 2));
	int mutRank = -1;
	int mutRankB = -1;

	//mutType = 0; // OK 
	//mutType = 1; // OK
	//mutType = 2; // OK
	//mutType = 3; // OK
	//mutType = 4; // OK
	//std::cout << "size " << sizef_ << std::endl;
	//std::cout << "Mutation de type " << mutType << std::endl;

	switch (mutType)
	{
		case 0: {// Mutation sur yes/no
			//std::cout << "mutYN" << std::endl;
			//std::cout << "size = " << sizef_ << std::endl;
			mutRank = std::rand()%(sizef_)*3; // quel rang concerne la mutation ?
			//std::cout << "mutRank = " << mutRank << std::endl;
			node *tmp;
			tmp = access_node(mutRank);
			//std::cout << "value0 = " << tmp->value_ << std::endl;
			tmp->value_ = std::abs((tmp->value_)-1); // inversion 0 <-> 1 
			//std::cout << "value1 = " << tmp->value_ << std::endl;
       	}break;
	    case 1: {// Mutation sur and/or
	    	//std::cout << "mutAO" << std::endl;
	    	//std::cout << "size = " << sizef_ << std::endl;
	    	mutRank = std::rand()%(sizef_)*3-2; // quel rang concerne la mutation ?
	    	//std::cout << "mutRank = " << mutRank << std::endl;
	    	node *tmp;
			tmp = access_node(mutRank);
			//std::cout << "value0 = " << tmp->value_ << std::endl;
			tmp->value_ = std::abs((tmp->value_)-1); // inversion 0 <-> 1 
			//std::cout << "value1 = " << tmp->value_ << std::endl;
       	}break;
	    case 2:{ // Inversion sur Var
	    	//std::cout << "mutRankB" << std::endl;
	    	mutRank = std::rand()%(sizef_)*3-1; // quels rang sont à échanger ?
	    	node *ptrRank;
			ptrRank = access_node(mutRank);
	    	//std::cout << mutRank << std::endl;
	    	node* ptrRankB;
	    	do 
	    	{
	    		mutRankB = std::rand()%(sizef_)*3-1; // quels rang sont à échanger ?
	    		
				ptrRankB = access_node(mutRankB);
	    		//std::cout << mutRankB << std::endl;
	    	}while(mutRank==mutRankB);


	    	/*std::cout << "mutRank = " << mutRank << std::endl;
	    	std::cout << "mutRankB = " << mutRankB << std::endl;	    	
			std::cout << "ptrRank val = " << ptrRank->value_ << std::endl;
			std::cout << "ptrRank type = " << ptrRank->type_ << std::endl;
			std::cout << "ptrRankB val = " << ptrRankB->value_ << std::endl;
			std::cout << "ptrRankB type = " << ptrRankB->type_ << std::endl;*/
	    	
	    	// switch the two var 
	    	int temp = ptrRank->value_;
	    	//std::cout << "temp = " << temp << std::endl;
	    	ptrRank->value_ = ptrRankB->value_;
	    	//std::cout << "ptrRank->value_ = " << ptrRank->value_ << std::endl;
	    	ptrRankB->value_ = temp;
	    	//std::cout << "ptrRankB->value_  = " << ptrRankB->value_  << std::endl;

	    }break;
	    case 3:{ // délétion sur Var
	    	mutRank = std::rand()%(sizef_)*3-1; // quelle est la variable concernée ?
	    	//mutRank = sizef_*3-2;
	    	node *tmp;

	    	if (mutRank == 1)// délétion en tête de liste
	    	{
	    		del_node_suiv(head_);
	    		del_node_suiv(head_);
	    		node* toDel = head_;
	    		head_ = head_->next_;
	    		delete toDel;
	    	}else if (mutRank==sizef_*3-2)
	    	{
	    		tmp = access_node(mutRank-3);
				// supression des 3 noeuds consecutifs (and/or, yes/no, var)
				del_node_suiv(tmp);
				del_node_suiv(tmp);
				del_node_suiv(tmp);
	    	}else
	    	{
	    		tmp = access_node(mutRank-2);
				// supression des 3 noeuds consecutifs (yes/no, var, and/or)
				del_node_suiv(tmp);
				del_node_suiv(tmp);
				del_node_suiv(tmp);
	    	}

			

			sizef_--;
	    	delete []formule_;
		    formule_ = new int[sizef_*3-1];
		    Formule();
	    }break;
	    case 4:{ // insertion sur Var
	    	int addVar = std::rand()%(n_); // quelle variable va-t-on ajouter ?
	    	//std::cout << "addVar = " << addVar << std::endl;
	    	mutRank = std::rand()%(sizef_)*3; // à quel rang est elle insérée ?
	    	//mutRank = sizef_*3;
	    	//std::cout << "mutRank = " << mutRank << std::endl;
	    	if (mutRank == 0)
	    	{
	    		/*node* tmp1 = head_;
			    std::cout << tmp1 << " ";
				while (tmp1 != NULL)
			    {
			        std::cout << tmp1->next_<< " ";
			        tmp1 = tmp1->next_;
			    }
			    std::cout << std::endl;*/

	    		node* p = new node;
		        p->value_ = std::rand()%2;
		        //std::cout << "pvalYN = " << p->value_ << std::endl;
		        p->type_ = 1;

		        p->next_ = head_;
		        head_ = p;
		        add_after_node(p, std::rand()%2, 3);
		        add_after_node(p, addVar, 2);

		        /*node* tmp2 = head_;
			    std::cout << tmp1 << " ";
				while (tmp2 != NULL)
			    {
			        std::cout << tmp2->next_<< " ";
			        tmp2 = tmp2->next_;
			    }
			    std::cout << std::endl;*/
		        
	    	}else if (mutRank == sizef_*3)
	    	{
	    		node *tmp;
		    	tmp = access_node(mutRank-2);
		    	add_after_node(tmp, addVar, 2);
		    	add_after_node(tmp, std::rand()%2, 1);
		    	add_after_node(tmp, std::rand()%2, 3);
	    	}else
	    	{

	    		node *tmp;
		    	tmp = access_node(mutRank-1);
		    	add_after_node(tmp, std::rand()%2, 3);
		    	add_after_node(tmp, addVar, 2);
		    	add_after_node(tmp, std::rand()%2, 1);

	    	}
	    	

	    	sizef_++;
	    	delete []formule_;
		    formule_ = new int[sizef_*3-1];
		    Formule();

	    }break;
	    default:{ // code to be executed if mutType doesn't match any cases
	    	std::cout << "ERROR" << std::endl;
	    }
	}


}


void fonction::affichage(){

	node* temp;
	temp = head_;
	while (temp != NULL)
    {
        std::cout << " " << temp->value_;
        temp = temp->next_;
    }
    std::cout << std::endl;

}

std::string fonction::formuleToString(){

	node* temp;
	temp = head_;
	std::string strtempbrut ="";
	
	while (temp != NULL)
    {
        strtempbrut += std::to_string(temp->value_);
        //std::cout << "temp->value "  << temp->value_ << "    strtempbrut " << strtempbrut <<std::endl;
        strtempbrut += "_";
        temp = temp->next_;
 
    }
    //std::cout << strtempbrut << std::endl;
    int compteur = 0;
    int j = 0;
    bool reini;
    std::string output = "";
    while(j < strtempbrut.length())
    {
    	if(strtempbrut[j] != '_')
    	{
    		reini = 0;
    		//-----------------------caractères not/yes
    		if (compteur == 0) // on est dans un truc not/yes
    		{
		    	if(strtempbrut[j] == '1')
		    	{
					output += "~";
		    	}
		    	else{ 
		    		//sinon c'est yes on met rien
		    	}
		    	  			
    		}

	    	//---------------------caractères numéro de gene
	    	if (compteur == 1)// on est dans un numéro de gène qui peut comporter plusieurs digits
	    	{
		    	output += 'x';
		    	while(strtempbrut[j] != '_')//tant que le numéro de gène n'est pas fini (genre il a plusieurs digit)
		    	{
	    			output += strtempbrut[j];
	    			j++;
	    		}
	    		    		
	    	}

	    	//----------------------caractère And/Or and : 0 ; or : 1
		    if (compteur == 2)
		    {
		    	if(strtempbrut[j] == '1')
		    	{
					output += " & ";
		    	}
		    	else{
		    		output += " | ";
		    	}
		    	reini = 1;
	    	}
	    	compteur++;	
	    	if (reini==1)
	    	{
	    		compteur = 0;
	    	}
    	}
    	j++;
    	//traite les trucs 3 par 3 
    	

    }/*
    //sinon on traite les 2 :
	if(strtempbrut[j] == '1')
	{
		output += "~";
	}
	else{ 
		//sinon c'est yes on met rien
	}
	j++;
	//---------------------caractères numéro de gene
	output += 'x';
	output += strtempbrut[j];
	j++;    */
	/*int l = 0;
	while(output[l] != '\0')
	{
		std::cout << output[l];
		l++;
	}*/
    return output;

}
