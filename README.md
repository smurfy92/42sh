<h1>42sh man</h1>

PDF 42sh correction:

tabulation: c’est obligatoire ca peut nous baiser !
--> bash n'en affiche jamais avec le bouton tab ..
--> utilisation d'une combinaison de touches INEDITE ?

hdoc: 
- Testez l'existence et le fonctionnement du heredoc "<<", avec ses options (wtf ???)  et cas particuliers. 
- errors: missing error fore HEREDOC when no EOF ex: echo <<

historic: (Ya pas de segflt)
- fais des truc bizarre si !num en plein milieu d’une cmd ---> normalement corrige avec ca 
- si historic dune cmd multiligne avc une ligne de taille plus grande que lq width du term, le prompt part en cacahuete

probleme sur env -i :---> ne fait rien que affichage ..
cd /tmp; sort << EOF | cat -e > sorted_poem --> fait bloquer dans le pupe .. a cause de cd /tmp ???

--> LEAKS au milieu de la correction .. BIZARRE avec un bail de DS_STORE(fichier de sauvegarde de sublim) dans la chaine qui leaks ----> aucune cmd comme ca ...

si on fait un cd en debut de cmd, et que derriere on lance une sred ex: mkdir test; cd test; echo lala > lolo
-----> fichier lolol nest pas cree dans le working directory test ---> getcwd appele dans le pere et nest pas encore effectif quand on cree le fichier ?

++ Trello: https://trello.com/b/WJXyMpVc/42sh
