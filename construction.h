#include <string>
#include "fonction.cpp"

class construction
{
    public:
    construction(const int gen, const int ind, const std::string adress);
    void dataManage();
    bool lectureCaseTab(size_t lig, size_t col);
    fonction* generation(bool popuInitiale);
    fonction SSE(const fonction* &tab); // reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la myFormule actuelle)
    void theCycleOfLife(); // prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la myFormule finale
    size_t get_nblig();
    size_t get_nbcol();


    protected:
    std::string adresse_; // Adresse du fichier .CSV fournie par l'utilisateur
    int numChildren_; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations_; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    bool** tab2d_; // Contient dans un tableau en 2D les données fournies par l'utilisateur
    size_t nb_ligtab2D_;
    size_t nb_coltab2D_;
    fonction formule_; // Contient la formule en cours de construction



};
