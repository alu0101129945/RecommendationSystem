#include "../include/Recomendation.hpp"

/**
 * @brief      Constructs a new instance.
 */
Recomendation::Recomendation (void) {}

/**
 * @brief      Constructs a new instance.
 *
 * @param[in]  inputFile  The input file
 */
Recomendation::Recomendation (std::string inputFile) {
	matrix_.set_InputFile(inputFile);
	matrix_.readFile();
}

/**
 * @brief      Destroys the object.
 */
Recomendation::~Recomendation (void) {}

/**
 * @brief      Gets the type.
 *
 * @return     The type.
 */
unsigned Recomendation::get_Type (void) const {
	return type_;
}

/**
 * @brief      Sets the type.
 *
 * @param[in]  newType  The new type
 */
void Recomendation::set_Type (unsigned newType) {
	type_ = newType;
}

/**
 * @brief      Runs and executes the program
 */
void Recomendation::runProgram (void) {
	matrix_.printMatrix();
	generateUsers();
	
	// Create the similitude
	for (unsigned i = 0; i < users_.size(); i++) {
		for (unsigned j = 0; j < users_.size(); j++) {
			users_[i].addSim(similitude(i, j));
		}
	}

	generateNeighbors();
	
	for (unsigned i = 0; i < users_.size(); i++) {
		users_[i].printUser();
	}

	unsigned predictionType;
	while (predictionType > 3) {
		std::cout << "\n\nSeleccione el tipo de predicción:\n\t- 1. Predicción Simple\n\t- 2. Predicción diferencia con la media\n\t- 0. Salir\n";
		std::cin >> predictionType;
	}

	for (unsigned i = 0; i < users_.size(); i++) {
		for (unsigned j = 0; j < users_[i].get_Valoration().size(); j++) {
			if (users_[i].get_Valoration()[j] == -1) {
				switch (predictionType) {
					case 0:
						std::exit(0);
						break;
					case 1:
						std::cout << std::endl << "Predicción simple del usuario " << i << " en el elemento " << j << ": " << prediction(i, j, predictionType) << std::endl;
						matrix_.changeValue(i, j, prediction(i, j, predictionType));
						break;
					case 2:
						std::cout << std::endl << "Predicción diferencia con la media del usuario " << i << " en el elemento " << j << ": " << prediction(i, j, predictionType) << std::endl;
						matrix_.changeValue(i, j, prediction(i, j, predictionType));
						break;
				}

			}
		}
	}
	matrix_.printMatrix();
}

/**
 * @brief Calculate prediction 
 * 
 * @param predictionType 
 */
float Recomendation::prediction(unsigned id, unsigned element, unsigned predictionType) {
	float sumA = 0;
	float sumB = 0;
	float result = 0;
	
	for (unsigned i = 0; i < users_[id].get_Neighbors().size(); i++) {
		unsigned idNeighbor = users_[i].get_Neighbors()[i].get_Id();
		if (users_[id].get_Sim()[idNeighbor] < 0)
			sumB += (users_[id].get_Sim()[idNeighbor] * (-1));
		else
			sumB += users_[id].get_Sim()[idNeighbor];

		if (predictionType == 1) {
			sumA += (users_[id].get_Sim()[idNeighbor] * users_[idNeighbor].get_Valoration()[element]);
			result = (sumA / sumB);
		}
		else {
			sumA += (users_[id].get_Sim()[idNeighbor] * (users_[idNeighbor].get_Valoration()[element] - users_[idNeighbor].get_Average()));
			result = users_[id].get_Average() + (sumA / sumB);
		}	
	}
	return int(result);
}

/**
 * @brief      Generate the users with the matrix.
 */
void Recomendation::generateUsers (void) {
	unsigned filteredType = 4;
	std::string typeName = "";
	while (filteredType > 3) {
		std::cout << "\n\nSeleccione el tipo de filtrado colaborativo basado en usuarios:\n\t- 1. Correlación de Pearson\n\t- 2. Distancia Coseno\n\t- 3. Distancia Euclídea\n\t- 0. Salir\n";
		std::cin >> filteredType;
	}
	set_Type(filteredType);
	std::system("clear");
	switch (filteredType) {
		case 0:
			std::exit(0);
			break;
		case 1:
			typeName = "Correlación de Pearson";
			break;
		case 2:
			typeName = "Distancia Coseno";
			break;
		case 3:
			typeName = "Distancia Euclídea";
			break;
	}

	for (unsigned i = 0; i < matrix_.get_Rows(); i++) {
		User tmp;
		tmp.set_Id(i);
		for (unsigned j = 0; j < matrix_.get_Columns(); j++) {
			tmp.addValoration(matrix_.get_Matrix()[i][j]);
		}
		tmp.set_Average();
		tmp.set_SimType(typeName);
		users_.push_back(tmp);
	}
}

