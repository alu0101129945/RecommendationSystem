# Variables
TIME =$(LOGPATH)$(shell date)
# Object Vars
OBJECTS = main.o Matrix.o User.o Recomendation.o
# Compilation flags
CFLAGS = -c -std=c++17 -Wall

recomendation: $(OBJECTS)
	g++ $(OBJECTS) -o recomendation
	mv recomendation ../bin

main.o: ../src/main.cpp
	g++ $(CFLAGS) ../src/main.cpp

Matrix.o: ../src/Matrix.cpp ../include/Matrix.hpp
	g++ $(CFLAGS) ../src/Matrix.cpp

User.o: ../src/User.cpp ../include/User.hpp
	g++ $(CFLAGS) ../src/User.cpp

Recomendation.o: ../src/Recomendation.cpp ../include/Recomendation.hpp
	g++ $(CFLAGS) ../src/Recomendation.cpp


.PHONY: clean
clean:
	rm -rf ../build/*.o
	rm -rf ../bin/*

run:
	../bin/recomendation ../inputs/input_file.txt