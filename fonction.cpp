#include "fonction.h"
#include <cstdlib>
#include <string>
#include <iostream>

void fonction::add_node(int value, int type)
{
	//! Adds a node containing the 1st parameter as its value and the 2nd parameter as its type

    node *tmp = new node; // creates a new node
    tmp->value_ = value; // value is asigned 
    tmp->type_ = type; // type is asigned
    tmp->next_ = NULL; // is set as the last node of the list

    if(head_ == NULL) // if the linked list is empty
    {
        head_ = tmp; // the new node is the first node
        tail_ = tmp; // and the last node
    }
    else
    {
        tail_->next_ = tmp; // the next node after the current last node is set as our new node
        tail_ = tmp; // our new node is set as the tail of the list
    }

}

void fonction::del_node_suiv(node* preced)
{
	//! Deletes the node right after the one given as parameter

	node* temp;
    temp = preced->next_; // temp takes the address of the node to delete
    preced->next_ = temp->next_; // the node before takes as next node the node after the one beeing deleted
    delete temp; // the node is deleted
}

node* fonction::access_node(int index)
{
	//! Returns the address of the node at the index given as parameter

	// Each node is traversed until the node at the asked index
	node* tmp;
	tmp = head_;
	for(int i = 0 ; i < index ; i++)
	{
		tmp = tmp->next_;
	}
	return tmp; // the address of the node is returned
}

void fonction::add_after_node(node *a, int value, int type)
    {
    	//! Adds a new node is added after the node a
    	//! The new node contains the 2nd and 3rd parameter as value and type respectivly 

        node* p = new node; // creates a new node p
        p->value_ = value; // value is asigned 
        p->type_ = type; // type is asigned

        // p in inserted after a
        p->next_ = a->next_; 
        a->next_ = p;

    }


/**
* Default constructor.
* Generates a random function with sizef_ variables picked randomly in the two possible variables.
*/
fonction::fonction()
{
	int n = 2; /*! <the number of variables is set to 2>*/
    n_ = n; // number of variables
	/*! < Initial formula's size is picked randomly between 1 and n_ >*/
	sizef_ = std::rand()%n_ +1; 

	head_ = NULL; 
    tail_ = NULL;

    /**
    * the linked list is filed with alternatively...
    * - yes(1) or no(0)
    * - an index corresponding to a variable
    * - and(1) or or(0)
    */
	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); 
		add_node(std::rand()%(n_), 2); 
		add_node(std::rand()%2, 3); 
	}
	add_node(std::rand()%2, 1);
	add_node(std::rand()%(n_), 2);

	//! memory is allocated for the table "formule_" containing the full function formula
    formule_ = new int[sizef_*3-1]; 
    //! formle_ is filed
	Formule(); 
}

/**
* Constructor
* @param n is the number of varaibles : n-1 are decriptivs and one is described
* Generates a random function with sizef_ variables picked randomly in the n-1 possible variables
*/
fonction::fonction(int n){ 
	//! initialises rand method's seed to the current time 
	srand(time(NULL)); 
	//! n-1 variables can be used in the formula
	n_ = n-1;
	//!  Initial formula's size is 4
	sizef_ = 4;


	head_ = NULL;
    tail_ = NULL;

    /**
    * the linked list is filed with alternatively...
    * - yes(1) or no(0)
    * - an index corresponding to a variable
    * - and(1) or or(0)
    */
	for(int i=0 ; i<(sizef_-1) ; i++){
		add_node(std::rand()%2, 1); 
		add_node(std::rand()%(n_), 2); 
		add_node(std::rand()%2, 3); 
	}
	add_node(std::rand()%2, 1); 
	add_node(std::rand()%(n_), 2); 

    //! memory is allocated for the table "formule_" containing the full function formula
    formule_ = new int[sizef_*3-1]; 
    //! formle_ is filed
	Formule(); 
}

//! Returns n_, the number of variables available to pick in
int fonction::getN()
{
	return n_;
}

//! Returns sizef_, the size of the formula which is the number of variables it contains
int fonction::getSizef()
{
	return sizef_;
}

//! Fills the array formule with the sequence of number representing the current formula
void fonction::Formule()
{
	node *tmp;
    tmp = head_;
    int i = 0;
    //! each node's value is put in the array
    while (tmp != NULL)
    {
        formule_[i] = tmp->value_;
        tmp = tmp->next_;
        i++;
    }
}

