//GENERAL INFO
//File Name : Assignment 2
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 03/02/20
//Date Last Edited : 06/02/20

// Description
// Program to compute mean, standard deviation and standard
// error of the mean electronic charge. Data is read from file

// Includes
#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include <string> 
#include <limits>  

// Declare functions
double calc_mean(const double x[], const int& size);  // function to calculate mean of array elements
double calc_std_dev(const double x[], const double& mean, const int& size);  // function to calculate standard deviation of array elements

// Begin main program
int main() {

	// Declare variables
	std::string number_data_points;
	std::string filename;

	int number_data_points_int{ 0 };  // number of data points in file
	int marker;  // marker to hold position of invalid characters in input
	int bad_data_counter{ 0 };  // counter to track number of bad data points, initiaised to zero
	int position{ 0 }; // track line of read file

	double mean;
	double std_dev;
	double std_err_mean;
	double throw_away;  // variable to initially read through file and determine number of data points

	// ask user to input filename
	std::cout << "Enter the file name: ";
	std::cin >> filename;

	// open file initially to determine the number of data points

	std::ifstream my_file(filename); // attempt to open read file

	// if file did not open successfully
	if (!my_file.good()) {
		std::cerr << "Error: file could not be opened" << std::endl;  // print error message
		return(1);  // exit program
	}

	// if file opened successfully
	if (my_file.good()) {

		std::cout << "Read file opened successfully" << std::endl;

		// while not at end of file
		while (!my_file.eof()) {

			my_file >> throw_away;  // read data into a throw away string

			// if the data is valid
			if (!my_file.fail()) number_data_points_int++;  // add one to counter

			// if data bad
			else {
				my_file.clear();  // take stream out of fail state
				my_file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore invalid input
			}
		} 
	}

	my_file.close();  // close the file

	double* my_data; // declare my_data as a pointer to a double
	my_data = new double[number_data_points_int]; // mydata now points to new array of N doubles

	std::ifstream my_file2(filename); // re-open the file

	// while not at the end of the file
	while (!my_file2.eof() && position < number_data_points_int) {

		my_file2 >> my_data[position];  // read data into array

		// check for bad data
		if (my_file2.fail()) {
			std::cout << "Error: bad data detected on line " << position + 1 << ", ignored" << std::endl;  // output error message
			bad_data_counter++;
			my_file2.clear();  // take stream out of fail state
			my_file2.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // ignore invalid input
		}

		position++;  // move to next line

	} 

	number_data_points_int -= bad_data_counter;  // adjust N 

	mean = calc_mean(my_data, number_data_points_int);  // calculate mean of data
	std_dev = calc_std_dev(my_data, mean, number_data_points_int);  // calculate standard deviation of data
	std_err_mean = mean / sqrt(number_data_points_int);  // calculate standard error in the mean

	// output results
	std::cout << number_data_points_int << " valid data points were read in. \nThe mean charge is "  << mean <<
		"C.\nThe standard deviation on the charge is " << std_dev << "C.\nThe standard error in the mean is "  << std_err_mean << "C." << std::endl;

	delete[] my_data;  // delete my_data array

	my_file.close();  // reached end of file so close it
	
	return 0;

}  // end of main program

// Function to calculate mean
double calc_mean(const double x[], const int& size) {

	double mean; // declare mean to be returned
	double summation{ 0 };  // declare and initalise sum to 0

	// for loop to calculate sum of array elements
	for (int i = 0; i < size; i++) summation += x[i];

	return mean = summation / size;  // compute mean
}

// Function to calculate standard deviation
double calc_std_dev(const double x[], const double& mean, const int& size) {

	double std_dev;  // declare standard deviation to be returned
	double summation{ 0 };  // decalre and initialise summation to 0

	// for loop to calculate sum of array elements
	for (int i = 0; i < size; i++) summation += pow((x[i] - mean), 2);

	return std_dev = sqrt(summation / (size - 1));  // calculate and return standard deviation
}