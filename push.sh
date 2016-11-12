make fclean;
sh clean.sh;
if [ -n "$1" ]
then
	git add -A;
	git commit -m "$1";
	git push;
else
	printf "usage: sh clean.sh [commit]\n"
fi
