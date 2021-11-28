#include "../include/User.hpp"

/**
 * @brief      Constructs a new instance.
 */
User::User (void) {
	set_Id(0);
    set_SimType("");
    set_Average();
}

/**
 * @brief      Destroys the object.
 */
User::~User (void) {}

/**
 * @brief      Gets the identifier.
 *
 * @return     The identifier.
 */
unsigned User::get_Id (void) const {
	return id_;
}

/**
 * @brief      Gets the valoration.
 *
 * @return     The valoration.
 */
std::vector<int> User::get_Valoration (void) const {
	return valoration_;
}

/**
 * @brief      Gets the similitude.
 *
 * @return     The similitude.
 */
std::vector<float> User::get_Sim (void) const {
    return sim_;
}

/**
 * @brief      Gets the neighbors.
 *
 * @return     The vector neighbors.
 */
std::vector<User> User::get_Neighbors (void) const {
    return neighbors_;
}

/**
 * @brief      Gets average.
 *
 * @return     Average.
 */
float User::get_Average (void) const {
    return average_;
}

/**
 * @brief      Sets the identifier.
 *
 * @param[in]  newId  The new identifier
 */
void User::set_Id (unsigned newId) {
	id_ = newId;
}

/**
 * @brief      Sets the average.
 */
void User::set_Average (void) {
    float sum = 0;
    unsigned counter = 0;
    for (unsigned i = 0; i < valoration_.size(); i++) {
        if (valoration_[i] != -1) {
            counter++;
            sum += valoration_[i]; 
        }
    }
    average_ = sum / counter;
}

/**
 * @brief      Sets the similitude type.
 *
 * @param[in]  newSim  The new similitude type
 */
void User::set_SimType (std::string newSimType) {
    simType_ = newSimType;
}


/**
 * @brief      Adds a valoration.
 *
 * @param[in]  newValoracion  The new valoration
 */
void User::addValoration (int newValoration) {
	valoration_.push_back(newValoration);
}

/**
 * @brief      Adds a neighbor.
 *
 * @param[in]  newVecino  The new neighbor
 */
void User::addNeighbor (User newNeighbor) {
	neighbors_.push_back(newNeighbor);
    set_Average();
}

/**
 * @brief      Prints an user.
 */
void User::printUser (void) {
    std::cout << "Usuario: " << get_Id() << std::endl;
    std::cout << "Valoraciones: ";
    for (unsigned i = 0; i < get_Valoration().size(); i++) {
        std::cout << "\t" << valoration_[i];
    }
    std::cout << std::endl << "Vecinos: ";
    for (unsigned i = 0; i < get_Neighbors().size(); i++) {
        std::cout << "\t" << neighbors_[i].get_Id();
    }
    std::cout << std::endl << "Similitud por " << simType_ << ":";
    for (unsigned i = 0; i < get_Sim().size(); i++) {
        if (id_ != i) {
            std::cout << std::endl << "\tsim(Person" << id_ << ", Person" << i << ") = " << sim_[i];
        }
    }
    std::cout << std::endl << std::endl;
}

/**
 * @brief      Adds a simulation.
 *
 * @param[in]  newSim  The new simulation
 */
void User::addSim (float newSim) {
    sim_.push_back(newSim);
}