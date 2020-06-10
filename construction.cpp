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

   
    fonction fonctiongen_(nb_coltab2D_);
    formulegen_ = fonctiongen_.getFormule(); // contient la formule d'un individu dans un tableau

    storage_ = new fonction[numChildren_];
    predict_ = new bool[numChildren_ * nb_ligtab2D_];
    std::cout << "coucou après crea storage et predict_\n";

    //---------------------TEST OUTPUT PYTHON--------------
    fonction testOutput(35);
    std::string newstring = testOutput.formuleToString();
    //testOutput.affichage();
    ecritureOutput(newstring);
    //---------------------FIN TEST OUTPUT PYTHON----------
    fonction test(2);
    bestformule_ = test;
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
   
    for(int i = 0; i <= nb_ligtab2D_; ++i) {
       delete [] tab2d_[i];
    }
        
    delete []tab2d_;
    if (predict_)
    {
       delete []predict_; 
    }
    
    std::cout << "avant storage" << std::endl;
    
    if (storage_)
    {
       delete []storage_; 
    }
    
    
    std::cout << "dest storage" << std::endl;

    //delete []tab_positions;
    //delete []tab_type;
    //delete []tab_rang;
    
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
        //storage_[i].affichage();
    }

    // std::cout << "après mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++)
    {
        storage_[i].mutation();
        std::cout << "\naffiche l'enfant n° " << i << " après mutation " << std::endl;
        storage_[i].affichage();
        int taillep = storage_[i].getN();
        std::cout << "\ntaille p : " << taillep << " pour enfant n° : " << i << std::endl;
    }

    prediction(storage_);

    // check si la valeur de sse n'est pas inférieure à celle de la meilleure fonction de la generation précédente
    //fonctiongen_ = SSE(storage_); //stocke la nouvelle meilleure formule dans l'attribut de la classe

    /* tab_positions[compteurFormules] = formule_.getPosition(); //stocke la mutation réalisée (position)
    tab_type[compteurFormules]= formule_.getType(); //stocke la mutation réalisée (type)
    tab_rang[compteurFormules]= formule_.getRang(); //stocke la mutation réalisée (rang, si interversion)
    compteurFormules =+ 1;*/

    ;
};

// reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la formule_ actuelle)



void construction::prediction(fonction *storage){ 
   
    std::cout << "\n VOUS ETES DANS PREDICTION " << std::endl;

    for(int j=0; j < numChildren_ ; j++) {
        //Calcul de la prédiction pour la formule j
        int sse = 0;
        
        int taillep = storage[j].getN();
        std::cout << "\ntaille p : " << taillep << std::endl;
        
        std::cout << j << "  ième enfant de la génération : " << std::endl;
        storage[j].affichage();
        
        std::cout << "\nprint p pour comparer à affichage : " <<std::endl;
        
        for (int i = 0; i < taillep; ++i){
                    std::cout << storage[j].getFormule()[i] << " ";
                } 

        bool res_fonc; // resultat pour chaque ligne que l'on stockera dans le tableau

        /*

        for (int k=0; k < nb_ligtab2D_ ;k++) { // pour chaque condition (ici 3) on a 6 gènes
                //Calcul du resultat de ma formule
                
                int node_yn = storage[j].getFormule()[k*3]; // Yes ou Not dans formule
                std::cout << "\n node_yn : " << node_yn << std::endl;

                int node_vark = tab2d_[0][storage[j].getFormule()[k*3+1]]; // fait appel à valeur dans tableau
                std::cout << "node_vark : " << node_vark << std::endl;

                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark);

                std::cout << "YN " << node_yn << " node_vark " << node_vark << " nous donne : " << res_fonc << std::endl;
                
                //std::cout << "itération de la ligne : " << k << std::endl;
                for (int g=1; g < nb_coltab2D_ ; g++) { //On ne prend que les (n-1) premiers points observés
                    //YES or NO
                    
                    int node_yn = storage[j].getFormule()[g*3]; 
                    //std::cout << "itération g= : " << g << std::endl;

                    int node_vark = tab2d_[0][storage[j].getFormule()[g*3+1]];
                    //std::cout << "YN sur node_vark : " << node_yn << " " << node_vark <<std::endl;
                    //AND or OR
                    int node_ao = storage[j].getFormule()[g*3-1]; //Si 1 : AND Si 0 : OR
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

    

} // fin prediction



// modifie l'attribut bestformule_
void construction::SSE(fonction *storage){

    int best_sse = nb_ligtab2D_*nb_coltab2D_ + 1 ; // le pire ce serait que toutes les lignes donnent un mauvais résultat
    
    std::cout << "nb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    std::cout << "nb de colonnes de tab : " << nb_coltab2D_ << std::endl;

    int sse = 0;

    for(int j=0; j < numChildren_ ; j++) {

            // predict contient la prediction pour chaque ligne (avec formule appliquée sur n-1 colonnes)
            // la premiere valeur de predict (ligne 0, formule0) est à comparer avec dernière colonne ligne 0
            // la deuxieme valeur de predict (ligne 1, formule0) est à comparer avec dernière colonne ligne 1

        int lastYN = storage_[j].getFormule()[nb_coltab2D_*3-3];
        //std::cout << "lastYN : " << lastYN << std::endl;

        int lastvark = storage_[j].getFormule()[nb_coltab2D_*3-2];
        //std::cout << "lastvark : " << lastvark << std::endl;

        for (int k=0; k < nb_ligtab2D_ ;k++) {
            // on regarde à quelle valeur correspond lastvark pour cette ligne
            int valeur = tab2d_[k][lastvark];
            //std::cout << "valeur dans le tableau pour lastvark : " << valeur << std::endl;

            // on applique lastYN à valeur :
            int result;
            result = (lastYN == 1) * (valeur) + (lastYN == 0) * (!valeur);
            //std::cout << "result de lastYN applique sur valeur : " << result << std::endl;

            // on compare result (dernière colonne pour chaque ligne) à predict


            sse += predict_[j*nb_ligtab2D_+k] - result;



        } // boucle k

        // pour chaque formule, on a le calcul de sse pour toutes les lignes
        if (sse <= best_sse) {
            std::cout << "boucle if" << std::endl;
            best_sse = sse;
            std::cout << "best sse in if : " << best_sse << std::endl;
            
            bestformule_ = storage_[j];}

    } // boucle j

    std::cout << "\n BEST SSE : " << best_sse << std::endl;
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




void construction::ecritureOutput(std::string trucaecrire)
{
    std::ofstream monFlux("output_to_python.txt");
    if(monFlux)  //On teste si tout est OK
    {
        //Tout est OK, on peut utiliser le fichier
        monFlux << trucaecrire;
    }
    else
    {
       std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

}
