#include "../include/Matrix.hpp"

/**
 * @brief      Constructs a new instance.
 */
Matrix::Matrix (void) {
	set_Rows(0);
	set_Columns(0);
	set_InputFile("");
}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 */
Matrix::Matrix (std::string inputFile) {
	set_Rows(0);
	set_Columns(0);
	set_InputFile(inputFile);
	readFile();
}

/**
 * @brief      Destroys the object.
 */
Matrix::~Matrix (void) {}

unsigned Matrix::get_Rows (void) const {
	return rows_;
}

/**
 * @brief      Gets the columns.
 *
 * @return     The columns.
 */
unsigned Matrix::get_Columns (void) const {
	return columns_;
}

/**
 * @brief      Gets the matrix.
 *
 * @return     The matrix.
 */
std::vector<std::vector<int>> Matrix::get_Matrix (void) const {
	return matrix_;
}

/**
 * @brief      Gets the input file.
 *
 * @return     The input file.
 */
std::string Matrix::get_InputFile (void) const {
	return inputFile_;
}


/**
 * @brief      Sets the rows.
 *
 * @param[in]  newRows  The new rows
 */
void Matrix::set_Rows (unsigned newRows) {
	rows_ = newRows;
}

/**
 * @brief      Sets the columns.
 *
 * @param[in]  newColumns  The new columns
 */
void Matrix::set_Columns (unsigned newColumns) {
	columns_ = newColumns;
}

/**
 * @brief      Sets the input file.
 *
 * @param[in]  newInputFile  The new input file
 */
void Matrix::set_InputFile (std::string newInputFile) {
	inputFile_ = newInputFile;
}


/**
 * @brief      Reads a file.
 */
void Matrix::readFile (void) {
	std::ifstream file(inputFile_, std::ios::in);
	if (file.fail()) {
		std::cout << std::endl << "Error 404, file not found." << std::endl;
		exit(1);
	}
	while (!file.eof()) {
		std::string line = "";
		std::getline(file, line);
		if (line.length() > 1)
			matrix_.push_back(generateRow(line));
	}
	set_Rows(matrix_.size());
	set_Columns(matrix_[0].size());
	file.close();
}

/**
 * @brief      Prints a matrix.
 */
void Matrix::printMatrix (void) {
	std::cout << std::endl << " ---------------------- Matriz: ---------------------- " << std::endl;
	for (unsigned i = 0; i < rows_; i++) {
		std::cout << "\n|\t";
		for (unsigned j = 0; j < columns_; j++) {
			std::cout << matrix_[i][j] << "\t";
		}
		std::cout << "|";
	} 
}

/**
 * @brief Change the prediction value
 * 
 * @param id The user id
 * @param element The item of the user
 * @param value Result of the prediction
 */
void Matrix::changeValue(unsigned id, unsigned element, int value) {
	matrix_[id][element] = value;
}

/**
 * @brief      Generate a vector with the matrix row.
 *
 * @param[in]  line  The line
 *
 * @return     The vector with the row items.
 */
std::vector<int> Matrix::generateRow (std::string line) {
	std::vector<int> result;
	std::string tmp = "";
	for (unsigned i = 0; i < line.length(); i++) {
		if ((line[i] == ' ') and (tmp.length() > 0)) {
			result.push_back(std::stoi(tmp));
			tmp = "";
		}
		else if (line[i] == '-') {
			tmp += "-1";
		}
		else {
			tmp += line[i];
		}
	}
	
	if (tmp.length() > 0)
		result.push_back(std::stoi(tmp));
		
	return result;
}
