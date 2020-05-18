#include "fonction.h"

/*fonction::fonction(int n){ //constructeur n nbr de variables
	n_ = n;
	rankYN_ = new int[n];
	rankAO_ = new int[n-1];
	rankVar_ = new int[n];
}*/

fonction::~fonction(){ //destructeur
	delete []rankYN_;
	rankYN_ = nullptr;
	delete []rankAO_;
	rankAO_ = nullptr;
	delete []rankVar_;
	rankVar_ = nullptr;
}