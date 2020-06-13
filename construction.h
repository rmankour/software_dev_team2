#include <string>
#include "fonction.h"

/*!
* Une classe prenant les paramètres fournis par l'utilisateur afin de construire la formule expliquant le mieux les données et les scores correspondants
*/

class construction
{
    public:
    construction(const int gen, const int ind, const std::string adress);
    ~construction();
    //! Méthode pour importer les données fournies par l'utilisateur sous la forme d'une tableau en 2D
    void dataManage();
    //! Méthode pour return une valeur (bool) du tableau en lui fournissant le numéro de la ligne et de la colonne (int)
    bool lectureCaseTab(int lig, int col);
    //! Méthode pour construire les enfants d'une génération, stockés dans le tableau storage, à partir de l'objet fonction correspondant au parent en input
    void generation(fonction& argfonctiongen_);
    //! Méthode prenant en input : tableau storage avec tous les enfants mutés
    //! modifie l'argument predict qui est un tableau avec pour chaque enfant, la prédiction pour chaque ligne (0 ou 1)
    void prediction(fonction *storage);
    //! fonction SSE(const fonction* &tab_fonctions);
    //! reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la myFormule actuelle)
    void SSE(fonction *storage);
    //! prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la myFormule finale
    void theCycleOfLife();
    //! Méthode pour donner le nombre de lignes du tableau
    int get_nblig();
    //! Méthode pour donner le nombre de colonnes du tableau
    int get_nbcol();

    void ecritureOutput(std::string trucaecrire);

    protected:
    //! Adresse du fichier .CSV fournie par l'utilisateur
    std::string adresse_;
    //! Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numChildren_;
    //! Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations_;
    int compteurFormules;
    //! stocke la position des mutations
    int *tab_positions;
    //! stocke le type de mutations
    int *tab_type;
    //! stocke le rang avec le lequel se fait un échange en cas d'interversion (-1 si pas d'interversion)
    int *tab_rang;
    //! Contient dans un tableau en 2D les données fournies par l'utilisateur
    bool** tab2d_;
    int nb_ligtab2D_;
    int nb_coltab2D_;
    fonction* storage_;
    bool* predict_;
    //! correspond à un individu
    fonction fonctiongen_;
    //! contient le meilleur enfant à chaque génération
    fonction bestformule_;
    int best_sse_;
    //! contient le meilleur score
    float best_fitness_;



};
