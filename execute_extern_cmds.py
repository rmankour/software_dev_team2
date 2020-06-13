import os
from sympy import simplify

## Fichier à exectuter par l'utilisateur pour lancer l'analyse des données et l'affichage graphique
## La ligne 24 est à modifier pour changer les paramètres du traitement tel que précisé à la ligne 23

## Classe permettant de lancer la compilation des fichiers cpp nécessaires au traitement
def compile():
	command="g++ main.cpp construction.cpp fonction.cpp -o main.out"
	print(command)
	return os.system(command)

## Classe permettant d'executer le programme de traitement des données avec les paramètres fixés par l'utilisateur : le nombre de générations, le nombre d'enfants par génération et l'adresse du fichier .CSV contenant le tableau de données
def run_cpp_ea(nb_children, nb_generations, file_path):
    command="./main.out "+str(nb_children)+" "+str(nb_generations)+" "+str(file_path)
    print(command)
    return os.system(command)


## permet de generer le main.out
compile()

## MODIFIER CETTE LIGNE EN METTANT LES ARGUMENTS DE VOTRE CHOIX AVEC DANS L'ORDRE : le nombre de générations, le nombre d'enfants par génération et l'adresse du fichier .CSV contenant le tableau de données
run_cpp_ea(5,15,"gene.csv")

## Code permettant de lancer l'affichage graphique : A DECOMMENTER SI VOUS VOULEZ L'AFFICHAGE de SIMPLIFY SIMPY
mon_fichier = open("output_to_python.txt", "r")
contenu = mon_fichier.read()
mon_fichier.close()
print("résultat non simplify : ")
print(contenu)
print("résultat de simplify : ")
print(simplify(contenu))
