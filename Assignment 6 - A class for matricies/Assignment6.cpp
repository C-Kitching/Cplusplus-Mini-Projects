//GENERAL INFO
//File Name : Assignment 6
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 03/03/20
//Date Last Edited : 03/03/20

// Description
// a class for matricies

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

// Begin class decleration
class matrix 
{
	// make function to overload << operator a friend of the matrix class
	friend std::ostream& operator<<(std::ostream& os, const matrix& matrix_array);

	// make function to overload >> operatour a friend of the matrix class
	friend matrix& operator>>(std::istream& is, const matrix& matrix_array);

private:

	int rows;
	int columns;
	double* matrix_data;

public:

	matrix() : rows{ 0 }, columns{ 0 }, matrix_data{ 0 } {}  // default constructor
	matrix(int size_rows, int size_columns);  // paramterised constructor
	matrix(const matrix&);  // copy constructor
	matrix(matrix&&);  // move constructor
	~matrix() { delete matrix_data; /*std::cout << "Destructor called" << std::endl;*/ }  // destuctor

	// Access functions
	int get_rows() const { return rows; }  // return number of rows
	int get_columns() const { return columns; }  // return number of columns
	int index(int m, int n) const  // return position of matrix element (m,n) in 1-D array
	{ 
		// if element in range, return position
		if (m > 0 && m <= rows && n>0 && n <= columns) return (n - 1) + (m - 1) * columns;

		// if element out of range, exit program
		else 
		{	
			std::cerr << "Error: index out of matrix range" << std::endl;
			exit(1);
		}
	}

	matrix& operator=(const matrix&);  // copy assignment operator overload
	matrix& operator=(matrix&&); // move assignment operator overload

	matrix operator+(const matrix& matrix_array) const;  // member function to overload plus operator
	matrix operator-(const matrix& matrix_array) const;  // member function to overload subraction operator
	matrix operator*(const matrix& matrix_array) const;  // member function to overload multiplication operator

	double& element(int i, int j) const;  // member funtion to return element (i,j)
	double& operator()(int i, int j) const;  // member function to overload () to return element (i,j)

	matrix minor(int i, int j) const;  // member function to calculate minors
	double determinant() const;  // member function to calculate determinant
};
// End of class decleration

// parameterised constructor implementation
matrix::matrix(int size_rows, int size_columns) 
{
	//std::cout << "Parameterised constructor called" << std::endl;

	// check number of rows and columns greater than 0
	if (size_rows < 1) {
		std::cerr << "Error: trying to decalre matrix with rows < 1" << std::endl;
		exit(1);
	}
	if (size_columns < 1) {
		std::cerr << "Error: trying to declare matrix with columns < 1" << std::endl;
		exit(1);
	}

	// initialise size of matrix
	rows = size_rows;
	columns = size_columns;

	matrix_data = new double[rows * columns];  // create 1-D array to store matrix data

	for (int i{ 0 }; i < rows * columns; i++) matrix_data[i] = 0;  // fill array
}

// copy constructor for deep copying
matrix::matrix(const matrix& matrix_array) 
{
	//std::cout << "Copy constructor called" << std::endl;

	// copy data of input array
	matrix_data = 0; rows = matrix_array.rows; columns = matrix_array.columns;
	int array_size{ matrix_array.rows * matrix_array.columns };

	// if input array has valid size
	if (array_size > 0)  {
		matrix_data = new double[array_size];  // initialise new array of matrix size
		for (int i{ 0 }; i < array_size; i++) matrix_data[i] = matrix_array.matrix_data[i];  // copy values into new array
	}
}

// move constructor
matrix::matrix(matrix&& matrix_array) 
{
	//std::cout << "Move constructor called" << std::endl;

	// steal data from array
	rows = matrix_array.rows;
	columns = matrix_array.columns;
	matrix_data = matrix_array.matrix_data;

	// reset data of input array
	matrix_array.rows = 0;
	matrix_array.columns = 0;
	matrix_array.matrix_data = nullptr;
}

