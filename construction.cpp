#include "construction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>



construction::construction(const int gen, const int ind, const std::string adress){
    adresse_ = adress; // Adresse du fichier .CSV fournie par l'utilisateur
    numChildren_ = ind; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    numGenerations_ = gen; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
	dataManage(); // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur

    fonction f1(nb_coltab2D_);
    fonctiongen_ = f1; // objet fonction
    formulegen_ = f1.getFormule(); // contient la formule d'un individu dans un tableau

    storage_ = new fonction[numChildren_];
    predict_ = new bool[numChildren_ * nb_ligtab2D_];;
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
*/
};

construction::~construction(){ //destructeur
    delete []storage_;
    storage_ = nullptr;
    delete []predict_;
    predict_ = nullptr;
}

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

    // std::cout << "avant mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++)
    {
        storage_[i] = fonctiongen_;
        //storage[i].affichage();
    }

    // std::cout << "après mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++)
    {
        storage_[i].mutation();
        //storage[i].affichage();
    }

    bool* predict_ = prediction(storage_);

    // check si la valeur de sse n'est pas inférieure à celle de la meilleure fonction de la generation précédente
    fonctiongen_ = SSE(storage_); //stocke la nouvelle meilleure formule dans l'attribut de la classe

    /* tab_positions[compteurFormules] = formule_.getPosition(); //stocke la mutation réalisée (position)
    tab_type[compteurFormules]= formule_.getType(); //stocke la mutation réalisée (type)
    tab_rang[compteurFormules]= formule_.getRang(); //stocke la mutation réalisée (rang, si interversion)
    compteurFormules =+ 1;*/

    return ;
};

// reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la formule_ actuelle)


bool* construction::prediction(fonction *storage){ // renvoie un tableau2D de bool
   
    std::cout << "vous etes dans prediction" << std::endl;

    for(int j=0; j < numChildren_ ; j++) {
        //Calcul de la prédiction pour la formule j
        int sse = 0;
        fonction p = storage[j];
        int taillep = p.getN();
        std::cout << "taille p : " << taillep << std::endl;
        
        std::cout << j << " ième enfant de la génération : " << std::endl;
        p.affichage();
        
        std::cout << "print p pour comparer à affichage : " <<std::endl;
        std::cout << p.getRankYN()[0] << " "; // ok
        std::cout << p.getRankAO()[0] << " "; // ok
        std::cout << p.getFormule()[0] << " "; // PAS OK DU TOUT
        /*
        for (int i = 0; i < taillep; ++i){
                    std::cout << p.getformule()[i] << " ";
                } */
        std::cout << "apres la boucle pour print p" << std::endl;
        bool res_fonc; // resultat pour chaque ligne que l'on stockera dans le tableau
/*
        for (int k=0; k < nb_ligtab2D_ ;k++) { // pour chaque condition (ici 3) on a 6 gènes
                //Calcul du resultat de ma formule
                
                int node_yn = p[k*3]; // Yes ou Not dans formule
                //std::cout << "\n node_yn : " << node_yn << std::endl;

                int node_vark = tab2d_[0][p[k*3+1]]; // fait appel à valeur dans tableau
                //std::cout << "node_vark : " << node_vark << std::endl;

                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark);

                //std::cout << "YN " << node_yn << " node_vark " << node_vark << " nous donne : " << res_fonc << std::endl;
                
                //std::cout << "itération de la ligne : " << k << std::endl;
                //std::cout << "itération de la ligne : " << k << std::endl;
                for (int g=1; g < nb_coltab2D_ ; g++) { //On ne prend que les (n-1) premiers points observés
                    //YES or NO
                    
                    int node_yn = p[g*3]; 
                    std::cout << "itération g= : " << g << std::endl;

                    int node_vark = tab2d_[0][p[g*3+1]];
                    //std::cout << "YN sur node_vark : " << node_yn << " " << node_vark <<std::endl;
                    //AND or OR
                    int node_ao = p[g*3-1]; //Si 1 : AND Si 0 : OR
                    //std::cout << "node_ao : " << node_ao << std::endl;

                    //J'assemble le tout YEAH
                    if(node_yn == 1) { // si YES
                        
                        if(node_ao == 1) { // si AND
                            res_fonc = res_fonc && node_vark;
                        }
                        else { // si OR
                            res_fonc = res_fonc || node_vark;
                        }
                    }
                    else { // si NOT
                        if(node_ao == 1) { // si AND
                            res_fonc = res_fonc && !node_vark; // applique NOT et AND
                        }
                        else { // si OR
                            res_fonc = res_fonc || !node_vark; // applique NOT et OR
                        }
                    }
                    //std::cout << "res_fonc entre deux genes : " << res_fonc << std::endl;
                predict_[j*nb_ligtab2D_ + k]= res_fonc;

                } // boucle g

        } // boucle k

*/
    } // boucle j

    return predict_;

} // fin prediction
/*  
            dans SSE : 
            // predict contient la prediction pour chaque ligne (avec formule appliquée sur n-1 colonnes)
            // la premiere valeur de predict (ligne 0, formule0) est à comparer avec dernière colonne ligne 0
            // la deuxieme valeur de predict (ligne 1, formule0) est à comparer avec dernière colonne ligne 1

            int lastYN = p[nb_coltab2D_*3-3];
            //std::cout << "lastYN : " << lastYN << std::endl;

            int lastvark = p[nb_coltab2D_*3-2];
            //std::cout << "lastvark : " << lastvark << std::endl;

            // on regarde à quelle valeur correspond lastvark pour cette ligne
            int valeur = tab2d_[k][lastvark];
            //std::cout << "valeur dans le tableau pour lastvark : " << valeur << std::endl;
} */




