import os

# toutes les fonctions utiles
# par exemple pour l'affichage de differents graphes

def compile():
	command="g++ main.cpp -o main.out"
	print(command)
	return os.system(command)

def run_cpp_ea(nb_children, nb_generations, file_path):
    command="./main.out "+str(nb_children)+" "+str(nb_generations)+" "+str(file_path)
    print(command)
    return os.system(command)


# permet de generer le main.out
compile()

# MODIFIER CETTE LIGNE EN METTANT LES ARGUMENTS DE VOTRE CHOIX
run_cpp_ea(4,5,"gene.csv")

