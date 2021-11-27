#include <vector>
#include <iostream>

/**
 * @brief      This class describes an user.
 */
class User {

	private:
		unsigned id_;
		std::vector<int> valoration_;
		std::vector<User> neighbors_;
		std::vector<float> sim_;
		std::string simType_;
		float average_;

	public:

		// Builder 
		User (void);

		// Destroyer
		~User (void);

		// Getter 
		unsigned get_Id (void) const;
		std::vector<int> get_Valoration (void) const;
		std::vector<float> get_Sim (void) const;
		std::vector<User> get_Neighbors (void) const;
		float get_Average (void) const;

		// Setter
		void set_Id (unsigned newId);
		void set_Average (void);
		void set_SimType (std::string newSimType);

		// Functions
		void addValoration (int newValoration);
		void addNeighbor (User newNeighbor);
		void printUser (void);
		void addSim (float newSim);
};