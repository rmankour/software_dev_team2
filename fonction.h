class fonction{
	public:
		fonction(int n); //constructeur
		~fonction(); //destructeur
		mutation();
		bool execute(bool data); //calcule les résultats pour data


	protected:
		int n_; //number of variables in the function
		int* rankYN_;
		int* rankAO_;
		int* rankVar_;


};