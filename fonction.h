#include <string>

//! structure utilisée pour employer une linked list

struct node
{
    int value_;
    //! Les types sont 1 : YN, 2 : Var, 3 : AO
    int type_;
    node *next_;
};

//! classe permettant de stocker une formule
class fonction{
	public:
        /**
        * Default constructor.
        * Generates a random function with sizef_ variables picked randomly in the two possible variables.
        */
		fonction();
        /**
        * Constructor
        * @param n is the number of varaibles : n-1 are decriptivs and one is described
        * Generates a random function with sizef_ variables picked randomly in the n-1 possible variables
        */
		fonction(int n);
        //! destructor
		~fonction();
        /**
        * Method that creates a mutation in a random part of the formula
        * There is 5 type of mutation :
        *  - type 0 : a 'no' is changed to 'yes' or a 'yes' is changed to 'no' ;
        *  - type 1 : an 'and' is changed to 'or' or a 'or' is changed to 'and' ;
        *  - type 2 : two variables are exchanged ;
        *  - type 3 : a variable is deleted ;
        *  - type 4 : a variable is inserted.
        */
		void mutation();
        //! Fills the array formule with the sequence of number representing the current formula
		void Formule();
        //! Returns the formula as a serie of int contained in an array
		int* getFormule();
        //! Returns n_, the number of variables available to pick in
		int getN();
        //! Returns sizef_, the size of the formula which is the number of variables it contains
		int getSizef();
        //! Assignment operator
        //! Assignment of the content of one object fonction to another one
		fonction& operator=(fonction& fct);
        //! Displays the function as a serie of integers
		void affichage();
        //! Displays the function as a string
        std::string formuleToString();

        //! Adds a node containing the 1st parameter as its value and the 2nd parameter as its type
		void add_node(int val, int ty);
        //! Deletes the node right after the one given as parameter
		void del_node_suiv(node* preced);
        //! Returns the address of the node at the index given as parameter
        //! Each node is traversed until the node at the asked index
		node* access_node(int index);
        //! Adds a new node is added after the node a
        //! The new node contains the 2nd and 3rd parameter as value and type respectivly
		void add_after_node(node *a, int value, int type);


	protected:
        //! number of variables existing
		int n_ = 1;
        //! number de termes dans la formule
		int sizef_ = 1;
        //! table containing the full function formula
		int* formule_;
        //! start and end of the linked list
		node *head_,*tail_;

};
