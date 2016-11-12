make fclean;
rm -rf `ls | grep -v "clean.sh" | grep -v "srcs" | grep -v "includes" | grep -v "Makefile"  | grep -v "README.md"\
 | grep -v "test.sh" | grep -v "test" | grep -v "TESTS"`;
rm **/**.*o;