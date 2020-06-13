#include <string>
struct node
{
    int value_;
    int type_; // 1 : YN, 2 : Var, 3 : AO
    node *next_;
};

class fonction{
	public:
		fonction();
		fonction(int n); //constructeur
		~fonction(); //destructeur
		void mutation();
		void Formule();
		int* getFormule();
		int getN();
		int getSizef();
		fonction& operator=(fonction& fct);
		void affichage();
		std::string formuleToString();

	protected:
		void add_node(int val, int ty);
		void del_node_suiv(node* preced);
		node* access_node(int index);
		void add_after_node(node *a, int value, int type);
		int n_ = 1; //number of variables existing
		int sizef_ = 1; //number de termes dans la formule
		int* formule_;
		int sizeformule_;
		node *head_,*tail_;


};
