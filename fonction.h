class fonction{
	public:
		fonction() = default;
		fonction(int n); //constructeur
		mutation();
		bool execute(bool data); //calcule les résultats pour data


	protected:
		int n; //number of variables in the function
		int rankYN[n];
		int rankAO[n-1];
		int rankVar[n];


};