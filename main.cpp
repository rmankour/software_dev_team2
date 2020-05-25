#include <stdio.h>

// ***************** REMARQUE : les lignes qu'il y a avait dans le main.cpp ne permettaient pas de compiler donc elles sont en commentaires
// #include "construction.h"

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
    char* nb_children = argv[1];
    char* nb_generation = argv[2];
    char* adresse_tab = argv[3];


    // debut des objets
    //construction obj(0,0,"gene.csv");
	  //obj.dataManage();
	

   return 0;
}