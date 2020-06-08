class fonction{
	public:
		fonction();
		fonction(int n); //constructeur
		~fonction(); //destructeur
		void mutation();
		bool execute(bool data); //calcule les résultats pour data
		int* getRankYN();
		int* getRankAO();
		int* getRankVar();
		int* getFormule();
		int getN();
		int getSizef();
		// int getPosition();
		// int getType();
		// int getRang();
		fonction& operator=(fonction& fct);
		void affichage();
		int* formule();

	protected:
		int n_; //number of variables existing
		int sizef_; //number de termes dans la formule
		int* rankYN_;
		int* rankAO_;
		int* rankVar_;
		int sizeYN_;
		int sizeAO_;
		int sizeVar_;
		int* formule_;
		int sizeformule_;
		// int position;
		// int type;
		// int rang;

};
