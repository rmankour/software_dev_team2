#include "construction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>



construction::construction(const int gen, const int ind, const std::string adress){
    adresse_ = adress; // Adresse du fichier .CSV fournie par l'utilisateur
    numChildren_ = ind; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    numGenerations_ = gen; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
	dataManage(); // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur

    fonction f1(5);
    formule_ = f1;
    /*
    fonction formule_; // Devrait générer une formule au pif si la classe marche bien
    int compteurFormules = 0; // Permet d'avancer dans l'historique composé des 3 tableaux à suivre
    int tab_positions[numGenerations+1]; // stocke la position des mutations
    int tab_type[numGenerations+1]; // stocke le type de mutations
    int tab_rang[numGenerations+1]; // stocke le rang avec le lequel se fait un échange en cas d'interversion (-1 si pas d'interversion)
    // Les mutations sont stockées dans l'ordre d'occurence
    theCycleOfLife();*/

    //écrire les ligne de code pour extraire les tableaux (2 pour formule_ et 3 pour historique) en attribut de obj dans un fichier texte :

/*  // OUTPUT == un fichier avec 3 lignes : les 3 attributs de l'objet formule_ en cours
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
        for (i=0 ; i<numGenerations-1 ; i++)
        {
             myfile << formule_.getRankYN()[i]; << ",";
        }
        myfile << formule_.getRankYN()[numGenerations]; << "\n";

        for (int i=0 ; i<numGenerations-1 ; i++)
        {
             myfile << formule_.getRankAO()[i]; << ",";
        }
        myfile << formule_.getRankAO()[numGenerations]; << "\n";

        for (int i=0 ; i<numGenerations-1 ; i++)
        {
             myfile << formule_.getRankVar()[i]; << ",";
        }
        myfile << formule_.getRankAO()[numGenerations]; << "\n";

        myfile.close();
    }
    else cout << "Unable to open file";
}; */



void construction::dataManage()
{
	std::ifstream ip(adresse_); //ouvre un flux appellé ip avec l'adress du fichier csv

	if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

	std::string charac;
	getline(ip,charac,'\n'); //getline : récupère sous forme de string tout ce qu'il y a dans le flux jusqu'au cara indiqué ici '\n'

	//---------------------------------
	// PRETRAITEMENT : CHERCHE NB LIGNES / COLONNES

	//On cherche le nombre de colonnes
	int n = std::count(charac.begin(), charac.end(), ',');
	n++;

	 // Donne le nombre de colonnes

	//On cherche le nombre de lignes du csv
	int m = 0;
	while (ip.peek()!=EOF)
	{
		getline(ip,charac,'\n');
		m++;

	}
	//std::cout << m << " ; "<< n << std::endl;
	//m est le nombre de ligne de notre fichier .csv ainsi :

	ip.close();//ferme le flux

	//---------------------------------------------------------
	// LECTURE DU CSV
	//
	std::ifstream ip2(adresse_);
	getline(ip2,charac,'\n');//zappe la première ligne d'entête


	tab2d_ = new bool*[m];
	for(int i = 0; i <= m; ++i) {
 	   tab2d_[i] = new bool[n-2];
	}
	nb_ligtab2D_ = m;
	nb_coltab2D_ = n-1;

	getline(ip2,charac,',');//zappe la première
	while (ip2.peek()!=EOF)
	{

		for (int i=0 ; i<=m-1 ; i++) // parcourt les lignes m (de 0 à 577)
		{

			for (int j=0 ; j<=n-2 ; j++) // parcourt les colonnes n-2 (de 0 à 119)
			{
				//std::cout << "\n i = " << i << "   j = " << j << std::endl;
				getline(ip2,charac,',');//zappe la première occurence de chaque ligne (nom de l'expérience)
				tab2d_[i][j] = (charac[0] == '1');
				//std::cout << tab2d_[i][j];
			}
			//std::cout << std::endl;
		}
	}
	ip2.close();

};

bool construction::lectureCaseTab(int lig, int col)
{
	if (!tab2d_)
	{
		return 0;
	}
	return tab2d_[lig][col];
};

void construction::generation(){
	fonction* storage = new fonction[numChildren_];

    std::cout << "avant mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++)
    {
        storage[i] = formule_;
        storage[i].affichage();
    }

    std::cout << "après mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++)
    {
        storage[i].mutation();
        storage[i].affichage();
    }

    // check si la valeur de sse n'est pas inférieure à celle de la meilleure fonctione de la generation précédente
    // formule_ = SSE(storage) //stocke la nouvelle meilleure formule dans l'attribut de la classe

    /* tab_positions[compteurFormules] = formule_.getPosition(); //stocke la mutation réalisée (position)
    tab_type[compteurFormules]= formule_.getType(); //stocke la mutation réalisée (type)
    tab_rang[compteurFormules]= formule_.getRang(); //stocke la mutation réalisée (rang, si interversion)
    compteurFormules =+ 1;*/

    delete []storage;
    storage = nullptr;

    return ;
/*
	fonction f1(3);
	fonction* storage = new fonction[5];
	storage[0] = f1;
	storage[1] = f1;
	for(int i =0; i<3;i++)
	{
		//storage[i] = f1;
		//std::cout << storage[i].getRankYN()[i];
		//std::cout << storage[i].getRankAO()[i];
		//std::cout << storage[i].getRankVar()[i] << std::endl;


	}/*
	storage[0].mutation();
	for(int i =0; i<3;i++)
	{
		std::cout << storage[i].getRankYN()[i];
		std::cout << storage[i].getRankAO()[i];
		std::cout << storage[i].getRankVar()[i] << std::endl;


	}

	/*
	fonction f1(528);
	formule_ = &f1; // -> formule est de type fonction* sans l'étoile ça serait simple mais ça marche pas :'(
	*/
	/*
	fonction storage[numChildren_]; // segmentation fault tel quel:'( -> faut il utiliser "fonction* storage[numChildren_]" ???
    int i = 0;
    while(i<numChildren_){
        storage[i]=formule_;// on peut remplacer formule par f1 objet de type fonction.
        storage[i].mutation();
        i++;
    }*/
    //formule_ = SSE(storage) //stocke la nouvelle meilleure formule dans l'attribut de la classe
    /*
    tab_positions[compteurFormules] = formule_.getPosition(); //stocke la mutation réalisée (position)
    tab_type[compteurFormules]= formule_.getType(); //stocke la mutation réalisée (type)
    tab_rang[compteurFormules]= formule_.getRang(); //stocke la mutation réalisée (rang, si interversion)
    compteurFormules =+ 1;*/
};

// reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la formule_ actuelle)


fonction construction::SSE(const fonction* &tab_fonctions){
/*
    //int best_sse = 0;
    //Calcul de la SSE pour chaque fonction enfant
    for(int j=0; j< numChildren; j++) {
        //Calcul de la SSE pour la formule j
        int sse = 0;
        for (int i=0; i<nb_ligtab2D;i++) {
            //Calcul du resultat de ma formule
            fonction formuleActuelle = tab_fonctions[j];

            bool node_yn = formuleActuelle.getRankYN()[0];
            bool node_vark = tab2d_[i][0];
            int resultat_de_ma_fonction = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark)

            for (int k=1;k<nb_coltab2D-1 ;k++) { //On ne prend que les (n-1) premiers points observés
                //YES or NO
                node_yn = formuleActuelle.getRankYN()[k];//Si 1 : YES Si 0 : OR
                //Variable k
                node_vark = tab2d_[i][k];
                //AND or OR
                bool node_ao = formuleActuelle.getRankAO()[k-1];//Si 1 : AND Si 0 : OR

                //J'assemble le tout YEAH
                if(node_yn) {
                    if(node_ao) {
                        resultat_de_ma_fonction = resultat_de_ma fonction && node_vark;
                    }
                    else {
                        resultat_de_ma_fonction = resultat_de_ma fonction || node_vark;
                    }
                }
                else {
                    if(node_ao) {
                        resultat_de_ma_fonction = resultat_de_ma fonction && !node_vark;
                    }
                    else {
                        resultat_de_ma_fonction = resultat_de_ma fonction || !node_vark;
                    }
                }

            }
            sse += (resultat_de_ma_fonction - tab2d_[i][nb_coltab2D])²;
        }
        //On obtient la SSE pour la formule j
        //Comparaison avec la best_sse
        if (sse <= best_sse) {
            best_sse = sse;
            formule_ = tab_fonctions[j];
        }
    }
    return; //doit retourner un objet
    */
} ;


// prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la formule_ finale
void construction::theCycleOfLife(){
    /*i = 0;
    while (i < numGenerations){
        generation();
    }*/

};
int construction::get_nblig()
{
	if(!nb_ligtab2D_)
	{
		return 0;
	}
	return nb_ligtab2D_;
};
int construction::get_nbcol()
{
	if(!nb_coltab2D_)
	{
		return 0;
	}
	return nb_coltab2D_;
};
