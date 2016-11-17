<h1>42sh man</h1>

norminette * | grep -v "C++ comment" | grep -v "bad indentation"<br />
valgrind --leak-check=full --show-leak-kinds=all ./42sh <br /><br />

-> Mettre les commande qui leaks dans les test unitaires

42sh> ls '
$>dsdffdsf \'
$>OK' && pwd ||ls

-- > Ne pas prend pas en compte le && en temps que separators


42sh en inception puis ctrl+c pluisiseurs fois + ctrl+d == segflt