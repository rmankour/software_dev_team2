class fonction{
	public:
		fonction(int n); //constructeur
		~fonction(); //destructeur
		void mutation();
		bool execute(bool data); //calcule les résultats pour data
		int* getRankYN();
		int* getRankAO();
		int* getRankVar();


	protected:
		int n_; //number of variables in the function
		int* rankYN_;
		int* rankAO_;
		int* rankVar_;
		int sizeYN_;
		int sizeAO_;
		int sizeVar_;
		
};