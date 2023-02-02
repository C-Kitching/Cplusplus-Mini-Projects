//GENERAL INFO
//File Name : Assignment 1
//Author : Christopher Kitching
//E - Mail: christopher.kitching@manchester.ac.uk
//Date created : 27 / 01 / 20
//Date last edited : 02 / 02 / 23

//DESCRIPTION
// Program that uses the Bohr model to calculate the photon energies of 
// electron transitions

//INCLUDES
#include<iostream>
#include<iomanip>
#include<cmath>
#include<string>
#include<sstream>
#include<limits>
#include<algorithm>

//DECLARE FUNCTIONS
// calculate photon energy in eV
double Bohr_eV(const int& atomic_number, const int& quantum_number_one, 
	const int& quantum_number_two); 
// calculate photon energy in Joules
double Bohr_J(const int& atomic_number, const int& quantum_number_one, 
	const int& quantum_number_two);
// get user input and validate
int input_valid_int(const std::string& output_message); 

// begin main program
int main() {

	// declare variables
	std::string atomic_number;
	std::string quantum_number_initial;
	std::string quantum_number_final;
	std::string unit;  // string to ask for the units
	std::string swap;  // string to check input order of quantum numbers
	std::string another_calc; // ask user for another calc
	int atomic_number_int;
	int quantum_number_initial_int;
	int quantum_number_final_int;
	int j;  // track position of invalid character in strings
	double photon_energy;  // final result

	std::cout << "Welcome to the photon energy calculator!" << std::endl;  

	// do-while loop for multiple calculations - 1
	do {

		// get atomic number input off user
		atomic_number_int = input_valid_int("Enter your atomic number:");
		atomic_number = std::to_string(atomic_number_int);

		// do-while loop to check quantum number order - 4
		do {

			// get initial quantum number from user
			quantum_number_initial_int = 
				input_valid_int("Enter your initial quantum number:");
			quantum_number_initial = 
				std::to_string(quantum_number_initial_int);

			// get final quantum number from user
			quantum_number_final_int = 
				input_valid_int("Enter your final quantum number:");
			quantum_number_final = std::to_string(quantum_number_final_int);

			// check if final quantum number is smaller than the initial
			if (quantum_number_final_int > quantum_number_initial_int) {

				// ask user to swap quantum numbers or re-enter them
				std::cout << "Your final quantum number is greater than your " 
					"initial quantum number. Did you mean n_intial= " 
					<< quantum_number_final_int << " and n_final= " 
					<< quantum_number_initial_int << " [Y/N]?: ";
				std::cin >> swap;

				// continously check for valid user repsonse
				while (swap != "Y" && swap != "N") {
					std::cout << "Your input was not valid. Please input 'Y' "
						"for Yes or 'N' for No: "; 
					std::cin.clear(); 
					std::cin.ignore(
						std::numeric_limits<std::streamsize>::max(), '\n');
					std::cin >> swap; 
				}

				// if the user made an input error
				if (swap == "N") {
					std::cout << "Please re-enter your quantum numbers." 
						<< std::endl;
					std::cin.clear(); 
					std::cin.ignore(
						std::numeric_limits<std::streamsize>::max(), '\n');
				}

				// swap number if user entered the wrong way around 
				else std::swap(quantum_number_final_int, 
							   quantum_number_initial_int);
			}

			// check that quantum numbers are not equal
			if(quantum_number_initial_int == quantum_number_final_int) {
				std::cout << "You have inputted the same initial and final "
					"quantum number. Please re-enter your numbers." 
					<< std::endl;;
			}

		} while(quantum_number_final_int > quantum_number_initial_int 
				|| quantum_number_initial_int == quantum_number_final_int);

		// ask user to input the unit they want the ouput in
		std::cout << "Do you want the energy printed in joules [J] or "
			"electron volts [eV]?: ";
		std::cin >> unit;

		// continuously check for valid unit request
		while (unit != "J" && unit != "eV") {
			std::cout << "Your input is not valid. Please input 'J' for "
				"joules or 'eV' for electron volts: ";
			std::cin.clear(); 
			std::cin.ignore(
				std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> unit; 
		}

		// calculate and output photon energy in joules
		if (unit == "J") {
			photon_energy = Bohr_J(atomic_number_int, 
								   quantum_number_initial_int, 
								   quantum_number_final_int);
			std::cout << "The energy of a photon emmitted from an electron "
				"transition in an atom with atomic number Z=" 
				<< atomic_number << ", from the electron level n=" 
				<< quantum_number_initial << " to the level n=" 
				<< quantum_number_final << ", is "
				<< std::setprecision(3) << photon_energy << 
				"J (3.s.f)." << std::endl;
		}
		// calculate and output photon energy in electron volts
		else {
			photon_energy = Bohr_eV(atomic_number_int, 
									quantum_number_initial_int, 
									quantum_number_final_int);
			std::cout << "The energy of a photon emmitted from an electron "
				"transition in an atom with atomic number Z=" 
				<< atomic_number << ", from the electron level n=" 
				<< quantum_number_initial << " to the level n=" 
				<< quantum_number_final << ", is " << std::setprecision(3) 
				<< photon_energy << "eV (3.s.f)." << std::endl;
		}

		// ask user if they wish to do another calculation
		std::cout << "Would you like to do another calculation [Y/N]?: ";
		std::cin >> another_calc;

		// continuously check for valid user response
		while (another_calc != "Y" && another_calc != "N") {
			std::cerr << "Your input was not valid. Please input 'Y' for Yes "
				"or 'N' for No: ";
			std::cin.clear(); 
			std::cin.ignore(
				std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin >> another_calc;
		}

		// say goodbye if no other calc wanted
		if (another_calc == "N") {
			std::cout << "Thank you for using this calculator." << std::endl;
		}

		// if user wants to do another calculation, clear all input
		if (another_calc == "Y") {
			// clear all previous input
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			atomic_number.clear();
			quantum_number_initial.clear();
			quantum_number_final.clear();
		}

	} while (another_calc == "Y");

	return 0;
}  // end of main program


//FUNCTION DEFINITIONS

// function to calculate energy of photon in electron transitions in eV
double Bohr_eV(const int& atomic_number, const int& quantum_number_initial, 
	const int& quantum_number_final) {

	double photon_energy;
	photon_energy = 13.6 * pow(atomic_number, 2) * 
	(1 / pow(quantum_number_final, 2) - 1 / pow(quantum_number_initial, 2));
	return photon_energy;
}

// function to calculate energy of photon in electron transitions in Joules
double Bohr_J(const int& atomic_number, const int& quantum_number_initial, 
	const int& quantum_number_final) {

	double photon_energy;
	photon_energy = 13.6 * 1.602e-19 * pow(atomic_number, 2) * 
	(1 / pow(quantum_number_final, 2) - 1 / pow(quantum_number_initial, 2)); 
	return photon_energy;
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

			// check for blank input
			if(user_input == ""){
				integer = false; 
				std::cerr << "Please input a non-blank value" << std::endl;
				std::cin.clear(); 
				std::cin.ignore(
					std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			// loop over all elements in string
			for (int i = 0; i < user_input.size(); i++) {

				// if whitespace or not a digit
				if (std::isspace(user_input[i]) 
					|| !std::isdigit(user_input[i])){

					integer = false; 
					std::cerr << "Please enter a valid number" << std::endl;
					std::cin.clear(); 
					std::cin.ignore(
						std::numeric_limits<std::streamsize>::max(), '\n');
					break;
				}
			}
		} while (!integer);

		user_input_int = std::stoi(user_input);  // convert string to integer

		// check the integer is not zero
		if (user_input_int == 0) {
			std::cerr << "Please enter a number greater than 0" << std::endl;
			std::cin.clear(); 
			std::cin.ignore(
				std::numeric_limits<std::streamsize>::max(), '\n');
		}

	} while (user_input_int == 0);
	
	return user_input_int;
}