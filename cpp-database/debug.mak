debug.mak: user_interface.o llist.o
	g++ -o project_debug llist.o user_interface.o
llist.o: llist.cpp
	g++ -ansi -pedantic-errors -Wall -D debug -c llist.cpp
user_interface.o: user_interface.cpp
	g++ -ansi -pedantic-errors -Wall -D debug -c user_interface.cpp
