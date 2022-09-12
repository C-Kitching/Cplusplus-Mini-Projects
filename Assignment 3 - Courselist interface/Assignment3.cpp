//GENERAL INFO
//File Name : Assignment 3
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 11/02/20
//Date Last Edited : 14/01/22

// Description
// 1.	Program to store and print physics courses
//		User inputs arbitrary number of courses
//		Provide course code (as integer) and title (as string)
//		Use stringstream to create a string containing all info
//		Store strings in a vector
//		Print out inputted course list using an iterator
// 2.	Asks user to choose a year and a sort method
//		Prints out all courses as specified

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

// Decalre Functions
bool comparisonFunc_code(const std::string& a, const std::string& b);
bool comparisonFunc_name(const std::string& a, const std::string& b);

//Begin main program
int main() {

	// declare variables
	const std::string degreeCode("PHYS");  // decalre constant prefix

	std::string userinput_course_title;  // string to hold course title input
	std::string year_choice;  // extract courses for a year of choice
	std::string sort_option;  // string to ask to sort by year or code 
	std::string data_course_title;  // string to hold course title from data file

	std::vector<std::string> userinput_course_info;  // vector of strings to hold full input course titles
	std::vector<std::string> data_course_info;  // vector of strings to hold full data course titles

	int one_entry_counter{ 0 };  // counter to ensure at least one entry

	// do-while loop to get arbitrary number of inputs
	do {

		int valid_input_counter{ 0 };  // initialse counter to ensure valid input
		bool duplicate{ false };  // bool type to check for duplicate input, initialised to false

		// while loop to check input course is valid
		while(valid_input_counter == 0) {

			// ask user to input course name
			std::cout << "Please enter a course name (or x to finish): ";
			std::getline(std::cin, userinput_course_title);

			// if user is trying to exit
			if (userinput_course_title == "x") {
				valid_input_counter++; // add one to counter to break while loop
			}

			// check for duplicate input
			if (one_entry_counter != 0) {
				
				std::ostringstream duplicatetest_userinput_output_stream;  // declare an output stringstream
				duplicatetest_userinput_output_stream << degreeCode << " " << userinput_course_title;  // set the output stringstream
				std::string duplicatetest_full_input_course_title{ duplicatetest_userinput_output_stream.str() };  // extract string part

				// declare vector iterators
				std::vector <std::string>::iterator duplicate_vector_begin{ userinput_course_info.begin() };
				std::vector <std::string>::iterator duplicate_vector_end{ userinput_course_info.end() };
				std::vector <std::string>::iterator duplicate_vector_iterator;

				// iterator over the vector
				for (duplicate_vector_iterator = duplicate_vector_begin; duplicate_vector_iterator < duplicate_vector_end; duplicate_vector_iterator++) {

					// if there is duplicate input
					if (*duplicate_vector_iterator == duplicatetest_full_input_course_title) {
					
						std::cerr << "Error: You have already entered this course. Please input a different course." << std::endl;  // output error statement
						valid_input_counter++;  // add one to counter to break while loop
						duplicate = true;  // set duplicate bool to true
						break;  // break iterator

					}
				}
			}

			// if user is not trying to exit
			if (userinput_course_title != "x"){

				std::ifstream courselist_datafile("courselist.dat"); // open the data file

				// if file opens successfully
				if (courselist_datafile.good()) {

					// while not at the end of the file
					while (std::getline(courselist_datafile, data_course_title, '\n')) {

						// if user input matches data
						if (data_course_title == userinput_course_title) {
							valid_input_counter++;  // add one to valid input counter
						}
					}
				}

				courselist_datafile.close();  // close the data file

				// if user input is not valid
				if (valid_input_counter == 0) {
					std::cerr << "Error: No such course exists. Please input a valid course. [XXXXX(3 spaces)name]" << std::endl;  // output error message
				}
			}
		}

		// if the input is not a duplicate
		if (duplicate != true) {

			// if user tried to exit with no inputs
			if (userinput_course_title == "x" && one_entry_counter == 0){
				std::cerr << "Error: You must enter at least one course name." << std::endl;  // output error message
			}

			std::ostringstream userinput_output_stream;  // declare an output stringstream
			userinput_output_stream << degreeCode << " " << userinput_course_title;  // set the output stringstream
			std::string full_input_course_title{ userinput_output_stream.str() };  // extract string part

			// if user hasn't opted to finish
			if (userinput_course_title != "x") {
				userinput_course_info.push_back(full_input_course_title);  // push back full course title onto a vector
				std::cout << "Course registered." << std::endl;
				one_entry_counter++;  // increment counter
			}

			userinput_output_stream.str(""); //clear stream content

		}

	} while (userinput_course_title != "x" || one_entry_counter == 0);

	// declare vector iterators
	std::vector <std::string>::iterator input_vector_begin{userinput_course_info.begin()};
	std::vector <std::string>::iterator input_vector_end{userinput_course_info.end()};
	std::vector <std::string>::iterator input_vector_iterator;

	// iterator over the vector
	for (input_vector_iterator = input_vector_begin; input_vector_iterator < input_vector_end; input_vector_iterator++) {
		std::cout << *input_vector_iterator << std::endl;  // write out vector to console
	}

	// check for valid input
	do {

		// ask user to input a year
		std::cout << "Please enter a year: ";
		std::getline(std::cin, year_choice);

		// if input not valid
		if (year_choice != "1" && year_choice != "2" && year_choice != "3" && year_choice != "4") {

			std::cerr << "Error: please input an integer 1-4." << std::endl;  // output error message

		}

	} while (year_choice != "1" && year_choice != "2" && year_choice != "3" && year_choice != "4");

	// check for valid input
	do {

		// ask user how they want the data sorted
		std::cout << "Sort the courses by code or name: ";
		std::getline(std::cin, sort_option);

		// if input not valid
		if (sort_option != "code" && sort_option != "name" && sort_option != "Code" && sort_option != "Name") {
			std::cerr << "Error: please input 'code' or 'name'." << std::endl;  // output error message
		}

	} while (sort_option != "code" && sort_option != "name" && sort_option != "Code" && sort_option != "Name");

	std::ifstream courselist_datafile_2("courselist.dat"); // open the data file

	// if file opens successfully
	if (courselist_datafile_2.good()) {

		// while not at the end of the file
		while (std::getline(courselist_datafile_2, data_course_title, '\n')){

			// if the course is for the correct year
			if (data_course_title[0] == year_choice[0]) {
						
				std::ostringstream datainput_output_stream;  // declare output stringstream
				datainput_output_stream << degreeCode << " " << data_course_title;  // set the output stringstream
				std::string full_data_course_title{ datainput_output_stream.str() };  // extract the string part

				data_course_info.push_back(full_data_course_title);  // push back full data course title onto a vector

			}
		}
	}

	courselist_datafile_2.close();  // close data file

	// declare vector iterators
	std::vector <std::string>::iterator data_vector_begin{ data_course_info.begin() };
	std::vector <std::string>::iterator data_vector_end{ data_course_info.end() };
	std::vector <std::string>::iterator data_vector_iterator;

	// sort courses by code
	if (sort_option == "code") {
		std::sort(data_vector_begin, data_vector_end, comparisonFunc_code);
		std::cout << "Sorting the Year " << year_choice << " courses by code:" << std::endl;
	}

	// sort courses by name
	if (sort_option == "name") {
		std::sort(data_vector_begin, data_vector_end, comparisonFunc_name);
		std::cout << "Sorting the Year " << year_choice << " courses by name:" << std::endl;
	}

	// iterator over the vector
	for (data_vector_iterator = data_vector_begin; data_vector_iterator < data_vector_end; data_vector_iterator++) {
		std::cout << *data_vector_iterator << std::endl;  // write out vector to console
	}

	return 0;

}  // end of main program


// Function definitions

// comparison function to sort strings by code
bool comparisonFunc_code(const std::string& a, const std::string& b){
	return a[5] < b[5];
}

// comparison function to sort strings by name
bool comparisonFunc_name(const std::string& a, const std::string& b) {
	return a[13] < b[13];
}