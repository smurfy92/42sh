norminette * | grep -v "C++ comment" | grep -v "bad indentation"
valgrind --leak-check=full --show-leak-kinds=all ./42sh
