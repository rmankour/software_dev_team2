import os
#from sympy import simplify

# toutes les fonctions utiles
# par exemple pour l'affichage de differents graphes

def compile():
	command="g++ main.cpp construction.cpp fonction.cpp -o main.out"
	print(command)
	return os.system(command)

def run_cpp_ea(nb_children, nb_generations, file_path):
    command="./main.out "+str(nb_children)+" "+str(nb_generations)+" "+str(file_path)
    print(command)
    return os.system(command)


# permet de generer le main.out
compile()

# MODIFIER CETTE LIGNE EN METTANT LES ARGUMENTS DE VOTRE CHOIX
run_cpp_ea(4,3,"gene_inter.csv")

''' A DECOMMENTER SI VOUS VOULEZ L'AFFICHAGE de SIMPLIFY SIMPY
mon_fichier = open("output_to_python.txt", "r")
contenu = mon_fichier.read()
mon_fichier.close()
print("résultat non simplify : ")
print(contenu)
print("résultat de simplify : ")
print(simplify("~x19 & x0 & x8 | x1 | x1 | x31 | x1 | x1 & x32 & x0 | x0 & x0 | x9 | x1 | x0 & x14 | x0 & x3 & x1 | x2 & x0 & x7 | x1 & x3"))
'''