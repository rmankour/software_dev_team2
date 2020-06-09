#include <string>
#include "fonction.h"


class construction
{
    public:
    construction(const int gen, const int ind, const std::string adress);
    ~construction();
    void dataManage();
    bool lectureCaseTab(int lig, int col);
    void generation();
    void prediction(fonction *storage);
    //fonction SSE(const fonction* &tab_fonctions); // reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la myFormule actuelle)
    void SSE(fonction *storage);
    void theCycleOfLife(); // prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la myFormule finale
    int get_nblig();
    int get_nbcol();


    protected:
    std::string adresse_; // Adresse du fichier .CSV fournie par l'utilisateur
    int numChildren_; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations_; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    int compteurFormules;
    int *tab_positions; // stocke la position des mutations
    int *tab_type; // stocke le type de mutations
    int *tab_rang; // stocke le rang avec le lequel se fait un échange en cas d'interversion (-1 si pas d'interversion)
    bool** tab2d_; // Contient dans un tableau en 2D les données fournies par l'utilisateur
    int nb_ligtab2D_;
    int nb_coltab2D_;
    fonction* storage_;
    bool* predict_;
    fonction fonctiongen_; // correspond à un individu
    int* formulegen_; // Contient la formule d'un individu dans un tableau
    fonction bestformule_; // contient le meilleur enfant à chaque génération



};
