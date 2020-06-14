#include "construction.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>


//! Constructeur de la classe prenant les paramètres fournis par l'utilisateur afin de construire la formule expliquant le mieux les données et les scores correspondants

construction::construction(const int gen, const int ind, const std::string adress){
    // Adresse du fichier .CSV fourni par l'utilisateur
    adresse_ = adress;
    // Nombre d'individus par génération, indiqué par l'utilisateur
    numChildren_ = ind;
    // Nombre de générations à réaliser, indiqué par l'utilisateur
    numGenerations_ = gen;
    // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur
	dataManage();


    storage_ = new fonction[numChildren_];
    predict_ = new bool[numChildren_ * nb_ligtab2D_];

    //---------------------TEST OUTPUT PYTHON--------------
    /*fonction testOutput(9);
    std::string newstring = testOutput.formuleToString();
    //testOutput.affichage();
    ecritureOutput(newstring);*/
    //---------------------FIN TEST OUTPUT PYTHON----------

    fonction bestformule_(2);
    // pire valeur possible de SSE, dans le cas où il n'y a aucune correspondance
    best_sse_ = nb_ligtab2D_*nb_coltab2D_ + 1 ;
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

//! Destructeur de la classe
construction::~construction(){

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

//! Méthode pour importer les données fournies par l'utilisateur sous la forme d'une tableau en 2D
void construction::dataManage()
{
    //ouvre un flux appellé ip avec l'adress du fichier csv
	std::ifstream ip(adresse_);

	if(!ip.is_open()) std::cout << "ERROR: File Open" << '\n';

	std::string charac;
    //getline : récupère sous forme de string tout ce qu'il y a dans le flux jusqu'au cara indiqué ici '\n'

	getline(ip,charac,'\n');

	//---------------------------------
	// PRETRAITEMENT : CHERCHE NB LIGNES / COLONNES

	// On cherche le nombre de colonnes
    // n donne le nombre de colonnes
	int n = std::count(charac.begin(), charac.end(), ',');
	n++;



	//On cherche le nombre de lignes du csv
    //m est le nombre de ligne de notre fichier .csv
	int m = 0;
	while (ip.peek()!=EOF)
	{
		getline(ip,charac,'\n');

		m++;

	}
	//std::cout << m << " ; "<< n << std::endl;

    //ferme le flux
	ip.close();

	//---------------------------------------------------------
	// LECTURE DU CSV
	//
	std::ifstream ip2(adresse_);
    //zappe la première ligne d'entête
	getline(ip2,charac,'\n');


	tab2d_ = new bool*[m];
	for(int i = 0; i <= m; ++i) {
 	   tab2d_[i] = new bool[n-2];
	}
	nb_ligtab2D_ = m;
	nb_coltab2D_ = n-1;
    //zappe la première
	getline(ip2,charac,',');
	while (ip2.peek()!=EOF)
	{
        // parcourt les lignes m (de 0 à 577)
		for (int i=0 ; i<=m-1 ; i++)
		{
            // parcourt les colonnes n-2 (de 0 à 119)
			for (int j=0 ; j<=n-2 ; j++)
			{
				//std::cout << "\n i = " << i << "   j = " << j << std::endl;
                //zappe la première occurence de chaque ligne (nom de l'expérience)
				getline(ip2,charac,',');
				tab2d_[i][j] = (charac[0] == '1');
				//std::cout << tab2d_[i][j];
			}
			//std::cout << std::endl;
		}
	}
	ip2.close();

};

//! Méthode pour return une valeur (bool) du tableau en lui fournissant le numéro de la ligne et de la colonne (int)
bool construction::lectureCaseTab(int lig, int col)
{
	if (!tab2d_)
	{
		return 0;
	}
	return tab2d_[lig][col];
};

//! Méthode pour construire les enfants d'une génération, stockés dans le tableau storage, à partir de l'objet fonction correspondant au parent en input
void construction::generation(fonction& argfonctiongen_){
    // on met dans storage l'ensemble des enfants clones
    for(int i = 0; i< numChildren_ ;i++)
    {
       storage_[i] = argfonctiongen_;
    }
    // chaque enfant subit une mutation de type 1,2,3 ou 4 (random)
    for(int i =0; i< numChildren_ ;i++)
    {
       storage_[i].mutation();
    }
    // stocke dans predict_ les résultats de chaque enfant appliqué aux données
    prediction(storage_);

    // compare la prédiction de chaque enfant pour chaque ligne, à chaque ligne de la dernière colonne du tab2d
    // modifie l'attribut bestformule_ qui contient désormais le meilleur enfant
    SSE(storage_);

};

//! Méthode prenant en input : tableau storage avec tous les enfants mutés
//! modifie l'argument predict qui est un tableau avec pour chaque enfant, la prédiction pour chaque ligne (0 ou 1)
void construction::prediction(fonction *storage){

    //Calcul de la prédiction pour l'enfant j (pour chaque ligne du tab2d on a une prédiction)
    for(int j=0; j < numChildren_ ; j++) {

        int nb_genes = storage[j].getSizef();
        int taillep = storage[j].getSizef()*3-1;
        // resultat pour chaque ligne que l'on stockera dans le tableau
        bool res_fonc;

        // pour chaque ligne on calcule la prédiction de l'enfant j
        for (int k=0; k < nb_ligtab2D_ ;k++) {
                // premier Yes ou Not dans formule
                int node_yn = storage[j].getFormule()[0];
                // valeur que prend le premier gene de la formule à la ligne k
                int node_vark = tab2d_[k][storage[j].getFormule()[1]];
                // on applique le Yes ou Not sur cette valeur
                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark);
                // calcul la prédiction en prenant en compte toute la formule de l'enfant j
                for (int g=1; g < nb_genes; g++) {
                    // prochain YN dans la formule
                    int node_yn = storage[j].getFormule()[g*3];
                    // valeur que prend le prochain gène dans la formule à la ligne k
                    int node_vark = tab2d_[k][storage[j].getFormule()[g*3+1]];
                    // opérateur And ou Or entre les gènes g et g-1
                    int node_ao = storage[j].getFormule()[g*3-1];
                    // si YES
                    if(node_yn == 1) {
                        // si AND
                        if(node_ao == 1) {
                            // applique Yes et AND
                            res_fonc = res_fonc && node_vark;
                        }
                        // si OR
                        else {
                            // applique YES et OR
                            res_fonc = res_fonc || node_vark;
                        }
                    }
                    // si NOT
                    else {
                        // si AND
                        if(node_ao == 1) {
                            // applique NOT et AND
                            res_fonc = res_fonc && !node_vark;
                        }
                        // si OR
                        else {
                            // applique NOT et OR
                            res_fonc = res_fonc || !node_vark;
                        }
                    }
                } // boucle g

                /* predict contient pour chaque enfant, la prediction pour chaque ligne
                \ la premiere valeur de predict (ligne 0, formule0) est à comparer avec dernière colonne ligne 0
                \ la deuxieme valeur de predict (ligne 1, formule0) est à comparer avec dernière colonne ligne 1
                \ pour chaque enfant on stocke la prédiction de chaque ligne */
                predict_[j*nb_ligtab2D_ + k]= res_fonc;

        // boucle k
        }
    // boucle j
    }
// fin prediction
}


//! Méthode prenant un tableau d'objets fonction correspondant aux enfants d'une génération
//! calcule la sse et stocke la meilleure formule de la génération dans bestformule_
void construction::SSE(fonction *storage){
    // 0 pour sse, autre chose pour fitness
    int choix =0;

    if (choix==0){

    for(int j=0; j < numChildren_ ; j++) {

        int sse = 0;
        // on parcourt toutes les lignes du tab2d
        for (int k=0; k < nb_ligtab2D_ ;k++) {
            // on stocke la valeur de la dernière colonne
            int valeur = tab2d_[k][nb_coltab2D_-1];

            // calcul de la sse : pour chaque ligne, chaque valeur prédite est comparée à la dernière colonne du tab2d
            sse += pow((predict_[j*(nb_ligtab2D_-1)+k] - valeur), 2);
        // boucle k
        }

        // pour chaque enfant, on a le calcul de sse qui est la somme (des différences entre predit et valeur)
        if (sse < best_sse_) {
            // la meilleure sse est la plus basse
            best_sse_ = sse;
            // on actualise bestformule_ qui correspond à la sse la plus faible
            bestformule_ = storage_[j];
        }else{
            // si meme score que la formule actuelle dans bestformule_
            if(sse == best_sse_){
                    //  conserver l'enfant j seulement s'il est plus court
                    if(bestformule_.getSizef() > storage_[j].getSizef()){
                        best_sse_ = sse;
                        bestformule_ = storage_[j];
                    }
            }
        //fin du else
        }
    // boucle j
    }

    }
    // pour calcul avec fitness
    else
    {

    // calcul de la sse : pour chaque ligne, chaque valeur prédite est comparée à la dernière colonne du tab2d
    for(int j=0; j < numChildren_ ; j++) {
        // autre façon de calculer le score
        float fitness = 0.0;
        // on parcourt toutes les lignes du tab2d
        for (int k=0; k < nb_ligtab2D_ ;k++) {
            // on stocke la valeur de la dernière colonne
            int valeur = tab2d_[k][nb_coltab2D_-1];


            fitness += pow((predict_[j*(nb_ligtab2D_-1)+k] - valeur), 2);
        // boucle k
        }

        // PENALISATION DES OU
        int nbgenes = storage_[j].getSizef();
        int tailleform = nbgenes*3-1;
        int nbdeou = 0;
        for (int i=0; i < tailleform ; i++) {
            // si le node_ao == 0 c'est un OR
            if (storage_[j].getFormule()[i*3+2] == 0){
                nbdeou++;
            }
        }

        fitness = fitness * nbdeou/nbgenes;
        std::cout << "best_fitness_ = " << best_fitness_ << std::endl;
        // la meilleure fitness_ est la plus basse
        if (fitness < best_fitness_) {
            best_fitness_ = fitness;
            bestformule_ = storage_[j];}
    // boucle j
    }
    // fin else
    }
    std::string fitnessstring = std::to_string((float)best_sse_/nb_ligtab2D_ * 100);
    fitnessstring += " ";
    ecritureFitness(fitnessstring);
};

//! réalise le nombre de générations demandé par l'utilisateur
void construction::theCycleOfLife(){

    std::cout << "\n DANS CYCLE_OF_LIFE " << std::endl;
    std::cout << "\nnb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    std::cout << "\nnb de colonnes de tab : " << nb_coltab2D_ << std::endl;
    fonction fonctiongen_(nb_coltab2D_);
    flushFitnessFile();
    ecritureFitness("100 ");  
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
    std::cout << "nb de lignes du tab2d : " << nb_ligtab2D_ << std::endl;
    float percent = (float)best_sse_/nb_ligtab2D_ * 100;
    std::cout << "nb d'erreurs : " << percent << " %" << std::endl;
    std::cout << "bestformule_ : " << std::endl;

    bestformule_.affichage();


    // pour voir un peu plus d'informations sur la sortie
    int nbgenes = bestformule_.getSizef();
    int tailleform = nbgenes*3-1;
    int nbdeou = 0;
    int nbdeand = 0;

    for (int i=0; i < tailleform ; i++) {
        // si le node_ao == 0 c'est un OR
        if (bestformule_.getFormule()[i*3+2] == 0){
            nbdeou++;
        }
        // si le node_ao == 1 c'est un AND
        if (bestformule_.getFormule()[i*3+3] == 0){
            nbdeand++;
        }
    }

    std::cout << "nb de OU dans bestformule_ = " << nbdeou << std::endl;
    std::cout << "nb de AND dans bestformule_ = " << nbdeand << std::endl;
    std::cout << "nb de gènes dans bestformule_ = " << bestformule_.getSizef() << std::endl;


    //---------ECRITURE FICHIER OUTPUT -> TXT -> PYTHON
    std::string stringaenvoyer = bestformule_.formuleToString();
    //testOutput.affichage();
    ecritureOutput(stringaenvoyer);

};

//! Méthode pour donner le nombre de lignes du tableau
int construction::get_nblig()
{
	if(!nb_ligtab2D_)
	{
		return 0;
	}
	return nb_ligtab2D_;
};

//! Méthode pour donner le nombre de colonnes du tableau
int construction::get_nbcol()
{
	if(!nb_coltab2D_)
	{
		return 0;
	}
	return nb_coltab2D_;
};

//! Méthode pour ouvrir un fichier texte et y écrire le string donné en argument : ici on exporte la formule au format txt
void construction::ecritureOutput(std::string trucaecrire)
{
    std::ofstream monFlux("output_to_python.txt");
    //On teste si tout est OK
    if(monFlux)
    {
        //Tout est OK, on peut utiliser le fichier
        monFlux << trucaecrire;
    }
    else
    {
       std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }

}
//! Méthode pour ouvrir un fichier texte et y écrire le string donné en argument : ici on exporte la fitness au format txt
void construction::ecritureFitness(std::string trucaecrire)
{
    std::ofstream monFlux("fitness_to_python.txt", std::ios_base::app);
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
//! Méthode pour vider le fichier txt contenant la fitness
void construction::flushFitnessFile()
{
    std::ofstream monFlux("fitness_to_python.txt");
    if(monFlux)  //On teste si tout est OK
    {
        //Tout est OK, on peut utiliser le fichier
        monFlux << "";
    }
    else
    {
       std::cout << "ERREUR: Impossible d'ouvrir le fichier." << std::endl;
    }
}
