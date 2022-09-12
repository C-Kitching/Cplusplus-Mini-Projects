//GENERAL INFO
//File Name : Assignment 5
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 25/02/20
//Date Last Edited : 14/01/22

// Description
// a class for complex numbers

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
class complex
{
	// make function to overload << operator a friend of the complex class
	friend std::ostream& operator<<(std::ostream& os, const complex& z);

	// make function to overload >> operator a friend of the complex class
	friend std::istream& operator>>(std::istream& is, complex& z);

private:

	// declare variables
	double Re;
	double Im;

public:

	// default constructor
	complex() : Re{0}, Im{0} {}

	// paramterized constructor
	complex(double real, double imag) : 
		Re{real}, Im{imag}
	{}

	// destructor
	~complex() { std::cout << "Destroying z" << std::endl; }

	// member function to return real part
	double real_part() const { return Re; }

	// member function to return imaginary part
	double imag_part() const { return Im; }

	// member function to return modulus
	double modulus() const { return sqrt(pow(Re, 2) + pow(Im, 2)); }

	// member function to return arguement
	double arguement() const { return atan2(Im, Re); }

	// member function to return complex conjugate
	complex conjugate() const { return complex(Re, -Im); }

	// member function to overload + operator (addition of two complex numbers)
	complex operator+(const complex& z) const
	{
		return complex(Re + z.Re, Im + z.Im);
	}

	// member function to overload - operator (subtraction of two complex numbers)
	complex operator-(const complex& z) const
	{
		return complex(Re - z.Re, Im - z.Im);
	}

	// member function to overload * operator (product of two complex numbers)
	complex operator*(const complex& z) const
	{
		return complex(Re * z.Re - Im * z.Im, Re * z.Im + Im * z.Re);
	}

	// member function to overload / operator (division of two complex numbers)
	complex operator/(const complex& z) const
	{
		return complex((Re * z.Re + Im * z.Im) / (pow(z.Re, 2) + pow(z.Im, 2)),
			(z.Re * Im - Re * z.Im) / (pow(z.Re, 2) + pow(z.Im, 2)));
	}

};  // End of class decleration


// Friend functions (not member functions but can access private data of 'complex' class)

// non-member function to overload ostream for complex number Z
std::ostream& operator<<(std::ostream& os, const complex& z) 
{	

	// if real part is non-zero
	if (z.Re != 0) {

		os << z.Re;  // real part
		if (z.Im < 0) os << "-" << abs(z.Im) << "i";  // if imaginary part is negative
		else if (z.Im > 0) os << "+" << z.Im << "i";  // if imaginary part is positive

	}

	// if real part is zero
	else if (z.Re == 0 && z.Im != 0) {

		if (z.Im < 0) os << "-" << abs(z.Im) << "i";  // if imaginary part is negative
		else if (z.Im > 0) os << "+" << z.Im << "i";  // if imaginary part is positive
	
	}

	else os << "0";  // if complex number is zero

	return os;

}

// non-member function to overload istream for complex number Z
std::istream& operator>>(std::istream& is, complex& z)
{
	char sign, i;  // declare characters for read in

	is >> z.Re >> sign >> z.Im >> i;  // overload input stream

	if (z.Re == -0) z.Re = 0;  // catch -0 real part input

	// if imaginary part is negative
	if (sign == '-') {

		if (z.Im != 0) z.Im = -z.Im;  // if imag part non-zero
		else z.Im = 0;  // if imag part zero

	}

	return is;

}
// End of friend funcitions


// Declare functions

// function to print out data
void complexData(const complex& z);


// Begin main program
int main() {

	std::cout.precision(3);  // set precision to 2 d.p

	// create two complex numbers
	complex a{ 3,4 };
	complex b{ 1,-2 };

	// print out complex number data
	complexData(a);
	complexData(b);

	// print sum
	std::cout << "Printing sum:" << std::endl;
	std::cout << "a + b = " << a + b << std::endl;

	// print difference
	std::cout << "Printing difference:" << std::endl;
	std::cout << "a - b = " << a - b << std::endl;

	// print product
	std::cout << "Printing product:" << std::endl;
	std::cout << "a*b = " << a*b << std::endl;

	// print quotient
	std::cout << "Printing quotient:" << std::endl;
	std::cout << "a/b = " << a/b << std::endl;

	bool multipleCalc{true};  // initialise to true for single calculation

	// while loop for multiple calculations
	while(multipleCalc) {
		
		std::string anotherCalc;  // declare string to ask user for another calculation
		complex z;  // declare a complex number for input

		// ask user to input a complex number
		std::cout << "Please enter a complex number [a+bi]:";
		std::cin >> z;

		complexData(z);  // print complex number properties

		std::cin.ignore();  // clear stream buffer

		// do-while loop to check for valid input
		do {

			// ask user if they'd like to enter another number
			std::cout << "Do you want to enter another complex number? [y/n]:";
			std::getline(std::cin, anotherCalc);

			// if input not valid
			if (anotherCalc != "y" && anotherCalc != "n") {

				// output error message and clear input
				std::cerr << "Error: Please input 'y' for yes or 'n' for no." << std::endl;

			}

		} while (anotherCalc != "y" && anotherCalc != "n");

		// if user doesn't want another calculation
		if (anotherCalc == "n") {
			
			break;  // break while loop

		}
	
	}

	return 0;

}  // end of main program


// Function definitions

// function to print out complex number data
void complexData(const complex& z) {

	// print out complex number
	std::cout << "Printing original complex number:" << std::endl;
	std::cout << "z= " << z << std::endl;

	//print real part
	std::cout << "Printing real part:" << std::endl;
	std::cout << "Re(z)= " << z.real_part()  << std::endl;

	//print imaginary part
	std::cout << "Printing real part:" << std::endl;
	std::cout << "Im(z)= " << z.imag_part() << std::endl;

	// print modulus
	std::cout << "Printing modulus:" << std::endl;
	std::cout << "|z|= " << z.modulus() <<  std::endl;

	// print arguement
	std::cout << "Printing arguement:" << std::endl;
	std::cout << "Arg(z)= " << z.arguement() << "rad" << std::endl;

	// print out complex conjugate
	std::cout << "Printing complex conjugate:" << std::endl;
	std::cout << "z*= " << z.conjugate() << std::endl;

}