/**
 * @brief      Calculate the similitud.
 *
 * @param[in]  idA   The identifier a
 * @param[in]  idB   The identifier b
 *
 * @return     The similitude.
 */
float Recomendation::similitude (unsigned idA, unsigned idB) {
	float similitude = 0;
	if (get_Type() == 1) { // Pearson case
		float sumUxI = 0.0;
		float sumU = 0.0;
		float sumI = 0.0;
		for (unsigned k = 0; k < users_[idA].get_Valoration().size(); k++) {
			if (users_[idA].get_Valoration()[k] != -1 and users_[idB].get_Valoration()[k] != -1) {
				sumUxI += ((users_[idA].get_Valoration()[k] - users_[idA].get_Average()) * (users_[idB].get_Valoration()[k] - users_[idB].get_Average()));
				sumU += ((users_[idA].get_Valoration()[k] - users_[idA].get_Average()) * (users_[idA].get_Valoration()[k] - users_[idA].get_Average()));
				sumI += ((users_[idB].get_Valoration()[k] - users_[idB].get_Average()) * (users_[idB].get_Valoration()[k] - users_[idB].get_Average()));
			}
		}
		similitude = (sumUxI / (std::sqrt(sumU) * std::sqrt(sumI)));
	}
	else if (get_Type() == 2) {	// Coseno case
		float sumUxI = 0.0;
		float sumU = 0.0;
		float sumI = 0.0;
		for (unsigned k = 0; k < users_[idA].get_Valoration().size(); k++) {
			if (users_[idA].get_Valoration()[k] != -1 and users_[idB].get_Valoration()[k] != -1) {
				sumUxI += (users_[idA].get_Valoration()[k]  * users_[idB].get_Valoration()[k]);
				sumU += (users_[idA].get_Valoration()[k]  * users_[idA].get_Valoration()[k]);
				sumI += (users_[idB].get_Valoration()[k]  * users_[idB].get_Valoration()[k]);
			}
		}
		similitude = (sumUxI / (std::sqrt(sumI) * std::sqrt(sumU)));
	}
	else if (get_Type() == 3) {	// Euclidea case
		float sum = 0;
		for (unsigned k = 0; k < users_[idA].get_Valoration().size(); k++) {
			if (users_[idA].get_Valoration()[k] != -1 and users_[idB].get_Valoration()[k] != -1) {
				float dist = (users_[idA].get_Valoration()[k]  - users_[idB].get_Valoration()[k]);
				sum += (dist * dist);
			}
		}
		similitude = std::sqrt(sum);
	}
	return similitude;
}

/**
 * @brief      Generates the neighbours of each user
 */
void Recomendation::generateNeighbors (void) {
	const unsigned K = 3;	// Minimum neighbors 
	for (unsigned i = 0; i < users_.size(); i++) {
		while (users_[i].get_Neighbors().size() < K) {
			resetNeighbors(i);
		}
	}
}

/**
 * @brief      Adds a new neighbour to the user
 *
 * @param[in]  id    The identifier
 */
void Recomendation::resetNeighbors (unsigned id) {
	float tmpSim;
	unsigned tmpId = id;
	if (get_Type() == 1 or get_Type() == 2) {
		tmpSim = -1;
		for (unsigned j = 0; j < users_[id].get_Sim().size(); j++) {
			if ((id != j) and (users_[id].get_Sim()[j] > tmpSim) and (containsNeighbor(users_[id].get_Neighbors(), j) == false)) {
				tmpSim = users_[id].get_Sim()[j];
				tmpId = j;
			}
		}
	}
	else if (get_Type() == 3) {
		tmpSim = 999999;
		for (unsigned j = 0; j < users_[id].get_Sim().size(); j++) {
			if ((id != j) and (users_[id].get_Sim()[j] < tmpSim) and (containsNeighbor(users_[id].get_Neighbors(), j) == false)) {
				tmpSim = users_[id].get_Sim()[j];
				tmpId = j;
			}
		}
	}
	users_[id].addNeighbor(users_[tmpId]);
}

/**
 * @brief      Looks if a vector contains the element
 *
 * @param[in]  v     The vector
 * @param[in]  id    The element identifier
 *
 * @return     True if it contains the element, false otherwhise.
 */
bool Recomendation::containsNeighbor (std::vector<User> n, unsigned id) {
	for (unsigned i = 0; i < n.size(); i++) {
		if (n[i].get_Id() == id)
			return true;
	}
	return false;
}