// overload assignment operator for deep copying
matrix& matrix::operator=(const matrix& matrix_array) 
{
	//std::cout << "Copy assignment" << std::endl;

	if (&matrix_array == this) return *this;  // don't allow self assignment
	delete[] matrix_data; matrix_data = 0;  // delete 'this' array info
	rows = matrix_array.rows; columns = matrix_array.columns;  // copy input array data
	int array_size{ rows * columns };  // initialise array size

	// if matrix size is valid
	if (array_size > 0) {
		matrix_data = new double[array_size];  // decalre new array of matrix size
		for (int i{ 0 }; i < array_size; i++) matrix_data[i] = matrix_array.matrix_data[i];  // copy values into new array
	}

	return *this;
}

// overload assignment operator for moving
matrix& matrix::operator=(matrix&& matrix_array) 
{
	//std::cout << "Move assignment" << std::endl;

	// swap object info
	std::swap(matrix_data, matrix_array.matrix_data);
	std::swap(rows, matrix_array.rows);
	std::swap(columns, matrix_array.columns);

	return *this;
}

// overload addition operator
matrix matrix::operator+(const matrix& matrix_array) const 
{
	// check matricies have the same dimensions
	if (rows != matrix_array.rows || columns != matrix_array.columns) {
		std::cerr << "Error: matricies do not have the same dimensions" << std::endl;
		exit(1);		
	}

	matrix temp_matrix(rows, columns);  // decalre temprorary matrix to sum
	int array_size{ rows * columns };  // initialise array size
	for (int i{0}; i < array_size; i++) temp_matrix.matrix_data[i] = (*this).matrix_data[i] + matrix_array.matrix_data[i];  // sum matricies

	return temp_matrix;
}

// overload subtraction operator
matrix matrix::operator-(const matrix& matrix_array) const
{
	// check matricies have the same dimensions
	if (rows != matrix_array.rows || columns != matrix_array.columns) {
		std::cerr << "Error: matricies do not have the same dimensions" << std::endl;
		exit(1);
	}

	matrix temp_matrix(rows, columns);  // decalre temprorary matrix to sum
	int array_size{ rows * columns };  // initialise array size
	for (int i{ 0 }; i < array_size; i++) temp_matrix.matrix_data[i] = (*this).matrix_data[i] - matrix_array.matrix_data[i];  // sum matricies

	return temp_matrix;
}

// overload multiplication operator
matrix matrix::operator*(const matrix& matrix_array) const 
{
	// check in matricies valid for multiplication
	if (columns != matrix_array.rows) {
		std::cerr << "Error: matricies incompatiable for multiplication" << std::endl;
		exit(1);	
	}

	matrix temp_matrix(rows, matrix_array.columns);  // declare temporary matrix of product size

	// for loops to multiply matricies
	for (int i{ 1 }; i <= rows; i++) {
		for (int k{ 1 }; k <= matrix_array.columns; k++) {
			for (int j{ 1 }; j <= columns; j++){
				temp_matrix(i, k) += element(i, j) * matrix_array(j, k);			
			}	
		}
	}
	return temp_matrix;
}

// return element (i,j)
double& matrix::element(int i, int j)const 
{
	return matrix_data[index(i, j)];
}

// overload () to return element (i,j)
double& matrix::operator()(int i, int j) const 
{
	return element(i, j);
}

// return minor of matrix
matrix matrix::minor(int i, int j) const
{
	// check validity of input
	if (i > rows || j > columns || rows != columns || i < 0 || j < 0) {

		std::cerr << "Error: cannot determine minor of this matrix" << std::endl;
		exit(1);
	}

	// if matrix is 1x1
	if (rows == 1) return *this;

	matrix temp_matrix(rows - 1, columns - 1);  // declare temp matrix of minor size
	int temp_index{ 0 };  // counter for index of temp matrix
	int array_size{ rows * columns };  // initialise size of original matrix

	for (int n{ 1 }; n <= columns; n++) {
		for (int m{ 1 }; m <= rows; m++) {
			if (m != i && n != j) {
				temp_matrix.matrix_data[temp_index] = element(m, n);
				temp_index++;
			}
		}
	}
	return temp_matrix;
}

