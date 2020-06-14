import os
from sympy import simplify
import matplotlib.pyplot as plt
import numpy as np

## Fichier à executer par l'utilisateur pour lancer l'analyse des données et l'affichage graphique
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
run_cpp_ea(10,500,"gene.csv")

## Code permettant de lancer l'affichage graphique : A DECOMMENTER SI VOUS VOULEZ L'AFFICHAGE de SIMPLIFY SIMPY
mon_fichier = open("output_to_python.txt", "r")
contenu = mon_fichier.read()
mon_fichier.close()
print("\nRésultat non simplify : ")
print(contenu)
print("Résultat de simplify : ")
print(simplify(contenu))
x = np.genfromtxt('fitness_to_python.txt', delimiter=' ')[:-1]
plt.plot(x, label='''Taux d'erreurs''')
plt.xlabel('Nombre de génération')
plt.ylabel('''Taux d'erreurs''')
plt.title('''Evolution du taux d'erreurs en fonction du nombre de génération''')
plt.legend()
plt.show()