fonction& construction::SSE(fonction *storage){

    int best_sse = nb_ligtab2D_*nb_coltab2D_ + 1 ; // le pire ce serait que toutes les lignes donnent un mauvais résultat
   // fonction best_formule;
    std::cout << "nb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    std::cout << "nb de colonnes de tab : " << nb_coltab2D_ << std::endl;

    /*
    //Calcul de la SSE pour chaque fonction enfant
    for(int j=0; j < numChildren_ ; j++) {
        //Calcul de la SSE pour la formule j
        int sse = 0;
        fonction formuleActuelle = storage[j];

        std::cout << j << " ième enfant de la génération : " << std::endl;
        formuleActuelle.affichage();

        // ici j'ai créé un tableau de int (parce que les getters sont des int) qui contient la formule
        // je vérifie que j'ai bien la même chose
        int *p = NULL;
        p = new int[nb_coltab2D_*3-1];
        p = formuleActuelle.formule();
        
        int taillep = nb_coltab2D_*3-1;

        for (int i = 0; i < taillep; ++i){
            std::cout << p[i] << " ";
        }

        bool res_fonc;

        for (int k=0; k < nb_ligtab2D_ ;k++) { // pour chaque condition (ici 3) on a 6 gènes
                //Calcul du resultat de ma formule
                
                int node_yn = p[k*3]; // Yes ou Not dans formule
                //std::cout << "\n node_yn : " << node_yn << std::endl;

                int node_vark = tab2d_[0][p[k*3+1]]; // fait appel à valeur dans tableau
                //std::cout << "node_vark : " << node_vark << std::endl;

                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark);

                //std::cout << "YN " << node_yn << " node_vark " << node_vark << " nous donne : " << res_fonc << std::endl;
                
                std::cout << "itération de la ligne : " << k << std::endl;
                for (int g=1; g < nb_coltab2D_ ; g++) { //On ne prend que les (n-1) premiers points observés
                    //YES or NO
                    
                    int node_yn = p[g*3]; 
                    std::cout << "itération g= : " << g << std::endl;

                    int node_vark = tab2d_[0][p[g*3+1]];
                    //std::cout << "YN sur node_vark : " << node_yn << " " << node_vark <<std::endl;
                    //AND or OR
                    int node_ao = p[g*3-1]; //Si 1 : AND Si 0 : OR
                    //std::cout << "node_ao : " << node_ao << std::endl;

                    
                    //J'assemble le tout YEAH
                    if(node_yn == 1) { // si YES
                        
                        if(node_ao == 1) { // si AND
                            res_fonc = res_fonc && node_vark;
                        }
                        else { // si OR
                            res_fonc = res_fonc || node_vark;
                        }
                    }
                    else { // si NOT
                        if(node_ao == 1) { // si AND
                            res_fonc = res_fonc && !node_vark; // applique NOT et AND
                        }
                        else { // si OR
                            res_fonc = res_fonc || !node_vark; // applique NOT et OR
                        }
                    }
                    //std::cout << "res_fonc entre deux genes : " << res_fonc << std::endl;
                
                }

            int lastYN = p[nb_coltab2D_*3-3];
            //std::cout << "lastYN : " << lastYN << std::endl;

            int lastvark = p[nb_coltab2D_*3-2];
            //std::cout << "lastvark : " << lastvark << std::endl;

            // on regarde à quelle valeur correspond lastvark pour cette ligne
            int valeur = tab2d_[k][lastvark];
            //std::cout << "valeur dans le tableau pour lastvark : " << valeur << std::endl;

            // on applique lastYN à valeur :
            int result;
            result = (lastYN == 1) * (valeur) + (lastYN == 0) * (!valeur);
            //std::cout << "result de lastYN applique sur valeur : " << result << std::endl;
            sse += pow((res_fonc - result),2);

            std::cout << "sse : " << sse << std::endl;
            //On obtient la SSE pour la formule j
            //Comparaison avec la best_sse

        }
        
        if (sse <= best_sse) {
            std::cout << "boucle if" << std::endl;
            best_sse = sse;
            std::cout << "best sse in if : " << best_sse << std::endl;
            
            best_formule = storage[j];}
        

        
        std::cout << "avant delete" << std::endl;
        std::cout << "best sse avant delete : " << best_sse << std::endl;
        //delete[] p;
        std::cout << "apres delete" << std::endl;

    }*/
    std::cout << "\n BEST SSE : " << best_sse << std::endl;
    //return best_formule; 
     //doit retourner un objet
    
} ;

// prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la formule_ finale
void construction::theCycleOfLife(){
    // on pourrait initialiser ici la formule de départ, l'individu racine plutot que de le faire dans le constructeur
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
