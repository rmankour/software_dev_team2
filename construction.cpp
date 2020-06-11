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

   
    fonction fonctiongen_(nb_coltab2D_);
    fonctiongen_.affichage();
    formulegen_ = fonctiongen_.getFormule(); // contient la formule d'un individu dans un tableau

    storage_ = new fonction[numChildren_];
    predict_ = new bool[numChildren_ * nb_ligtab2D_];
    std::cout << "coucou après crea storage et predict_\n";

    //---------------------TEST OUTPUT PYTHON--------------
    fonction testOutput(9);
    std::string newstring = testOutput.formuleToString();
    //testOutput.affichage();
    ecritureOutput(newstring);
    //---------------------FIN TEST OUTPUT PYTHON----------

    fonction bestformule_(2);
    best_sse_ = nb_ligtab2D_*nb_coltab2D_ + 1 ; // pire des cas
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
    std::cout << "fonctiongen_ au debut de la génération avant mutation : " << std::endl;
    fonctiongen_.affichage();
    // std::cout << "avant mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++) // on met dans storage l'ensemble des enfants clones
    {

        storage_[i] = fonctiongen_;
        storage_[i].affichage();
    }

    // std::cout << "après mutation : " << std::endl;
    for(int i =0; i< numChildren_ ;i++) // chaque enfant subit une mutation
    {
        storage_[i].mutation();
        //std::cout << "\naffiche l'enfant n° " << i << " après mutation " << std::endl;
        //storage_[i].affichage();
        int nbgenes = storage_[i].getSizef();
        //std::cout << "\nnb de gènes = " << nbgenes << " pour enfant n° : " << i << std::endl;
    }

    prediction(storage_); // calcule pour chaque enfant une prédiction (pour chaque ligne du tab2d)

    SSE(storage_); // compare la prédiction de chaque enfant pour chaque ligne, à chaque ligne de la dernière colonne du tab2d
    // modifie l'attribut bestformule_ qui contient désormais le meilleur enfant
 
};

// reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la formule_ actuelle)



void construction::prediction(fonction *storage){ 
   
    std::cout << "\n VOUS ETES DANS PREDICTION " << std::endl;
    //std::cout << "nb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    //std::cout << "nb de colonnes de tab : " << nb_coltab2D_ << std::endl;



    for(int j=0; j < numChildren_ ; j++) {
        //Calcul de la prédiction pour la formule j
        
        int nb_genes = storage[j].getSizef(); 
        int taillep = storage[j].getSizef()*3-1;
        //std::cout << "\ntaille p (nb de cases) : " << taillep << std::endl;
        
        std::cout << "\n" << j << "  ième enfant de la génération : " << std::endl;
        storage[j].affichage();
        
        //std::cout << "\nprint enfant pour comparer à affichage : " <<std::endl;
        
        // à enlever une fois le code fonctionnel
    /*    for (int i = 0; i < taillep; ++i){
                    std::cout << storage[j].getFormule()[i] << " ";
                } */

        bool res_fonc; // resultat pour chaque ligne que l'on stockera dans le tableau

        

        for (int k=0; k < nb_ligtab2D_ ;k++) { // pour chaque condition (ici 3) on a 6 gènes
                //Calcul du resultat de ma formule

                //std::cout << "\n ligne n° : " << k <<std::endl;

                int node_yn = storage[j].getFormule()[0]; // Yes ou Not dans formule
                //std::cout << "\n node_yn : " << node_yn << std::endl;

                int node_vark = tab2d_[k][storage[j].getFormule()[1]]; // fait appel à valeur dans tableau
                //std::cout << "node_vark : " << node_vark << std::endl;

                res_fonc = (node_yn == 1) * (node_vark) + (node_yn == 0) * (!node_vark);

                //std::cout << "YN " << node_yn << " node_vark " << node_vark << " nous donne : " << res_fonc << std::endl;
                
                //std::cout << "itération de la ligne : " << k << std::endl;
                for (int g=1; g < nb_genes; g++) { // il y nb_genes dans formule
                    //YES or NO
                    
                    int node_yn = storage[j].getFormule()[g*3]; 
                    //std::cout << "itération g= : " << g << std::endl;

                    int node_vark = tab2d_[k][storage[j].getFormule()[g*3+1]];
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

                } // boucle g
                predict_[j*nb_ligtab2D_ + k]= res_fonc;
                //std::cout << "predict : " << predict_[j*nb_ligtab2D_ + k] << std::endl;

        } // boucle k
        
    } // boucle j

    

} // fin prediction



// modifie l'attribut bestformule_
void construction::SSE(fonction *storage){


    for(int j=0; j < numChildren_ ; j++) {

        int sse = 0;

            // predict contient la prediction pour chaque ligne (avec formule appliquée sur n-1 colonnes)
            // la premiere valeur de predict (ligne 0, formule0) est à comparer avec dernière colonne ligne 0
            // la deuxieme valeur de predict (ligne 1, formule0) est à comparer avec dernière colonne ligne 1

        for (int k=0; k < nb_ligtab2D_ ;k++) {
            //std::cout << "predict = "<< predict_[j*nb_ligtab2D_+k] << std::endl;
            // on veut comparer predict à la valeur de la dernière colonne
            int valeur = tab2d_[k][nb_coltab2D_];
            //std::cout << "valeur = "<< valeur << std::endl;
            //std::cout << "valeur de la dernère colonne du tab2d : " << valeur << std::endl;
            sse += pow((predict_[j*nb_ligtab2D_+k] - valeur), 2);

        } // boucle k
        std::cout << "sse = " << sse << " pour l'enfant n°" << j << std::endl;

        // pour chaque enfant, on a le calcul de sse qui est la somme (des différences entre predit et valeur)
        if (sse <= best_sse_) { // la meilleure sse est la plus basse
            best_sse_ = sse;
            //std::cout << "best sse in if : " << best_sse_ << std::endl;
            
            bestformule_ = storage_[j];} // on actualise bestformule_ qui correspond à la sse la plus faible

    } // boucle j

    std::cout << "\n BEST SSE : " << best_sse_ << std::endl;
    bestformule_.affichage();
    
} ;


// prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la formule_ finale
void construction::theCycleOfLife(){

    std::cout << "\n DANS CYCLE_OF_LIFE " << std::endl;
    std::cout << "\nnb de lignes de tab   : " << nb_ligtab2D_ << std::endl;
    std::cout << "\nnb de colonnes de tab : " << nb_coltab2D_ << std::endl;

    // on pourrait initialiser ici la formule de départ, l'individu racine plutot que de le faire dans le constructeur
    
    for(int i=0; i < numGenerations_ ;i++) {
        std::cout << "\npour la génération n°"<< i << std::endl;
        generation();
        fonctiongen_ = bestformule_;
    }

    // check si la valeur de sse n'est pas inférieure à celle de la meilleure fonction de la generation précédente
    //fonctiongen_ = SSE(storage_); //stocke la nouvelle meilleure formule dans l'attribut de la classe   

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
