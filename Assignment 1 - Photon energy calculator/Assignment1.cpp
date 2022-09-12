//GENERAL INFO
//File Name : Assignment 1
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date created : 27 / 01 / 20
//Date last edited : 13 / 01 / 22

//DESCRIPTION
// Program that uses the Bohr model to calculate the photon energies of electron transitions

//INCLUDES
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<sstream>

//DECLARE FUNCTIONS
double Bohr_eV(int atomic_number, int quantum_number_one, int quantum_number_two);  // calculate photon energy in eV
double Bohr_J(int atomic_number, int quantum_number_one, int quantum_number_two);  // calculate photon energy in Joules
int input_valid_int(const std::string& output_message);  // get user input and validate

// begin main program
int main() {

	// declare variables
	std::string atomic_number;
	std::string quantum_number_initial;
	std::string quantum_number_final;
	std::string unit;  // string to ask for the units
	std::string swap;  // string to check input order of quantum numbers
	std::string another_calc; // string to ask the user if they wish to do a calculation

	int atomic_number_int;
	int quantum_number_initial_int;
	int quantum_number_final_int;
	int j;  // track position of invalid character in strings

	double photon_energy;

	std::cout << "Welcome to the photon energy calculator!" << std::endl;  // output intro statement

	// do-while loop for multiple calculations - 1
	do {

		// get atomic number input off user
		atomic_number_int = input_valid_int("Enter your atomic number:");
		atomic_number = std::to_string(atomic_number_int);

		// do-while loop to check quantum number order - 4
		do {

			// get initial quantum number from user
			quantum_number_initial_int = input_valid_int("Enter your initial quantum number:");
			quantum_number_initial = std::to_string(quantum_number_initial_int);

			// get final quantum number from user
			quantum_number_final_int = input_valid_int("Enter your final quantum number:");
			quantum_number_final = std::to_string(quantum_number_final_int);

			// check if final quantum number is smaller than the initial
			if (quantum_number_final_int > quantum_number_initial_int) {

				// ask user to swap quantum numbers or re-enter them
				std::cout << "Your final quantum number is greater than your initial quantum number. Did you mean n_intial= " << quantum_number_final_int <<
					" and n_final= " << quantum_number_initial_int << " [Y/N]?: ";
				std::cin >> swap;

				// check if the users response is valid
				while (swap != "Y" && swap != "N") {

					std::cout << "Your input was not valid. Please input 'Y' for Yes or 'N' for No: "; 
					std::cin.clear();  // clear error
					std::cin.ignore(1000, '\n');  // ignore input
					std::cin >> swap;  // ask user for a new input

				}

				// if the user made an input error
				if (swap == "N") {
					std::cout << "Please re-enter your quantum numbers." << std::endl;
					std::cin.clear();  // clear error
					std::cin.ignore(1000, '\n');  // ignore input
				}

				// if the user entered the quantum numbers the wrong way around 
				else {
					std::swap(quantum_number_final_int, quantum_number_initial_int);  // swap quantum numbers
				}
			}

			// check that quantum numbers are not equal
			if (quantum_number_initial_int == quantum_number_final_int) {
				std::cout << "You have inputted the same initial and final quantum number. Please re-enter your numbers." << std::endl;;
			}

		} while (quantum_number_final_int > quantum_number_initial_int || quantum_number_initial_int == quantum_number_final_int);

		// ask user to input the unit they want the ouput in
		std::cout << "Do you want the energy printed in joules [J] or electron volts [eV]?: ";
		std::cin >> unit;

		// check unit input is a valid string
		while (unit != "J" && unit != "eV") {

			std::cout << "Your input is not valid. Please input 'J' for joules or 'eV' for electron volts: ";  // output error message
			std::cin.clear();  // clear error
			std::cin.ignore(1000, '\n');  // ignore input
			std::cin >> unit;  // ask user for new input
		}

		// calculate photon energy in joules
		if (unit == "J") {

			photon_energy = Bohr_J(atomic_number_int, quantum_number_initial_int, quantum_number_final_int); // call function to calculate energy in joules

			std::cout << "The energy of a photon emmitted from an electron transition in an atom with atomic number Z=" << atomic_number <<
				", from the electron level n=" << quantum_number_initial << " to the level n=" << quantum_number_final << ", is "
				<< std::setprecision(3) << photon_energy << "J (3.s.f)." << std::endl;  // output statement
		}
		// calculate photon energy in electron volts
		else {

			photon_energy = Bohr_eV(atomic_number_int, quantum_number_initial_int, quantum_number_final_int); // call function to calculate energy in eV

			std::cout << "The energy of a photon emmitted from an electron transition in an atom with atomic number Z=" << atomic_number <<
				", from the electron level n=" << quantum_number_initial << " to the level n=" << quantum_number_final << ", is "
				<< std::setprecision(3) << photon_energy << "eV (3.s.f)." << std::endl;  // output statement
		}

		// ask user if they wish to do another calculation
		std::cout << "Would you like to do another calculation [Y/N]?: ";
		std::cin >> another_calc;

		// check if the users response is valid
		while (another_calc != "Y" && another_calc != "N") {

			std::cout << "Your input was not valid. Please input 'Y' for Yes or 'N' for No: ";  // output error message
			std::cin.clear();  // clear error
			std::cin.ignore(1000, '\n');  // ignore input
			std::cin >> another_calc;  // ask user for a new input
		}

		// if user doesn't want to do another calculation
		if (another_calc == "N") {
			std::cout << "Thank you for using this calculator.";  // output goodbye message
		}

		// if user wants to do another calculation, clear all input
		if (another_calc == "Y") {

			std::cin.ignore(1000, '\n');  // ignore input
			atomic_number.clear();
			quantum_number_initial.clear();
			quantum_number_final.clear();
		}

	} while (another_calc == "Y");

	return 0;
}  // end of main program