//! Returns the formula as a serie of int contained in an array
int* fonction::getFormule()
{
	Formule(); 
	return formule_; 
}

//! Destructor
fonction::~fonction()
{ 
	//! All the nodes of the linked list are deleted
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

	//! The array formule is deleted
	try  { 
		delete []formule_;
    } 
	catch (...)  { 
        std::cout << "Exception delete []formule_\n"; 
    } 
}


fonction& fonction::operator=(fonction& fct)
{
	//! Assignment of the content of one object fonction to another one

	int SizeLeft = sizef_; //! < current sizef is stocked in the variable SizeLeft >
	//! n is updated
	n_ = fct.getN(); 
	//! sizef is updated
	sizef_ = fct.getSizef(); 
	//! formuleFct is filed with the content of the fonction to be put in the other one
	int* formuleFct = fct.getFormule(); 
	node *tmp;
	tmp = head_;

	/**
	* If the current function is biger than the new one,
	*  - the first nodes's values are replaced with the new ones that are in formuleFct
	*  - the remaining nodes are deleted.
	*
	* If the current and the new function are the same size, values are just replaced.
	*
	* If the new function is bigger,
	*  - the current nodes's values are replaced with the first ones in formuleFct
	*  - new nodes are created for the remaining values of formuleFct.
	*/
	if (sizef_<SizeLeft)
	{
		for(int i=0 ; i<(sizef_*3-1) ; i++) 
		{
			tmp->value_ = formuleFct[i];
    		tmp->type_ = i%3 +1;
    		tmp = tmp->next_;
		}

		tail_ = access_node(sizef_*3-2);
		tail_->next_ = NULL;

		node* tmpA;
		tmpA = tmp->next_;
		
		node* tmpd;
		tmpd = tmpA;
		int i = sizef_*3-1;

		while(tmpA != NULL)
		{

			try
			{
				tmpd = tmpA;
				tmpA = tmpd->next_;
				delete tmpd;
			}
			catch(...){
				std::cout << "Exception de délétion pour i = " << i << std::endl;
			}
			i++;
		}

	}else if (sizef_==SizeLeft)
	{

		for(int i=0 ; i<(sizef_*3-1) ; i++)
		{
			tmp->value_ = formuleFct[i];
    		tmp->type_ = i%3 +1;
    		tmp = tmp->next_;
		}
	}else{

		for(int i=0 ; i<(SizeLeft*3-1) ; i++)
		{
			tmp->value_ = formuleFct[i];
    		tmp->type_ = i%3 +1;
    		tmp = tmp->next_;
		}

		int val;
		int ty;

		for (int i = SizeLeft*3-1 ; i < sizef_*3-1 ; ++i) 
		{

			val = formuleFct[i];
			ty = (i%3 +1);
			add_node(val, ty);

		}
	}


	try
	{
		//! The current forula is deleted
    	delete []formule_;
    	//! Memory is allocated accordingly to the new size of the function
        formule_ = new int[sizef_*3-1];
        //! The array is filled
        Formule();
    }catch(...)
    {
    	std::cout << "Exception Formule Maj" << std::endl;
    }

    return *this;

}

