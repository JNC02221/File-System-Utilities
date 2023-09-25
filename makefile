all: myls mysearch mystat mytail

myls: myls-Jackson.c
	gcc -o myls myls-Jackson.c

mysearch: mysearch-Jackson.c
	gcc -o mysearch mysearch-Jackson.c

mystat: mystat-Jackson.c
	gcc -o mystat mystat-Jackson.c

mytail: mytail-Jackson.c
	gcc -o mytail mytail-Jackson.c
