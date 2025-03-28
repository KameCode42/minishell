# Schéma détaillé de la construction de l'AST pour cmd1 | cmd2 | cmd3:

Étape 1: Premier appel à build_ast_recursive

Tokens: cmd1, |, cmd2, |, cmd3
Position du curseur: tokens[0] (cmd1)

ROOT
 |
NULL

Étape 2: Traitement de cmd1

ROOT
 |
 +-- cmd1

Étape 3: Rencontre du premier pipe (tokens[1])

Création d'un nœud pipe
Structure mise à jour:

ROOT
 |
PIPE
 |
 +-- LEFT: cmd1
 |
 +-- RIGHT: NULL (nœud vide)

Étape 4: Appel récursif pour traiter la partie après le premier pipe

build_ast_recursive(shell, RIGHT, &index)
Position du curseur: tokens[2] (cmd2)
Premier appel sort de sa boucle avec break

Étape 5: Dans le premier appel récursif, traitement de cmd2

ROOT
 |
PIPE
 |
 +-- LEFT: cmd1
 |
 +-- RIGHT: cmd2

Étape 6: Rencontre du deuxième pipe (tokens[3])

Création d'un autre nœud pipe dans l'appel récursif
Structure mise à jour:

ROOT
 |
PIPE
 |
 +-- LEFT: cmd1
 |
 +-- RIGHT: PIPE
		   |
		   +-- LEFT: cmd2
		   |
		   +-- RIGHT: NULL (nœud vide)

Étape 7: Deuxième appel récursif pour traiter après le deuxième pipe

build_ast_recursive(shell, RIGHT du second PIPE, &index)
Position du curseur: tokens[4] (cmd3)
Premier appel récursif sort avec break

Étape 8: Dans le deuxième appel récursif, traitement de cmd3

ROOT
 |
PIPE
 |
 +-- LEFT: cmd1
 |
 +-- RIGHT: PIPE
		   |
		   +-- LEFT: cmd2
		   |
		   +-- RIGHT: cmd3

Cette structure permet d'exécuter les commandes dans le bon ordre: la sortie de cmd1 est l'entrée de cmd2, et la sortie de cmd2 est l'entrée de cmd3.

# BREAK

Le break dans la fonction initiale ne fait qu'arrêter la première boucle, mais la récursion continue à travers les appels successifs à build_ast_recursive.
Chaque nouvel appel récursif:

Traite une portion différente de la chaîne de commandes
A son propre contexte (sa propre boucle while)
Utilise le même curseur de position (*i) qui est passé par référence et continue d'avancer
