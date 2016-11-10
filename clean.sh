make fclean;
rm -rf `ls | grep -v "clean.sh" | grep -v "Makefile" | grep -v "includes" | grep -v "README.md" | grep -v "srcs"`