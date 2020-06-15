#include "construction.h"
#include <stdio.h>
#include <string>
#include <iostream>

//! Main program that executes the necessary commands to construct the formula

/*! \mainpage FormuGen
 *
 * \section intro_sec Introduction
 *
 * This program's purpose is to determine the best formula that establishes the relationship between the expression of a set of genes and the expression of a determined gene.
 *
 * \section install_sec How to use it ?
 *
 * To use this program, you need to run the file execute_extern_cmds.py after modifying it to indicate the parameters you wish to use.
 * The parameters are to be given in line 24 :
 *
 * run_cpp_ea(5,15,"gene.csv")
 *
 * They correspond in order to : the number of children per generation, the number of generations (cycles) the user wishes to apply and the adresse of the .CSV file containing the provided data.
 *
 * The program will then establish a formula and for each generation make a number of variations corresponding to the number of children per generation, choose the one most fitting to the provided data, then redo a new generation from it.
 *
 * Once the desired number of generations is done, the program will then show the resulting formula on the graphical output and a graph showing the evolution of the percentage of errors compared to the data with each new generation until the last.
 *
 */

int main(int argc, char *argv[]) {
    /*
   printf("Hello, this is the beginning !");

   // pour s'assurer que tout a bien ete pris correctement en argument
   // argv[0] holds the name of the program.
   // argv[1] points to the first command line argument etc.
   int counter;
   printf("\nProgram Name Is: %s",argv[0]);
   if(argc==1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if(argc>=2)
    {
        printf("\nNumber Of Arguments Passed: %d",argc);
        printf("\n----Following Are The Command Line Arguments Passed----");
        for(counter=0;counter<argc;counter++)
            printf("\nargv[%d]: %s",counter,argv[counter]);
    }
    */
    // on met les arguments dans des variables
    // convertit notre char en int
    int nb_children = std::atoi(argv[1]);
    // convertit notre char en int
    int nb_generation = std::atoi(argv[2]) ;
    // constructeur de string converti directement un char en int
    std::string adresse_tab = argv[3];


    // construit l'objet construction possédant les méthodes nécessaires au traitement des données
    construction obj(nb_generation, nb_children, adresse_tab);
    /*fonction f20(3);
    fonction f3(3);
    std::cout << "fonction f20(20);\n";
    f20.affichage();
    std::cout << "fonction f3(3);\n";
    f3.affichage();
    std::cout << "ON FE f20 = F3;\n";
    f20 = f3;
    std::cout << "fonction f20(20);\n";
    f20.affichage();
    std::cout << "fonction f3(3);\n";
    f3.affichage();
    */
    //obj.generation(); // à enlever une fois que tout marche, on utilise cycleoflife
    // Application de la méthode permettant de produire les générations successives en gardant à chaque fois l'enfant avec le meilleur score
    // Renvoie en sortie la meilleure formule voulue par l'utilisateur et les scores correspondants, exploitée ensuite sur python
    obj.theCycleOfLife();
	//obj.dataManage();


    //construction obj(0,0,"gene.csv");
	 //obj.dataManage(); //A enlever après

	/*
    //écrire les ligne de code pour extraire les tableaux (2 pour formule_ et 3 pour historique) en attribut de obj dans un fichier texte :
    ofstream myfile ("output.txt");
    if (myfile.is_open())
    {
    i = 0;
    for i in obj.formule_.table1 {écrire dans le doc}
    myfile << "This is a line.\n";
    myfile.close();
    }
    else cout << "Unable to open file";

    */

    return 0;
}
