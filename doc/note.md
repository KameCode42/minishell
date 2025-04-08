fonction externe :

- readline :
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
readline lira une ligne depuis le terminal et la renverra, en utilisant prompt comme invite. Si prompt est NULL ou une chaîne vide, aucune invite n'est affichée. La ligne renvoyée est allouée avec malloc(3) ; l'appelant doit la libérer une fois terminé. La ligne renvoyée ne contient pas le retour à la ligne final, seul le texte de la ligne est conservé

-----------------------------------------------------------------------------------------------------------------------------------------------------

- rl_clear_history : (dans readline.h)
void rl_clear_history(void);
Cette fonction supprime toutes les entrées de l'historique de Readline
Elle est utile lorsqu'on souhaite réinitialiser l'historique sans quitter le programme.
Après l'appel à rl_clear_history, l'historique est vide et ne contient plus aucune commande précédente

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    add_history("commande 1");
    add_history("commande 2");

    printf("Historique avant effacement :\n");
    HIST_ENTRY **history_list = history_list();
    for (int i = 0; history_list && history_list[i]; i++) {
        printf("%s\n", history_list[i]->line);
    }

    // Effacer l'historique
    rl_clear_history();

    printf("Historique après effacement :\n");
    history_list = history_list();
    if (!history_list) {
        printf("L'historique est vide.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- rl_on_new_line : (dans readline.h)
void rl_on_new_line(void);
Cette fonction informe Readline qu’une nouvelle ligne commence.
Elle est utile lorsqu’on gère manuellement l’affichage de l’entrée utilisateur et que l’on souhaite repositionner le curseur sur une nouvelle ligne
Elle est souvent utilisée en combinaison avec rl_redisplay() pour mettre à jour l’affichage correctement après une modification de l’entrée en cours

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while ((input = readline("Prompt> ")) != NULL) {
        printf("Vous avez saisi : %s\n", input);
        rl_on_new_line();   // Indique à Readline qu'une nouvelle ligne commence
        rl_redisplay();     // Met à jour l'affichage
        add_history(input);
        free(input);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- rl_replace_line : (dans readline.h)
void rl_replace_line(const char *text, int clear_undo);
La fonction rl_replace_line remplace le contenu actuel de la ligne d'entrée de Readline par une nouvelle chaîne de caractères
text : La nouvelle ligne à insérer.
clear_undo : Si non nul (1), l'historique des actions annulables est effacé ; si 0, l'utilisateur peut toujours annuler (Ctrl+_ en mode Emacs)

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while ((input = readline("Prompt> ")) != NULL) {
        if (input[0] == 'r') {  // Exemple : remplacer la ligne si elle commence par 'r'
            rl_replace_line("Texte remplacé", 1);
            rl_redisplay();  // Rafraîchir l'affichage
        }
        add_history(input);
        free(input);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------


- rl_redisplay : (dans readline.h)
void rl_redisplay(void);
rl_redisplay force la mise à jour de l'affichage de la ligne d'entrée utilisateur dans le terminal
Elle est utilisée après une modification de la ligne en cours, par exemple après un appel à rl_replace_line ou rl_insert_text

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    while ((input = readline("Prompt> ")) != NULL) {
        if (input[0] == 'r') {  // Exemple : si l'entrée commence par 'r', on la remplace
            rl_replace_line("Texte remplacé", 1);
            rl_redisplay();  // Rafraîchir l'affichage
        }
        add_history(input);
        free(input);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- add_history : dans (history.h)
void add_history(const char *line);
La fonction add_history permet d'ajouter une ligne à l'historique des commandes de Readline. Cela permet à l'utilisateur de naviguer dans ses commandes précédentes en utilisant les flèches haut et bas

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input = readline("Commande> ");
    
    if (input && *input) {  
        add_history(input);  // Ajouter la ligne à l'historique
    }

    printf("Vous avez entré : %s\n", input);

    free(input);  // Libérer la mémoire allouée par readline
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- access : (dans unistd.h)
La fonction access permet de vérifier l'existence et les permissions d'un fichier ou d'un répertoire. Elle est utilisée pour tester si le programme a la possibilité d'accéder à un fichier de manière spécifique (lecture, écriture, exécution)

#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "monfichier.txt";

    if (access(filename, F_OK) == 0) {  // Vérifie si le fichier existe
        printf("Le fichier %s existe.\n", filename);
    } else {
        printf("Le fichier %s n'existe pas.\n", filename);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- fork : (dans unistd.h)
pid_t fork(void);
La fonction fork crée un nouveau processus en dupliquant le processus appelant. Le processus créé est un processus fils qui est une copie exacte du processus père, sauf pour la valeur retournée par fork.
Processus père : Reçoit l'ID du processus fils (PID) comme valeur de retour de fork.
Processus fils : Reçoit 0 comme valeur de retour de fork

#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Créer un nouveau processus

    if (pid == -1) {
        // Erreur de fork
        perror("Erreur de fork");
        return 1;
    }

    if (pid == 0) {
        // Code du processus fils
        printf("Je suis le processus fils.\n");
    } else {
        // Code du processus père
        printf("Je suis le processus père. Le PID du fils est %d.\n", pid);
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- signal : (dans signal.h)
void (*signal(int signum, void (*handler)(int)))(int);
La fonction signal permet d'installer un gestionnaire pour un signal particulier. Un signal est une notification envoyée à un processus pour l'informer d'un événement, comme une interruption ou une demande de terminaison

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
    printf("Signal %d reçu !\n", sig);
    exit(0);
}

int main() {
    signal(SIGINT, handler);  // Installer un gestionnaire pour SIGINT (Ctrl+C)
    while (1) {
        // Boucle infinie jusqu'à ce que l'utilisateur appuie sur Ctrl+C
    }
    return 0;
}
-----------------------------------------------------------------------------------------------------------------------------------------------------

- sigaction : (dans signal.h)
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
La fonction sigaction permet d'installer un gestionnaire de signal avec plus de contrôle que signal. Elle permet également de définir des options supplémentaires pour la gestion des signaux

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void handler(int sig) {
    printf("Signal %d reçu, programme terminé.\n", sig);
    exit(0);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handler;       // Définir le gestionnaire de signal
    sa.sa_flags = 0;               // Aucun drapeau spécifique
    sigemptyset(&sa.sa_mask);      // Aucune action sur les signaux masqués

    sigaction(SIGINT, &sa, NULL);  // Installer le gestionnaire pour SIGINT (Ctrl+C)

    while (1) {
        // Boucle infinie jusqu'à ce que l'utilisateur appuie sur Ctrl+C
    }
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- sigemptyset : (dans signal.h)
int sigemptyset(sigset_t *set);
La fonction sigemptyset initialise un ensemble de signaux à vide. Cela signifie que l'ensemble ne contient aucun signal, et il peut ensuite être utilisé pour manipuler des masques de signaux (comme ceux utilisés avec sigaction).

#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t set;
    sigemptyset(&set);  // Initialise l'ensemble à vide
    printf("Ensemble de signaux vidé.\n");

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- sigaddset : (dans signal.h)
int sigaddset(sigset_t *set, int signum);
La fonction sigaddset permet d'ajouter un signal à un ensemble de signaux. Cela est utile pour manipuler des ensembles de signaux, en particulier lorsque vous travaillez avec des masques de signaux

#include <stdio.h>
#include <signal.h>

int main() {
    sigset_t set;
    sigemptyset(&set);      // Initialise l'ensemble à vide
    sigaddset(&set, SIGINT);  // Ajoute SIGINT à l'ensemble

    printf("SIGINT ajouté à l'ensemble des signaux.\n");

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- kill : (dans signal.h)
int kill(pid_t pid, int sig);
La fonction kill envoie un signal à un ou plusieurs processus. Bien que son nom puisse suggérer une terminaison, elle peut être utilisée pour envoyer n'importe quel signal, pas uniquement pour tuer des processus.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Créer un processus fils

    if (pid == 0) {
        // Code du processus fils
        printf("Je suis le processus fils avec PID %d.\n", getpid());
        while (1) {
            // Boucle infinie pour rester en vie
        }
    } else {
        // Code du processus père
        sleep(2);  // Attendre 2 secondes pour laisser le fils démarrer
        printf("Envoi du signal SIGKILL au processus fils avec PID %d.\n", pid);
        kill(pid, SIGKILL);  // Envoyer SIGKILL au processus fils
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- getcwd : (dans unistd.h)
char *getcwd(char *buf, size_t size);
La fonction getcwd récupère le répertoire de travail actuel (le répertoire dans lequel le programme s'exécute). Elle renvoie le chemin absolu du répertoire courant.

#include <stdio.h>
#include <unistd.h>

int main() {
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Le répertoire courant est : %s\n", cwd);
    } else {
        perror("Erreur lors de la récupération du répertoire courant");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- chdir : (dans unistd.h)
int chdir(const char *path);
La fonction chdir change le répertoire de travail courant du programme. Elle permet de naviguer dans le système de fichiers à partir du programme en modifiant le répertoire courant.

#include <stdio.h>
#include <unistd.h>

int main() {
    if (chdir("/tmp") == 0) {
        printf("Le répertoire de travail a été changé avec succès.\n");
    } else {
        perror("Erreur lors du changement de répertoire");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- stat : (dans sys/stat.h)
int stat(const char *path, struct stat *buf);
La fonction stat permet de récupérer des informations détaillées sur un fichier ou un répertoire, telles que sa taille, ses permissions, son propriétaire, et son horodatage.

#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat file_stat;
    const char *filename = "monfichier.txt";

    if (stat(filename, &file_stat) == 0) {
        printf("Taille du fichier : %ld octets\n", file_stat.st_size);
        printf("Permissions du fichier : %o\n", file_stat.st_mode & 0777);
    } else {
        perror("Erreur lors de l'obtention des informations sur le fichier");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- lstat : (dans sys/stat.h)
int lstat(const char *path, struct stat *buf);
a fonction lstat est similaire à stat, mais elle récupère les informations sur le fichier lui-même, même si le chemin est un lien symbolique. Si le chemin donné est un lien symbolique, lstat renvoie des informations sur le lien, alors que stat donne des informations sur le fichier pointé par le lien

#include <stdio.h>
#include <sys/stat.h>

int main() {
    struct stat file_stat;
    const char *filename = "monlien_symlink";  // Lien symbolique

    if (lstat(filename, &file_stat) == 0) {
        printf("Taille du lien : %ld octets\n", file_stat.st_size);
        if (S_ISLNK(file_stat.st_mode)) {
            printf("C'est un lien symbolique.\n");
        }
    } else {
        perror("Erreur lors de l'obtention des informations sur le fichier");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- fstat : (dans #include <sys/stat.h> et <fcntl.h>)
int fstat(int fd, struct stat *buf);
La fonction fstat est utilisée pour obtenir des informations sur un fichier à partir de son descripteur de fichier, plutôt que de son chemin. Elle est similaire à stat, mais elle fonctionne avec un descripteur de fichier ouvert.

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
    struct stat file_stat;
    int fd = open("monfichier.txt", O_RDONLY);  // Ouvrir le fichier en lecture

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    if (fstat(fd, &file_stat) == 0) {
        printf("Taille du fichier : %ld octets\n", file_stat.st_size);
    } else {
        perror("Erreur lors de l'obtention des informations sur le fichier");
    }

    close(fd);  // Fermer le descripteur de fichier
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- unlink : (dans unistd.h)
int unlink(const char *pathname);
la fonction unlink supprime un fichier du système de fichiers. Elle n'efface pas immédiatement les données, mais décrémente le compteur de liens (références) du fichier. Si le compteur de liens atteint zéro, les données sont effectivement supprimées

#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "monfichier.txt";

    if (unlink(filename) == 0) {
        printf("Le fichier '%s' a été supprimé avec succès.\n", filename);
    } else {
        perror("Erreur lors de la suppression du fichier");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- execve : (dans unistd.h)
int execve(const char *pathname, char *const argv[], char *const envp[]);
La fonction execve remplace le processus courant par un nouveau programme. Elle charge et exécute un programme spécifié, en utilisant l'image du programme et ses arguments.

#include <stdio.h>
#include <unistd.h>

int main() {
    char *argv[] = {"ls", "-l", NULL};  // Arguments pour ls -l
    char *envp[] = {NULL};  // Aucun variable d'environnement spécifique

    if (execve("/bin/ls", argv, envp) == -1) {
        perror("Erreur lors de l'exécution de execve");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- dup2 : (dans unistd.h)
int dup2(int oldfd, int newfd);
La fonction dup2 est similaire à dup, mais elle permet de spécifier explicitement le descripteur de fichier de destination. Si le descripteur de fichier de destination est déjà ouvert, il sera fermé avant que dup2 ne le duplique

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int fd = open("monfichier.txt", O_RDONLY);  // Ouvrir le fichier en lecture

    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    int newfd = 5;  // Choisir un nouveau descripteur de fichier
    if (dup2(fd, newfd) == -1) {  // Copier fd dans newfd
        perror("Erreur lors de la duplication du descripteur");
        close(fd);
        return 1;
    }

    printf("Le fichier est maintenant accessible via le descripteur %d\n", newfd);

    close(fd);    // Fermer le descripteur original
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- pipe : (dans unistd.h)
int pipe(int pipefd[2]);
La fonction pipe crée un canal de communication entre deux processus (souvent utilisé pour la communication entre un processus parent et un processus enfant). Elle permet à un processus d'écrire des données dans un descripteur de fichier et à un autre processus de lire ces données via un autre descripteur
pipe_fd[0] = lecture
pipe_fd[1] = ecriture

-----------------------------------------------------------------------------------------------------------------------------------------------------

- opendir : (dans dirent.h)
DIR *opendir(const char *name);
La fonction opendir ouvre un répertoire pour lecture. Elle retourne un pointeur vers un flux de répertoire qui peut être utilisé pour lire les fichiers et sous-répertoires à l'intérieur du répertoire spécifié.

#include <stdio.h>
#include <dirent.h>

int main() {
    const char *dir_name = ".";  // Répertoire courant
    DIR *dir = opendir(dir_name);

    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);  // Afficher le nom du fichier
    }

    closedir(dir);  // Fermer le répertoire
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- readdir : (dans dirent.h)
struct dirent *readdir(DIR *dirp);
La fonction readdir lit le contenu d'un répertoire ouvert. À chaque appel, elle retourne un pointeur vers une structure dirent contenant les informations sur le fichier ou sous-répertoire suivant du répertoire.

#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Nom du fichier : %s\n", entry->d_name);  // Afficher le nom du fichier ou répertoire
    }

    closedir(dir);  // Fermer le répertoire
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- closedir : (dans dirent.h)
int closedir(DIR *dirp);
La fonction closedir ferme un répertoire ouvert avec opendir. Elle libère les ressources associées au flux de répertoire et rend ce dernier inutilisable pour toute opération ultérieure

#include <stdio.h>
#include <dirent.h>

int main() {
    DIR *dir = opendir(".");

    if (dir == NULL) {
        perror("Erreur lors de l'ouverture du répertoire");
        return 1;
    }

    // Lire les fichiers et sous-répertoires ici avec readdir...
    // Exemple : readdir(dir)

    if (closedir(dir) == -1) {
        perror("Erreur lors de la fermeture du répertoire");
        return 1;
    }

    printf("Le répertoire a été fermé avec succès.\n");
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- sterror : (dans string.h)
char *strerror(int errnum);
La fonction strerror renvoie une chaîne de caractères décrivant l'erreur correspondant à un code d'erreur spécifique. Ce code d'erreur est généralement renvoyé par des fonctions systèmes comme open, read, write, etc

-----------------------------------------------------------------------------------------------------------------------------------------------------

- perror : (dans errno.h)
La fonction perror affiche un message d'erreur sur la sortie d'erreur standard (stderr). Elle utilise la valeur de errno, qui est une variable globale contenant le dernier code d'erreur rencontré lors d'un appel système échoué

-----------------------------------------------------------------------------------------------------------------------------------------------------

- isatty : (dans unistd.h)
int isatty(int fd);
La fonction isatty permet de vérifier si un descripteur de fichier correspond à un terminal (TTY).

#include <stdio.h>
#include <unistd.h>

int main() {
    if (isatty(STDIN_FILENO)) {
        printf("L'entrée standard est un terminal.\n");
    } else {
        printf("L'entrée standard n'est pas un terminal.\n");
    }
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- ttyname : (dans unistd.h)
char *ttyname(int fd);
La fonction ttyname retourne le nom du terminal associé à un descripteur de fichier.

#include <stdio.h>
#include <unistd.h>

int main() {
    char *nom_terminal = ttyname(STDIN_FILENO);
    
    if (nom_terminal) {
        printf("Nom du terminal : %s\n", nom_terminal);
    } else {
        printf("Aucun terminal associé à l'entrée standard.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- ttyslot : (dans unistd.h)
int ttyslot(void);
La fonction ttyslot renvoie l'index du terminal du processus actuel dans le fichier /etc/utmp.

#include <stdio.h>
#include <unistd.h>

int main() {
    int slot = ttyslot();
    
    if (slot > 0) {
        printf("Numéro du terminal dans /etc/utmp : %d\n", slot);
    } else {
        printf("Impossible de trouver le terminal dans /etc/utmp.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- ioctl : (dans #include <sys/ioctl.h>)
int ioctl(int fd, unsigned long request, ...);
La fonction ioctl permet de manipuler des périphériques via des commandes spécifiques.

#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main() {
    struct winsize w;
    
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("Erreur ioctl");
        return 1;
    }

    printf("Taille du terminal : %d lignes x %d colonnes\n", w.ws_row, w.ws_col);
    
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- getenv : (dans stdlib.h)
char *getenv(const char *name);
La fonction getenv récupère la valeur d'une variable d'environnement.


#include <stdio.h>
#include <stdlib.h>

int main() {
    char *path = getenv("PATH");
    
    if (path) {
        printf("PATH : %s\n", path);
    } else {
        printf("La variable PATH n'existe pas.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tcsetattr & tcgetattr : (dans termios.h)
int tcgetattr(int fd, struct termios *termios_p);
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
tcgetattr : Obtient les attributs du terminal.
tcsetattr : Modifie les attributs du terminal.

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios term;
    
    tcgetattr(STDIN_FILENO, &term);
    
    term.c_lflag &= ~ICANON;  // Désactiver le mode canonique
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    
    printf("Mode non-canonique activé, tapez un caractère : ");
    char c = getchar();
    printf("\nVous avez tapé : %c\n", c);
    
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tgetent : (dans #include <curses.h> et #include <term.h>)
int tgetent(char *bp, const char *name);
La fonction tgetent initialise l'utilisation des fonctionnalités du terminal en chargeant ses capacités à partir de la base de données termcap.

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    char *term = getenv("TERM");
    
    if (tgetent(NULL, term) != 1) {
        printf("Erreur : Impossible de charger les capacités du terminal.\n");
        return 1;
    }

    printf("Capacités du terminal chargé pour : %s\n", term);
    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tgetflag : (dans #include <curses.h> et #include <term.h>)
int tgetflag(const char *id);
La fonction tgetflag permet de tester si une capacité booléenne est présente pour un terminal

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    tgetent(NULL, getenv("TERM"));
    
    if (tgetflag("hc")) {
        printf("Le terminal ne peut pas exécuter des capacités de contrôle de curseur.\n");
    } else {
        printf("Le terminal prend en charge le contrôle du curseur.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tgetbnum :(dans #include <curses.h> et #include <term.h>)
int tgetnum(const char *id);
La fonction tgetnum récupère une valeur numérique d'une capacité du terminal.

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    tgetent(NULL, getenv("TERM"));

    int cols = tgetnum("co");  // Nombre de colonnes du terminal
    if (cols != -1) {
        printf("Le terminal a %d colonnes.\n", cols);
    } else {
        printf("Impossible d'obtenir le nombre de colonnes.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tgetstr : (dans #include <curses.h> et #include <term.h>)
char *tgetstr(const char *id, char **area);
La fonction tgetstr récupère une séquence de contrôle du terminal sous forme de chaîne.

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    tgetent(NULL, getenv("TERM"));

    char *buffer;
    char *clear = tgetstr("cl", &buffer);  // Séquence pour effacer l'écran
    
    if (clear) {
        printf("Séquence pour effacer l'écran : %s\n", clear);
    } else {
        printf("Impossible d'obtenir la séquence d'effacement.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tgoto : (dans #include <curses.h> et #include <term.h>)
char *tgoto(const char *cap, int col, int row);
La fonction tgoto génère une séquence pour déplacer le curseur à une position spécifique.

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    tgetent(NULL, getenv("TERM"));

    char *buffer;
    char *move_cursor = tgetstr("cm", &buffer);  // Séquence de déplacement du curseur

    if (move_cursor) {
        printf("Séquence pour déplacer le curseur à (10,5) : %s\n", tgoto(move_cursor, 10, 5));
    } else {
        printf("Impossible d'obtenir la séquence de déplacement.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------

- tputs : (dans #include <curses.h> et #include <term.h>)
int tputs(const char *str, int affcnt, int (*putc)(int));
La fonction tputs envoie une séquence de contrôle au terminal.

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

int main() {
    tgetent(NULL, getenv("TERM"));

    char *buffer;
    char *clear = tgetstr("cl", &buffer);  // Séquence pour effacer l'écran

    if (clear) {
        tputs(clear, 1, putchar);  // Envoie la séquence d'effacement au terminal
    } else {
        printf("Impossible d'effacer l'écran.\n");
    }

    return 0;
}

-----------------------------------------------------------------------------------------------------------------------------------------------------
