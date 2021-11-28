#include "../include/Recomendation.hpp"

/**
 * @brief      Main function of the program, receives the data file as parameter.
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     0 If program finishes correctly
 */
int main (int argc, char* argv[]) {
	if (argc == 2) {
		Recomendation myRecomendation(argv[1]);
		myRecomendation.runProgram();
	}
	else {
		std::cout << "Modo de empleo: " << std::endl;
		std::cout << "./recomendation [INPUTFILE] " << std::endl;
		std::cout << "Esta tarea está automatizada en el makefile: make run" << std::endl;
	}
	return 0;
}	
