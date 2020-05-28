#include "construction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>



construction::construction(const int gen, const int ind, const std::string adress){
    adresse_ = adress; // Adresse du fichier .CSV fournie par l'utilisateur
    int numChildren = ind; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations = gen; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    /*dataManage(); // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur
    fonction formule_; // Devrait générer une formule au pif si la classe marche bien
    int compteurFormules = 0; // Permet d'avancer dans l'historique composé des 3 tableaux à suivre
    int tab_positions[numGenerations+1]; // stocke la position des mutations
    int tab_type[numGenerations+1]; // stocke le type de mutations
    int tab_rang[numGenerations+1]; // stocke le rang avec le lequel se fait un échange en cas d'interversion (-1 si pas d'interversion)
    // Les mutations sont stockées dans l'ordre d'occurence
    theCycleOfLife();*/
};


void construction::dataManage()
{
	std::ifstream ip(adresse_); //ouvre un flux appellé ip avec l'adress du fichier csv

	if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

	std::string charac;
	getline(ip,charac,'\n'); //getline : récupère sous forme de string tout ce qu'il y a dans le flux jusqu'au cara indiqué ici '\n'

	//---------------------------------
	// PRETRAITEMENT : CHERCHE NB LIGNES / COLONNES

	//On cherche le nombre de colonnes
	size_t n = std::count(charac.begin(), charac.end(), ',');
	n++;

	 // Donne le nombre de colonnes

	//On cherche le nombre de lignes du csv
	size_t m = 0;
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
	for(size_t i = 0; i <= m; ++i) {
 	   tab2d_[i] = new bool[n-2];
	}
	nb_ligtab2D_ = m;
	nb_coltab2D_ = n-1;

	getline(ip2,charac,',');//zappe la première
	while (ip2.peek()!=EOF)
	{

		for (size_t i=0 ; i<=m-1 ; i++) // parcourt les lignes m (de 0 à 577)
		{

			for (size_t j=0 ; j<=n-2 ; j++) // parcourt les colonnes n-2 (de 0 à 119)
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

bool construction::lectureCaseTab(size_t lig, size_t col)
{
	if (!tab2d_)
	{
		return 0;
	}
	return tab2d_[lig][col];
};

void construction::generation(){
/*
    fonction storage[numChildren];
    i = 0;
    while(i<numChildren){
        storage[i]=formule_;
        storage[i].mutation();
    }
    formule_ = SSE(storage) //stocke la nouvelle meilleure formule dans l'attribut de la classe
    tab_positions[compteurFormules] = formule_.position; //stocke la mutation réalisée (position)
    tab_type[compteurFormules]= formule_.type; //stocke la mutation réalisée (type)
    tab_rang[compteurFormules]= formule_.rang; //stocke la mutation réalisée (rang, si interversion)
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
size_t construction::get_nblig()
{
	if(!nb_ligtab2D_)
	{
		return 0;
	}
	return nb_ligtab2D_;
};
size_t construction::get_nbcol()
{
	if(!nb_coltab2D_)
	{
		return 0;
	}
	return nb_coltab2D_;
};
