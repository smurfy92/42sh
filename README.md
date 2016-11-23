<h1>42sh man</h1>

PDF 42sh correction:

tabulation: c’est obligatoire ca peut nous baiser !
- bash n'en affiche jamais avec le bouton tab ..
- utilisation d'une combinaison de touches INEDITE ?

hdoc: 
- Testez l'existence et le fonctionnement du heredoc "<<", avec ses options (wtf ???)  et cas particuliers. 

historic:
- fais des truc bizarre si !num en plein milieu d’une cmd ---> normalement corrige avec ca 
- si historic dune cmd multiligne avc une ligne de taille plus grande que lq width du term, le prompt part en cacahuete

cd /tmp; sort << EOF | cat -e > sorted_poem 
- fait bloquer dans le pipe .. a cause de cd /tmp ??? 
- problem: hdoc's fd were removed on every ft_exit() on each son !
- fixed bien vu !

--> LEAKS au milieu de la correction .. BIZARRE avec un bail de DS_STORE(fichier de sauvegarde de sublim) dans la chaine qui leaks ----> aucune cmd comme ca ...

++ Trello: https://trello.com/b/WJXyMpVc/42sh
