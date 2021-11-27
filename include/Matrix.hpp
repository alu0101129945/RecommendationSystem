#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief      This class describes a matrix.
 */
class Matrix {

	private:
		unsigned rows_;
		unsigned columns_;
		std::vector<std::vector<int>> matrix_;
		std::string inputFile_;

	public:
	
		// Builders 
		Matrix (void);
		Matrix (std::string inputFile);

		// Destroyer
		~Matrix (void);

		// Getters
		unsigned get_Rows (void) const;
		unsigned get_Columns (void) const;
		std::vector<std::vector<int>> get_Matrix (void) const;
		std::string get_InputFile (void) const;

		// Setters
		void set_Rows (unsigned newRows);
		void set_Columns (unsigned newColumns);
		void set_InputFile (std::string newInputFile);

		// Functions
		void readFile (void);
		void printMatrix (void);
		std::vector<int> generateRow (std::string line);
		void changeValue(unsigned id, unsigned element, int value);
};