// return determinanct of matrix
double matrix::determinant() const 
{
	// check if the matrix is square
	if (rows != columns) {
		std::cerr << "Error: matrix is not square, cannot calculate determinant" << std::endl;
		exit(1);
	}

	if (rows == 1) return element(1, 1);  // if matrix is 1x1, return (1,1) element

	double determinant{ 0 };  // initialise determinant to zero

	// loop over columns of matrix
	for (int j{ 1 }; j <= columns; j++) {
		matrix minor_matrix; // decalre a minor matrix with default constructor
		minor_matrix = (*this).minor(1, j);  // calculate the minor
		determinant += pow(-1, j + 1) * element(1, j) * minor_matrix.determinant();  // increment determinant
	}
	return determinant;
}

// friend function to overload insertion operator
std::ostream& operator<<(std::ostream& os, const matrix& matrix_array) 
{
	// loop over all rows
	for (int i{ 1 }; i <= matrix_array.rows; i++) {

		os << "  ";

		// loop over all columns
		for (int j{ 1 }; j <= matrix_array.columns; j++) {
			os << std::setw(5) << matrix_array.element(i, j);  // print out each element of row
		}
		os << std::endl;  // line break at end of row
	}
	return os;
}

// friend function to overload extraction operator
matrix& operator>>(std::istream& is, matrix& input_matrix)
{
	// decalre insertion as a string
	std::string string_input;
	is >> string_input;

	std::stringstream input_stream_count{ string_input };  //  initialise a string stream to deteremine matrix size

	// set some initial variables to determine size of input matrix
	int rows_count{ 0 }; int columns_count{ 0 }; double element_count{ 0 }; 
	char breaker_count{ 0 }; int first_row_breaker_count{ 0 };

	// while not at then end of the input
	while (!input_stream_count.eof()) {

		// while not at the end of the row
		while (breaker_count != ';') {

			input_stream_count >> element_count >> breaker_count;  // read in elements

			// when user enters column seperation
			if (breaker_count == ',') {

				// if on first row
				if (first_row_breaker_count == 0) {
					columns_count++; // record number of columns
				}		
			}

			if (breaker_count == ';') {		

				rows_count++;  // if ';' add a row
			
				// if on first row
				if (first_row_breaker_count == 0) {
					columns_count++; // record number of columns
					first_row_breaker_count++;  // not on first row anymore
				}			
			}

			if (breaker_count == 0) break;  // if at end of matrix, break loop	
		}
		breaker_count = 0; element_count = 0; // reset variables
	}

	// output info about the inputted matrix
	std::cout << "You've inputted a matrix with " << columns_count << " columns and " << rows_count << " rows." << std::endl;

	matrix temp_matrix(rows_count, columns_count );  // decalre a matrix of desired size
	std::stringstream input_stream_read{ string_input };  // intialise a 2nd input stream to read in data

	// set new initial variables to determine size of input matrix
	int rows_read{ 1 }; int columns_read{ 1 }; double element_read{ 0 }; char breaker_read{ 0 };

	// while not at end of input
	while (!input_stream_read.eof()) {

		// while not at the end of the row
		while (breaker_read != ';') {

			input_stream_read >> element_read >> breaker_read;  // read in elements

			if (breaker_read == 0) break;  // if at end of matrix, break loop

			temp_matrix(rows_read, columns_read) = element_read;  // read data to temp matrix

			if (breaker_read == ',') columns_read++;  // user enters column seperation
			if (breaker_read == ';') { rows_read++; columns_read++; }  // user enters row seperation
		}
		columns_read = 1; breaker_read = 0; element_read = 0; // reset variables
	}

	// move temp_matrix to the extraction matrix and return address
	input_matrix = std::move(temp_matrix);
	return(input_matrix);
}


