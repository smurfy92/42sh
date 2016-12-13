#!/bin/sh
make fclean;
rm -rf `ls | grep -v "clean.sh" | grep -v "srcs" | grep -v "includes" | grep -v "Makefile"  | grep -v "README.md"\
 | grep -v "tests.sh" | grep -v "TESTS" | grep -v "push.sh" | grep -v "auteur"`;