<img width="720" height="720" alt="Image" src="https://github.com/user-attachments/assets/3de40da6-7ca8-437d-afef-c0f1859c36e9" />

# Sujet :
minishell est un projet qui consiste à développer un mini-interpréteur de commandes Unix. <br>
L’objectif est de recréer les fonctionnalités de base d’un shell (bash/zsh) :
- Lecture de ligne
- Parsing
- Exécution de commandes
- Gestion des pipelines
- Gestion des redirections

# Fonctionnement :
Boucle de lecture :
- Affiche un prompt (ex : minishell$ ).
- Lit la ligne de commande saisie (readline()).
- Utilisation de la bibliothèque readline pour offrir l’édition de ligne et l’historique. (readline & history)

Parsing :
- Découpe la ligne en tokens (commandes, arguments, opérateurs |, <, >, >>, etc.).
- Construit une liste de commandes (commande simple ou un pipeline).

Heredoc :
- Ouvre un pipe ou un fichier temporaire.
- Lit ligne par ligne depuis l’entrée standard jusqu’à obtenir une ligne égale à DELIM.
- Écrit chaque ligne lue dans le pipe/fichier.
- Lors de l’exécution de la commande, redirige stdin depuis ce pipe/fichier.

Exécution :
- Builtins cd, echo, pwd, export, unset, env, exit gérés directement, sans fork. <br>

Pipelines & redirections :
- Chaque segment entre `|` s’exécute dans sa propre suite de forks, reliés par des pipe().
- < infile : redirige stdin depuis un fichier
- '>' outfile / >> outfile : redirige stdout vers un fichier (écrasement ou ajout)

Environnement :
- Gestion et modification de l’array envp pour export/unset.

Gestion des signaux :
- Interception de SIGINT (Ctrl-C) et SIGQUIT pour éviter de quitter le shell lui-même.
- SIGINT (Ctrl-C) : interrompt la commande courante sans quitter le shell
- SIGQUIT (Ctrl-) : ignoré pour ne pas générer de core dump

Autres commandes :
- Création de processus (fork())
- Appel à execve()
- Le shell attend la terminaison des processus avant de revenir au prompt.
