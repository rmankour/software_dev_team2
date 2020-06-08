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
		//bool execute(bool data); //calcule les résultats pour data
		int* getFormule();
		int getN();
		int getSizef();
		// int getPosition();
		// int getType();
		// int getRang();
		fonction& operator=(fonction& fct);
		void affichage();

		void add_node(int val, int ty);
		void del_node_suiv(node* preced);
		node* access_node(int index);
		void add_after_node(node *a, int value, int type);
		

	protected:
		int n_; //number of variables existing
		int sizef_; //number de termes dans la formule
		int* formule_;
		// int position;
		// int type;
		// int rang;
		node *head_,*tail_;
		node* gethead();


};
