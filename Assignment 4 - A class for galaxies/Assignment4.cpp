//GENERAL INFO
//File Name : Assignment 3
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 18/02/20
//Date Last Edited : 14/01/22

// Description
// demonstration of classes in C++
// classifying galaxies with classification, redshift, total mass and stellar mass fraction

// Includes
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string> 
#include<limits>
#include<sstream>
#include<vector>
#include<algorithm>

// Begin class deceration
class galaxy
{
private:

	// decalre variables
	std::string hubble_type;
	double redshift;
	double total_mass;
	double stellar_mass_fraction;
	std::vector<galaxy> satellite_data;

public:

	// default constructor
	galaxy() : hubble_type{ "Ghost galaxy" }, redshift{}, total_mass{}, stellar_mass_fraction{} {}

	// parameterised constructor
	galaxy(std::string galaxy_hubble_type, double galaxy_redshift, double galaxy_total_mass, double galaxy_stellar_mass_fraction) :
		hubble_type{ galaxy_hubble_type }, redshift{ galaxy_redshift },
		total_mass{ galaxy_total_mass }, stellar_mass_fraction{ galaxy_stellar_mass_fraction }
	{}

	// destructor
	~galaxy() { std::cout << "Destroying hubble type: " << hubble_type << std::endl; }

	// define member function to return stellar mass
	double stellar_mass() { return stellar_mass_fraction * total_mass; }

	// define member function to change galaxys hubble type
	void change_hubble_type(std::string new_type) { hubble_type = new_type; }

	// declare member function to print data
	void print_data();

	// define member function to add satellite galaxy
	void add_satellite(galaxy satellite) { satellite_data.push_back(satellite); }

};

// define member function to print data outside class
void galaxy::print_data() {

	std::cout.precision(3); // set precision to 2 s.f

	// print galaxy data
	std::cout << "Galaxy [type, redshift, total mass, stellar mass fraction, number of satellites] = [" <<
		hubble_type << ", " << redshift << ", " << total_mass << " solar masses, " <<
		stellar_mass_fraction << ", " << satellite_data.size() << "]" << std::endl;

	// if the galaxy has at least one satellite
	if (satellite_data.size() != 0) {
	
		// for loop over all satellites of the galaxy
		for (size_t i{}; i < satellite_data.size(); i++) {

			// print out satellite data
			std::cout << "Satellite " << i+1 << "[type, redshift, total mass, stellar mass fraction] = [" <<
				satellite_data[i].hubble_type << ", " << satellite_data[i].redshift << ", " <<
				satellite_data[i].total_mass << " stellar masses, " << satellite_data[i].stellar_mass_fraction << 
				"]" << std::endl;

		}
	}
}
// end of class decleration and associated member functions


// Decalre functions
void print_galaxy_data(std::vector<galaxy> &galaxy_data);


// Begin main program
int main() {

	// example using default constructor
	galaxy ghost_galaxy;

	// example using parameterised constructor
	galaxy real_galaxy_1("E0", 5.6, 1.5e9, 0.02);
	galaxy real_galaxy_2("Irr", 9.3, 7.3e11, 0.04);

	std::vector<galaxy> galaxy_data;  // declare vector of galaxy data
	galaxy_data.reserve(3);  // reserve space to prevent reallocation

	// push back galaxy data onto vector
	galaxy_data.push_back(ghost_galaxy);
	galaxy_data.push_back(real_galaxy_1);
	galaxy_data.push_back(real_galaxy_2);

	// call function to print out galaxy data
	std::cout << "Printing galaxy data:" << std::endl;
	print_galaxy_data(galaxy_data);

	// spaces for formatting
	std::cout << "\n" << std::endl;

	// change hubble type of g3 Irr -> S0
	std::cout << "Changing hubble type of galaxy" << std::endl;
	galaxy_data[2].change_hubble_type("S0");

	// call function to print galaxy data again with changed hubble type
	std::cout << "Printing galaxy data with hubble type change:" << std::endl;
	print_galaxy_data(galaxy_data);

	// spaces for formatting
	std::cout << "\n" << std::endl;

	// declare satellites
	galaxy satellite_1("E7", 2.2, 5.9e7, 0.03);
	galaxy satellite_2("Sa", 6.8, 3.3e8, 0.07);
	galaxy satellite_3("Sc", 8.5, 6.1e11, 0.09);

	// add satellites to galaxies
	std::cout << "Adding satellites to galaxies" << std::endl;
	galaxy_data[1].add_satellite(satellite_1);
	galaxy_data[1].add_satellite(satellite_2);
	galaxy_data[2].add_satellite(satellite_3);

	// call function to print galaxy data with satellites
	std::cout << "Printing galaxy data with satellites:" << std::endl;
	print_galaxy_data(galaxy_data);

	// spaces for formatting
	std::cout << "\n" << std::endl;

	return 0;

}  // end of main program


// Function definitions

// function to print out galaxy data using an iterator
void print_galaxy_data(std::vector<galaxy>& galaxy_data) {

	// iterator to print out vector data
	for (auto galaxy_it = galaxy_data.begin(); galaxy_it < galaxy_data.end(); ++galaxy_it) {
		galaxy_it->print_data();
		std::cout << " has stellar mass " << galaxy_it->stellar_mass() << " solar masses." << std::endl;
	}
}