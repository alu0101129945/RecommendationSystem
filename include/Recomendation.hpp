#include "User.hpp"
#include "Matrix.hpp"
#include <cmath>

/**
 * @brief      This class describes a recomendation.
 */
class Recomendation {

	private:
		Matrix matrix_;
		std::vector<User> users_;
		unsigned type_;

	public:

		// Builders 
		Recomendation (void);
		Recomendation (std::string inputFile);

		// Destroyer
		~Recomendation (void);

		// Getter 
		unsigned get_Type (void) const;

		// Setter
		void set_Type (unsigned newType);

		// Functions
		void runProgram (void);
		void generateUsers (void);
		void generateNeighbors (void);
		float similitude (unsigned idA, unsigned idB);
		void resetNeighbors (unsigned id);
		bool containsNeighbor (std::vector<User> n, unsigned id);
		float prediction(unsigned id, unsigned element, unsigned predictionType);
};