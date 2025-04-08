================================= Git =================================


# Travailler avec les branches
Lister les branches locales					git branch
Lister les branches distantes				git branch -r
Changer de branche							git checkout NOM_DE_LA_BRANCHE
Créer et passer sur une nouvelle branche	git checkout -b NOM_DE_LA_BRANCHE
Supprimer une branche locale				git branch -d NOM_DE_LA_BRANCHE
Supprimer une branche locale (forcé)		git branch -D NOM_DE_LA_BRANCHE
Supprimer une branche distante (GitHub)		git push origin --delete NOM_DE_LA_BRANCHE

# Envoyer et récupérer les modifications
Envoyer une branche sur GitHub				git push origin NOM_DE_LA_BRANCHE
Pousser une branche pour la première fois	git push -u origin NOM_DE_LA_BRANCHE
Récupérer les dernières modifications 
du repo distant :							git pull origin NOM_DE_LA_BRANCHE
Récupérer toutes les branches distantes		git fetch

# Fusionner des branches
1. Se placer sur la branche modifications	git checkout main 
2. Mettre a jour main (si necessaire)		git pull origin main
3. Fusionner la branche dans main			git merge NOM_DE_LA_BRANCHE
4. Pousser les changements vers le dépôt 
distant :									git push origin main


Si vous souhaitez supprimer la branche 
après la fusion :							git branch -d NOM_DE_LA_BRANCHE
Annuler une fusion si elle pose problème	git merge --abort