//FUNCTION DEFINITIONS

// function to calculate energy of photon in electron transitions in eV
double Bohr_eV(int atomic_number, int quantum_number_initial, int quantum_number_final) {

	double photon_energy;  // declare photon energy to be returned

	photon_energy = 13.6 * pow(atomic_number, 2) * (1 / pow(quantum_number_final, 2) - 1 / pow(quantum_number_initial, 2));  // calculate photon energy in eV

	return photon_energy;  // return photon energy
}

// function to calculate energy of photon in electron transitions in Joules
double Bohr_J(int atomic_number, int quantum_number_initial, int quantum_number_final) {

	double photon_energy;  // declare photon energy to be returned

	photon_energy = 13.6 * 1.602e-19 * pow(atomic_number, 2) * (1 / pow(quantum_number_final, 2) - 1 / pow(quantum_number_initial, 2));  // calculate photon energy in Joules

	return photon_energy;  // return photon energy
}

// function to get user input and check its an int greater than zero
int input_valid_int(const std::string& output_message) {

	// declare variables
	bool integer;
	std::string user_input;
	int user_input_int;

	// loop to request non-zero number
	do {

		// loop to request integer
		do {

			// assume input is an integer
			integer = true;

			// ask user to input an atomic number
			std::cout << output_message;
			std::getline(std::cin, user_input);

			// loop over all elements in string
			for (int i = 0; i < user_input.size(); i++) {

				// if whitespace or not a digit
				if (std::isspace(user_input[i]) || !std::isdigit(user_input[i])) {

					integer = false;  // input is not an integer
					std::cout << "Your input is not valid. Please input an integer value greater than zero." << std::endl;
					std::cin.clear();  // clear error
					break;  // break for loop
				}
			}
		} while (!integer);

		user_input_int = std::stoi(user_input);  // convert string to integer

		// check the integer is not zero
		if (user_input_int == 0) {

			std::cout << "Your input is not valid. Please input an integer value greater than zero." << std::endl;
			std::cin.clear();  // clear error
			std::cin.ignore(1000, '\n');  // ignore input
		}

	} while (user_input_int == 0);
	
	// return input
	return user_input_int;
}