#include "construction.h"
#include <stdio.h>
#include <string>
#include <iostream>



// ***************** REMARQUE : les lignes qu'il y a avait dans le main.cpp ne permettaient pas de compiler donc elles sont en commentaires

int main(int argc, char *argv[]) {

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

    // on met les arguments dans des variables
    int nb_children = std::atoi(argv[1]);  // converti notre char en int 
    int nb_generation = std::atoi(argv[2]) ; // converti notre char en int
    std::string adresse_tab = argv[3]; // constructeur de string converti directement un char en int sans soucis.


    // debut des objets
    
    construction obj(nb_children,nb_generation,adresse_tab);

    obj.generation();
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
