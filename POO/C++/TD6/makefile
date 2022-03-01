monprog : main.cpp formes.a
	g++ -o monprog main.cpp formes.a
	clear
	./monprog

monprog2 : main2.cpp formes.a
	g++ -o monprog2 main2.cpp formes.a
	clear
	./monprog2

forme.o : forme.h cercle.cpp carre.cpp
	g++ -c forme.cpp

cercle.o : forme.h cercle.h cercle.cpp
	g++ -c cercle.cpp

carre.o : forme.h carre.h carre.cpp
	g++ -c carre.cpp

formes.a : forme.o cercle.o carre.o
	ar crs formes.a forme.o cercle.o carre.o

template : template.cpp formes.a
	g++ -o template template.cpp formes.a
	clear
	./template