// Begin main program
int main() {

	// demonstrate default constructor
	std::cout << "Default construction of a1" << std::endl;
	matrix a1;
	std::cout << "a1 = " << std::endl;
	std::cout << a1;
	std::cout << std::endl;

	// demonstrate parameterized constructor
	std::cout << "Parameterized construction of b1" << std::endl;
	matrix b1(2, 2);
	std::cout << "b1 = " << std::endl;
	std::cout << b1;
	std::cout << std::endl;

	// demonstrate access functions
	std::cout << "Access functions:" << std::endl;
	std::cout << "b1 has " << b1.get_rows() << " rows and " << b1.get_columns() << " columns" << std::endl;
	std::cout << std::endl;

	// set some values for b1
	std::cout << "Change values of b1" << std::endl;
	b1(1, 1) = 5; b1(1, 2) = -3; 
	b1(2, 1) = 6; b1(2, 2) = 7;
	std::cout << "b1 = " << std::endl;
	std::cout << b1;
	std::cout << std::endl;

	// demonstrate deep copy assingment
	std::cout << "Parameterized construction of b2" << std::endl;
	matrix b2(2, 2);
	std::cout << "b2 = " << std::endl;
	std::cout << b2;
	std::cout << "Deep copy b1 to b2 by assignment" << std::endl;
	b2 = b1;
	std::cout << "b2 = " << std::endl;
	std::cout << b2;
	std::cout << "Now change b1" << std::endl;
	b1(1, 1) = -2; b1(1, 2) = 8; 
	b1(2, 1) = 9; b1(2, 2) = -1;
	std::cout << "b1 = " << std::endl;
	std::cout << b1;
	std::cout << "We deep copied so b2 is unchanged" << std::endl;
	std::cout << "b2 = " << std::endl;
	std::cout << b2;
	std::cout << std::endl;

	// demonstrate deep copy construction
	std::cout << "Parameterized construction of c1" << std::endl;
	matrix c1(2, 3);
	std::cout << "Set some values for c1" << std::endl;
	std::cout << "c1 = " << std::endl;
	c1(1, 1) = -2; c1(1, 2) = 4; c1(1, 3) = 9; 
	c1(2, 1) = 5; c1(2, 2) = 8; c1(2, 3) = -6;
	std::cout << c1;
	std::cout << "Copy constructor to declare c2 and deep copy c1 to c2" << std::endl;
	matrix c2(c1);
	std::cout << "c2 = " << std::endl;
	std::cout << c2;
	std::cout << "Now change c1" << std::endl;
	c1(1, 1) = 8; c1(1, 2) = 3; c1(1, 3) = -2;
	c1(2, 1) = 4; c1(2, 2) = -5; c1(2, 3) = 6;
	std::cout << "c1 = " << std::endl;
	std::cout << c1;
	std::cout << "We deep copied so c2 is unchanged" << std::endl;
	std::cout << "c2 = " << std::endl;
	std::cout << c2;
	std::cout << std::endl;

	// demonstrate move assignment
	std::cout << "Parameterized construction of d1" << std::endl;
	matrix d1(3, 3);
	std::cout << "Set some values for d1" << std::endl;
	d1(1, 1) = -8; d1(1, 2) = 6; d1(1, 3) = 4;
	d1(2, 1) = 2; d1(2, 2) = -1; d1(2, 3) = 3;
	d1(3, 1) = 5; d1(3, 2) = 9; d1(3, 3) = -7;
	std::cout << "d1 = " << std::endl;
	std::cout << d1;
	std::cout << "Parameterized construction of d2" << std::endl;
	matrix d2;
	std::cout << "Move values from d1 to d2 by assignment" << std::endl;
	d2 = std::move(d1);
	std::cout << "d2 = " << std::endl;
	std::cout << d2;
	std::cout << "d1 is no empty" << std::endl;
	std::cout << "d1 = " << std::endl;
	std::cout << d1;
	std::cout << std::endl;

	// demonstrate move construction
	std::cout << "Parameterized construction of e1" << std::endl;
	matrix e1(3, 2);
	std::cout << "Set some values for e1" << std::endl;
	e1(1, 1) = 1; e1(1, 2) = -2; 
	e1(2, 1) = 6; e1(2, 2) = 5;
	e1(3, 1) = -9; e1(3, 2) = 3; 
	std::cout << "e1 = " << std::endl;
	std::cout << e1;
	std::cout << "Move constructor to construct e2, a copy of e1" << std::endl;
	matrix e2(std::move(e1));
	std::cout << "e2 = " << std::endl;
	std::cout << e2;
	std::cout << "e1 is now empty" << std::endl;
	std::cout << "e1 = " << std::endl;
	std::cout << e1;
	std::cout << std::endl;

	// demonstrate determinant
	std::cout << "Parameterized construction of f1" << std::endl;
	matrix f1(4, 4);
	std::cout << "Set some values for f1" << std::endl;
	f1(1, 1) = 2; f1(1, 2) = 3; f1(1, 3) = -2; f1(1, 4) = -6;
	f1(2, 1) = -5; f1(2, 2) = 7; f1(2, 3) = -8; f1(2, 4) = 7;
	f1(3, 1) = 9; f1(3, 2) = 6; f1(3, 3) = -4; f1(3, 4) = 2;
	f1(4, 1) = -7; f1(4, 2) = 5; f1(4, 3) = -9; f1(4, 4) = -1;
	std::cout << "f1 = " << std::endl;
	std::cout << f1;
	std::cout << "Det(f1) = " << f1.determinant() << std::endl;
	std::cout << std::endl;

	// demonstrate matrix addition and subtraction
	std::cout << "Parameterized construction of g1" << std::endl;
	matrix g1(2, 2);
	std::cout << "Set some values for g1" << std::endl;
	g1(1, 1) = 1; g1(1, 2) = -3;
	g1(2, 1) = -6; g1(2, 2) = 8;
	std::cout << g1;
	std::cout << "Parameterized construction of g2" << std::endl;
	matrix g2(2, 2);
	std::cout << "Set some values for g2" << std::endl;
	g2(1, 1) = 4; g2(1, 2) = 2;
	g2(2, 1) = -1; g2(2, 2) = 9;
	std::cout << g2;
	std::cout << "Add matricies" << std::endl;
	std::cout << "g1 + g2 = " << std::endl;
	std::cout << g1 + g2;
	std::cout << "Subtract matricies" << std::endl;
	std::cout << "g1 - g2 = " << std::endl;
	std::cout << g1 - g2;
	std::cout << std::endl;

	// demonstrate matrix multiplication
	std::cout << "Parameterized construction of h1" << std::endl;
	matrix h1(1, 3);
	std::cout << "Set some values for h1" << std::endl;
	h1(1, 1) = 6; h1(1, 2) = 3; h1(1, 3) = -7;
	std::cout << h1;
	std::cout << "Parameterized construction of h2" << std::endl;
	matrix h2(3, 2);
	std::cout << "Set some values for h2" << std::endl;
	h2(1, 1) = 2; h2(1, 2) = -7;
	h2(2, 1) = -8; h2(2, 2) = -3;
	h2(3, 1) = 8; h2(2, 2) = 5;
	std::cout << h2;
	std::cout << "Multiplly matricies" << std::endl;
	std::cout << "h1 * h2 = " << std::endl;
	std::cout << h1 * h2;
	std::cout << std::endl;


	// matrix determinant calculator
	std::cout << "Matrix Determinant Calculator!" << std::endl;
	bool multipleCalc{ true };

	// while loop for multiple calculations
	while(multipleCalc){
	
		std::string anotherCalc;
		matrix input_matrix;

		// read in a matrix
		std::cout << "Please enter a matrix eg. [A11,A12;A21,A22;]: ";
		std::cin >> input_matrix;
		std::cout << "Inputted matrix = " << std::endl;
		std::cout << input_matrix;
		std::cout << "Calculating determinant" << std::endl;
		std::cout << "Det(input_matrix) = " << input_matrix.determinant() << std::endl;
		std::cout << std::endl;

		std::cin.ignore();  // clear stream buffer
	
		// do-while loop to check for valid input
		do {

			// ask user if they'd like to enter another number
			std::cout << "Do you want to enter another matrix? [y/n]:";
			std::getline(std::cin, anotherCalc);

			// if input not valid
			if (anotherCalc != "y" && anotherCalc != "n") {

				// output error message and clear input
				std::cerr << "Error: Please input 'y' for yes or 'n' for no." << std::endl;
			}

		} while (anotherCalc != "y" && anotherCalc != "n");

		// if user doesn't want another calculation
		if (anotherCalc == "n") { 
			std::cout << "Thank you for using determinant calculator!";
			break; 
		}

	} 

	return 0;		
}  // End of main program