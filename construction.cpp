#include "construction.h"
#include "string.h"

construction::construction(const int gen, const int ind, const char c_str[]){
    string adresse = c_str; // Adresse du fichier .CSV fournie par l'utilisateur
    int numChildren = ind; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations = gen; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    dataManage(); // donne une valeur à tableau qui contient dans un tableau en 2D les données fournies par l'utilisateur
    formule myFormule; // Devrait générer une formule au pif si la classe marche bien
    theCycleOfLife();
    //ligne de code qui génère un fichier contenant les informations sur myFormule finale
};

void construction::dataManage(){

};
formule construction::generation(){

};

// reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la myFormule actuelle)
formule construction::SCE(const formule &tab){

} ;

// prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la myFormule finale
void construction::theCycleOfLife{

};
