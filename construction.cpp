#include "construction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>



construction::construction(const int gen, const int ind, const std::string adress){
    adresse_ = adress; // Adresse du fichier .CSV fourni par l'utilisateur
    numChildren_ = ind; // Nombre d'individus par génération, indiqué par l'utilisateur
    numGenerations_ = gen; // Nombre de générations à réaliser, indiqué par l'utilisateur
	dataManage(); // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur


    storage_ = new fonction[numChildren_];
    predict_ = new bool[numChildren_ * nb_ligtab2D_];
    std::cout << "coucou après crea storage et predict_\n";

    //---------------------TEST OUTPUT PYTHON--------------
    /*fonction testOutput(9);
    std::string newstring = testOutput.formuleToString();
    //testOutput.affichage();
    ecritureOutput(newstring);*/
    //---------------------FIN TEST OUTPUT PYTHON----------

    fonction bestformule_(2);
    best_sse_ = nb_ligtab2D_*nb_coltab2D_ + 1 ; // pire des cas
    best_fitness_ = nb_ligtab2D_*nb_coltab2D_ + 1 ;
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

void construction::generation(fonction& argfonctiongen_){ 

    for(int i = 0; i< numChildren_ ;i++) // on met dans storage l'ensemble des enfants clones
    {
       storage_[i] = argfonctiongen_;
    }

    for(int i =0; i< numChildren_ ;i++) // chaque enfant subit une mutation de type 1,2,3 ou 4 (random)
    {
       storage_[i].mutation();
    }

    prediction(storage_); // stocke dans predict_ les résultats de chaque enfant appliqué aux données

    SSE(storage_); // compare la prédiction de chaque enfant pour chaque ligne, à chaque ligne de la dernière colonne du tab2d
    // modifie l'attribut bestformule_ qui contient désormais le meilleur enfant
 
};


void construction::prediction(fonction *storage){ 

    for(int j=0; j < numChildren_ ; j++) {
        //Calcul de la prédiction pour l'enfant j (pour chaque ligne du tab2d on a une prédiction)
        
        int nb_genes = storage[j].getSizef(); 
        int taillep = storage[j].getSizef()*3-1;
        
        bool res_fonc; // resultat pour chaque ligne que l'on stockera dans le tableau


        for (int k=0; k < nb_ligtab2D_ ;k++) { // pour chaque ligne on calcule la prédiction de l'enfant j
                
                int node_yn = storage[j].getFormule()[0]; // premier Yes ou Not dans formule
                
                int node_vark = tab2d_[k][storage[j].getFormule()[1]]; // valeur que prend le premier gene de la formule à la ligne k
                
                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark); // on applique le Yes ou Not sur cette valeur

                for (int g=1; g < nb_genes; g++) { // calcul la prédiction en prenant en compte toute la formule de l'enfant j
                    
                    int node_yn = storage[j].getFormule()[g*3]; // prochain YN dans la formule

                    int node_vark = tab2d_[k][storage[j].getFormule()[g*3+1]]; // valeur que prend le prochain gène dans la formule à la ligne k

                    int node_ao = storage[j].getFormule()[g*3-1]; // opérateur And ou Or entre les gènes g et g-1
                    
                    if(node_yn == 1) { // si YES
                        
                        if(node_ao == 1) { // si AND
                            res_fonc = res_fonc && node_vark; // applique Yes et AND
                        }
                        else { // si OR
                            res_fonc = res_fonc || node_vark; // applique YES et OR
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
                } // boucle g

                predict_[j*nb_ligtab2D_ + k]= res_fonc; // pour chaque enfant on stocke la prédiction de chaque ligne

                // predict contient pour chaque enfant, la prediction pour chaque ligne
                // la premiere valeur de predict (ligne 0, formule0) est à comparer avec dernière colonne ligne 0
                // la deuxieme valeur de predict (ligne 1, formule0) est à comparer avec dernière colonne ligne 1
        
        } // boucle k
    } // boucle j
} // fin prediction



// calcule la sse et stocke la meilleure formule de la génération dans bestformule_
void construction::SSE(fonction *storage){

    int choix =1; // 0 pour sse, autre chose pour fitness

    if (choix==0){

    for(int j=0; j < numChildren_ ; j++) {

        int sse = 0;

        for (int k=0; k < nb_ligtab2D_ ;k++) { // on parcourt toutes les lignes du tab2d
            
            int valeur = tab2d_[k][nb_coltab2D_-1]; // on stocke la valeur de la dernière colonne
            
            // calcul de la sse : pour chaque ligne, chaque valeur prédite est comparée à la dernière colonne du tab2d
            sse += pow((predict_[j*(nb_ligtab2D_-1)+k] - valeur), 2);

        } // boucle k

        // pour chaque enfant, on a le calcul de sse qui est la somme (des différences entre predit et valeur)
        if (sse <= best_sse_) { // la meilleure sse est la plus basse
            best_sse_ = sse;
            bestformule_ = storage_[j];} // on actualise bestformule_ qui correspond à la sse la plus faible

    } // boucle j

    } 
    else
    { // pour calcul avec fitness

    for(int j=0; j < numChildren_ ; j++) {

        float fitness = 0.0; // autre façon de calculer le score

        for (int k=0; k < nb_ligtab2D_ ;k++) { // on parcourt toutes les lignes du tab2d
            
            int valeur = tab2d_[k][nb_coltab2D_-1]; // on stocke la valeur de la dernière colonne
            
            // calcul de la sse : pour chaque ligne, chaque valeur prédite est comparée à la dernière colonne du tab2d
            fitness += pow((predict_[j*(nb_ligtab2D_-1)+k] - valeur), 2);

        } // boucle k

        // PENALISATION DES OU
        int nbgenes = storage_[j].getSizef();
        int tailleform = nbgenes*3-1;
        int nbdeou = 0;
        for (int i=0; i < tailleform ; i++) {

            if (storage_[j].getFormule()[i*3+2] == 0){ // si le node_ao == 0 c'est un OR
                nbdeou++;
            }
        }

        fitness = fitness * nbdeou/nbgenes;
        std::cout << "best_fitness_ = " << best_fitness_ << std::endl;

        if (fitness < best_fitness_) { // la meilleure fitness_ est la plus basse
            best_fitness_ = fitness;
            bestformule_ = storage_[j];}
    } // boucle j
    }// fin else
};
    

void construction::theCycleOfLife(){ // réalise le nombre de générations donné par l'utilisateur

    std::cout << "\n DANS CYCLE_OF_LIFE " << std::endl;
    std::cout << "\nnb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    std::cout << "\nnb de colonnes de tab : " << nb_coltab2D_ << std::endl;
    fonction fonctiongen_(nb_coltab2D_);
    
    for(int i=0; i < numGenerations_;i++) {

        generation(fonctiongen_);
        fonctiongen_ = bestformule_;
        if (i==0) {
            std::cout << "après la premiere génération on a : " << std::endl;
            bestformule_.affichage();
            std::cout << "nb de gènes dans bestformule_ = " << bestformule_.getSizef() << std::endl;

            }
    }

    std::cout << "\n BEST SSE : " << best_sse_ << std::endl;

    std::cout << "\n BEST fitness : " << best_fitness_ << "\n bestformule :"<< std::endl;

    bestformule_.affichage();


    // pour voir un peu plus d'informations sur la sortie
    int nbgenes = bestformule_.getSizef();
    int tailleform = nbgenes*3-1;
    int nbdeou = 0;
    int nbdeand = 0;

    for (int i=0; i < tailleform ; i++) {

        if (bestformule_.getFormule()[i*3+2] == 0){ // si le node_ao == 0 c'est un OR
            nbdeou++;
        }

        if (bestformule_.getFormule()[i*3+3] == 0){ // si le node_ao == 1 c'est un AND
            nbdeand++;
        }
    }

    std::cout << "nb de ou dans bestformule_ = " << nbdeou << std::endl;
    std::cout << "nb de and dans bestformule_ = " << nbdeand << std::endl;
    std::cout << "nb de gènes dans bestformule_ = " << bestformule_.getSizef() << std::endl;


    //---------ECRITURE FICHIER OUTPUT -> TXT -> PYTHON
    std::string stringaenvoyer = bestformule_.formuleToString();
    //testOutput.affichage();
    ecritureOutput(stringaenvoyer);

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