/**
* Method that creates a mutation in a random part of the formula
* There is 5 type of mutation :
*  - type 0 : a 'no' is changed to 'yes' or a 'yes' is changed to 'no' ;
*  - type 1 : an 'and' is changed to 'or' or a 'or' is changed to 'and' ;
*  - type 2 : two variables are exchanged ;
*  - type 3 : a variable is deleted ;
*  - type 4 : a variable is inserted.
*/
void fonction::mutation(){
	//! The type of mutation is picked randomly and stored in mutType
	int mutType = -1;
	do{
		mutType = std::rand()%5;
	}while((sizef_ == 1 && (mutType == 1 || mutType == 3)) || (sizef_ <= 2 && mutType == 2));
	
	int mutRank = -1; 
	int mutRankB = -1;

	switch (mutType)
	{
		//! Mutaion on yes/no
		case 0: {
			//! The rank of yes/no affected by the mutation is picked randomly
			mutRank = std::rand()%(sizef_)*3;
			node *tmp;
			tmp = access_node(mutRank);
			//! O and 1 are inverted
			tmp->value_ = std::abs((tmp->value_)-1);
       	}break;
       	//! Mutaion on and/or
	    case 1: {
	    	//! The rank of and/or affected by the mutation is picked randomly
	    	mutRank = std::rand()%(sizef_)*3-2; 
	    	node *tmp;
			tmp = access_node(mutRank);
			//! O and 1 are inverted
			tmp->value_ = std::abs((tmp->value_)-1); 
       	}break;
       	//! Invertion of two variables
	    case 2:{ 
	    	//! The ranks mutRank and mutRankB of the two variables beeing inverted are picked randomly
	    	mutRank = std::rand()%(sizef_)*3-1;
	    	node *ptrRank;
			ptrRank = access_node(mutRank);
	    	node* ptrRankB;
	    	do 
	    	{
	    		mutRankB = std::rand()%(sizef_)*3-1;
				ptrRankB = access_node(mutRankB);
	    	}while(mutRank==mutRankB);

	    	
	    	//! The two variables are swiched
	    	int temp = ptrRank->value_;
	    	ptrRank->value_ = ptrRankB->value_;
	    	ptrRankB->value_ = temp;

	    }break;
	    //! Variable deletion
	    case 3:{
	    	//! The rank of the variable is picked randomly
	    	mutRank = std::rand()%(sizef_)*3-1;
	    	node *tmp;

	    	//! Deletion at the begining of the list
	    	if (mutRank == 1)
	    	{
	    		// The two nodes after head_ are deleted
	    		del_node_suiv(head_);
	    		del_node_suiv(head_);
	    		// The head_ node is deleted
	    		node* toDel = head_;
	    		head_ = head_->next_;
	    		delete toDel;
	    	}
	    	//! Deletion at the end of the list
	    	else if (mutRank==sizef_*3-2)
	    	{
	    		tmp = access_node(mutRank-3);
				//! Deletion of 3 consecutiv nodes (and/or, yes/no, var)
				del_node_suiv(tmp);
				del_node_suiv(tmp);
				del_node_suiv(tmp);
	    	}
	    	else
	    	{
	    		tmp = access_node(mutRank-2);
				//! Deletion of 3 consecutiv nodes (yes/no, var, and/or)
				del_node_suiv(tmp);
				del_node_suiv(tmp);
				del_node_suiv(tmp);
	    	}

			//! The size of the function is updated
			sizef_--;
			//! Formule_ is updated
	    	delete []formule_;
		    formule_ = new int[sizef_*3-1];
		    Formule();
	    }break;
	    //! Variable insertion
	    case 4:{ 
	    	//! The inserted variable is picked randomly
	    	int addVar = std::rand()%(n_); 
	    	//! The rank of the inserted variable is picked randomly
	    	mutRank = std::rand()%(sizef_)*3; 
	    	
	    	//! Insertion at the begining of the list
	    	if (mutRank == 0)
	    	{
	    		node* p = new node;
	    		//! A random yes/no is added
		        p->value_ = std::rand()%2;
		        p->type_ = 1;
		        p->next_ = head_;
		        head_ = p;
		        //! A random and/or is added
		        add_after_node(p, std::rand()%2, 3);
		        //! The variable is added
		        add_after_node(p, addVar, 2);		        
	    	}
	    	//! Insertion at the end of the list
	    	else if (mutRank == sizef_*3)
	    	{
	    		node *tmp;
		    	tmp = access_node(mutRank-2);
		    	//! The variable is added
		    	add_after_node(tmp, addVar, 2);
		    	//! A random yes/no is added
		    	add_after_node(tmp, std::rand()%2, 1);
		    	//! A random and/or is added
		    	add_after_node(tmp, std::rand()%2, 3);
	    	}
	    	else
	    	{

	    		node *tmp;
		    	tmp = access_node(mutRank-1);
		    	//! A random and/or is added
		    	add_after_node(tmp, std::rand()%2, 3);
		    	//! The variable is added
		    	add_after_node(tmp, addVar, 2);
		    	//! A random yes/no is added
		    	add_after_node(tmp, std::rand()%2, 1);

	    	}
	    	
	    	//! The size of the formula is updates
	    	sizef_++;
	    	//! Formule_ is updated
	    	delete []formule_;
		    formule_ = new int[sizef_*3-1];
		    Formule();

	    }break;
	    //! Code to be executed if mutType doesn't match any cases
	    default:{ 
	    	std::cout << "ERROR" << std::endl;
	    }
	}
}

//! Displays the function as a serie of integers
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

//! Displays the function as a string
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
