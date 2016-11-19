touch result result2 total
for element in TESTS/*
do
	echo $element | ./42sh 1>result2;
	echo $elemnt | bash 1>result;
	diff result result2 > total
	if [ -s "total" ]
	then
		printf "\033[31m"
		cat $element
		printf "\033[0m\n"
		cat total

	else
		printf "\033[92m"
		cat $element
		printf "\033[0m\n"
	fi
done