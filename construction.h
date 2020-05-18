class construction
{
    public:
    construction(const int gen, const int ind, const char c_str[]);
    void dataManage() const;
    formule generation() const;
    formule SCE(const formule &tab); // reçoit un tableau de formule et retourne la meilleure d'entre elles (en prenant aussi en compte la myFormule actuelle)
    void theCycleOfLife; // prend tous les paramètres donnés par l'utilisateur et réalise la boucle de calculs nécessaire pour aboutir à la myFormule finale

    protected:
    string adresse; // Adresse du fichier .CSV fournie par l'utilisateur
    int numChildren; // Nombre de d'individus par génération, indiqué par l'utilisateur ou valeur par défaut
    int numGenerations; // Nombre de générations à réaliser, indiqué par l'utilisateur ou valeur par défaut
    bool tableau; // Contient dans un tableau en 2D les données fournies par l'utilisateur
    formule myFormule; // Contient la formule en cours de construction
};
