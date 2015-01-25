funix.out: main.o funix.o directory.o permissions.o
	g++ -ansi -o funix.out -Wall main.o funix.o directory.o permissions.o

main.o: main.cpp funix.h
	g++ -ansi -c -g -Wall main.cpp

funix.o: funix.cpp funix.h
	g++ -ansi -c -g -Wall funix.cpp

directory.o: directory.cpp directory.h
	g++ -ansi -c -g -Wall directory.cpp

permissions.o: permissions.cpp permissions.h
	g++ -ansi -c -g -Wall permissions.cpp

clean:
	 -rm -f *.o core
