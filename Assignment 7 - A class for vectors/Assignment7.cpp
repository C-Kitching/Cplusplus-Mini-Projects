//GENERAL INFO
//File Name : Assignment 7
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 10/03/20
//Date Last Edited : 10/03/20

// Description
// a class for vectors

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


// Vector class decleration
class vector
{
	// make function to overload << operator a friend of the vector class
	friend std::ostream& operator<<(std::ostream&, const vector&);

	// make function to overload >> operator a friend of the vector class
	friend vector& operator>>(std::istream&, vector&);

protected:

	int size;
	double* vector_data;

public:

	vector() : size{ 0 }, vector_data{ 0 } {}  // default constructor
	vector(int);  // parameterized constructor 1
	vector(double, double, double); // parameterized constructor 2 to make 3-vector
	vector(double, double, double, double);  // parameterized constructor 3 to make 4-vector
	vector(const vector&);  // copy constructor
	vector(vector&&) noexcept;  // move constructor
	~vector() { delete[] vector_data; vector_data = 0; size = 0; }  // destructor

	// Accesss functions
	int get_size() const { return size; }
	double& operator[](int) const; // member function to overload [] to return vector elements

	vector& operator=(const vector&);  // copy assignment operator overload
	vector& operator=(vector&&) noexcept;  // move assignment operator overload

	double dot(const vector&) const;  // member function to calculate dot product

	vector operator*(const vector&) const;  // member function to overload multiplication
	double magnitude() const; // member function to calculate magnitude
};

// vector parameterized constructor 1 implementation
vector::vector(int input_size)
{
	// check size is valid
	if (input_size <= 0) {
		std::cerr << "Error: vector must have size > 0" << std::endl;
		exit(1);
	}

	size = input_size;  // initialise vector3 size

	vector_data = new double[size];  // create 1-D array of appropriate size

	for (int i{ 0 }; i < size; i++) vector_data[i] = 0;  // fill vector3
}

// vector parameterized constructor 2 implementation
vector::vector(double x, double y, double z) : size(3), vector_data(new double[size])
{
	vector_data[0] = x; vector_data[1] = y; vector_data[2] = z;  // set values
}

// vector parameterized construct 3 implementation
vector::vector(double ct, double x, double y, double z) : size(4), vector_data(new double[size])
{
	vector_data[0] = ct; vector_data[1] = x; vector_data[2] = y; vector_data[3] = z;  // set values
}

// vector copy assignment implementation
vector& vector::operator=(const vector& vector_input)
{
	if (&vector_input == this) return *this;  // don't allow self assignment
	delete[] vector_data; vector_data = 0;  // delete 'this' info
	size = vector_input.get_size();  // copy input array data

	// if size is valid
	if (size > 0) {
		vector_data = new double[size];  // declare new array of correct size
		for (int i{ 0 }; i < size; i++) vector_data[i] = vector_input.vector_data[i];  // deep copy to new vector
	}
	return *this;
}

// vector move assignment implementation
vector& vector::operator=(vector&& vector_input) noexcept
{
	// swap object info
	std::swap(vector_data, vector_input.vector_data);
	std::swap(size, vector_input.size);

	return *this;
}

// vector copy constructor implementation
vector::vector(const vector& vector_input)
{
	vector_data = 0; size = vector_input.get_size();  // copy data of input array

	// deep copy vector data
	if (size > 0) {
		vector_data = new double[size];
		for (int i{ 0 }; i < size; i++) vector_data[i] = vector_input.vector_data[i];
	}
}

// vector move constructor implementation
vector::vector(vector&& vector_input) noexcept
{
	// steal data from input vector
	size = vector_input.get_size();
	vector_data = vector_input.vector_data;

	// reset input array
	vector_input.size = 0;
	vector_input.vector_data = nullptr;
}

// vector member function to calculate dot product
double vector::dot(const vector& vector_input) const
{
	// check if vectors are the same size
	if (size != vector_input.get_size()) {
		std::cerr << "Error: cannot calculate inner product, vectors are not the same size" << std::endl;
		exit(1);
	}

	double dot_product{ 0 };  // initialise dot product to zero

	// calculate dot product
	for (int i{ 0 }; i < size; i++) {
		dot_product += vector_data[i] * vector_input.vector_data[i];
	}

	return dot_product;
}

// vector member function to overload [] to return vector 3 element
double& vector::operator[](int element) const
{
	// check for element in range
	if (element < 1 || element > size) {
		std::cerr << "Error: vector index out of range" << std::endl;
		exit(1);
	}

	return vector_data[element - 1];
}

// vector mumber function to overload * operator
vector vector::operator*(const vector& vector_input) const
{
	// check vectors are the same size
	if (size != vector_input.get_size()) {
		std::cerr << "Error: cannot multiply, vectors not same size" << std::endl;
		exit(1);
	}

	vector temp_vector(size); // declare temp vector of appropriate size

	// multiply vectors 
	for (int i{ 0 }; i < size; i++) {
		temp_vector.vector_data[i] = vector_data[i] * vector_input.vector_data[i];
	}

	return temp_vector;
}

// vector member function to calculate magnitude
double vector::magnitude() const
{
	double sqr_magnitude{ 0 };  // initialise square of magnitude to zero

	// calculate square of magnitude
	for (int i{ 0 }; i < size; i++) {
		sqr_magnitude += vector_data[i] * vector_data[i];
	}
	// calculate magnitude and return it

	double magnitude{ pow(sqr_magnitude,0.5) };
	return magnitude;
}

// vector friend function to overload << (extraction operator)
std::ostream& operator<<(std::ostream& os, const vector& vector_input)
{
	// if vector size is not zero
	if (vector_input.get_size() != 0) {
		os << "(";
		for (int i{ 1 }; i <= vector_input.get_size(); i++) {
			if (i < vector_input.get_size()) {
				os << vector_input[i] << ",";
			}
			if (i == vector_input.get_size()) {
				os << vector_input[i] << ")" << std::endl;
			}
		}
	}
	// if vector size is zero
	else {
		os << "( )" << std::endl;
	}

	return os;
}

// vector friend function to overload >> (insertion operator)
vector& operator>>(std::istream& is, vector& vector_input)
{
	// declare input as a string
	std::string string_input;
	is >> string_input;

	// initalise two stringstreams
	std::stringstream stream_input1{ string_input };  // to determine size
	std::stringstream stream_input2{ string_input };  // to read in vector

	// decalre some variables to read into
	int element_count{ 0 }; double element{ 0 }; char vector_start{ 0 }; char breaker{ 0 };

	stream_input1 >> vector_start;  // extract the '('
	// determine size of vector
	while (!stream_input1.eof()) {
		stream_input1 >> element >> breaker;
		element_count++;
		if (breaker == ')') break;
	}

	vector temp_vector(element_count);  // declare vector of appropriate size
	element_count = 0; element = 0; vector_start = 0; breaker = 0; // reset variables

	stream_input2 >> vector_start;  // extract the '('
	// read in data from vector
	while (!stream_input2.eof()) {
		stream_input2 >> element >> breaker;
		temp_vector[element_count + 1] = element;
		element_count++;
		if (breaker == ')') break;
	}

	// move temp matrix and output it 
	vector_input = std::move(temp_vector);
	return vector_input;
}
// End vector class decleration 


// Minkowski class decleration, derived class of vector class
class Minkowski : public vector
{
	// make function to overload << operator a friend of the Minkowski class
	friend std::ostream& operator<<(std::ostream&, const Minkowski&);

	// make function to overload >> operator a friend of the Minkowski class
	friend Minkowski& operator>>(std::istream& is, Minkowski&);

public:

	Minkowski() : vector(4) {}  // default constructor
	Minkowski(double, double, double, double);  // parameterized constructor 1
	Minkowski(double, vector&);  // parameterized constructor 2
	Minkowski(const Minkowski&);  // copy constructor
	Minkowski(Minkowski&&) noexcept;  // move constructor
	~Minkowski() {};  // destructor

	// access functions
	double& operator[](int) const;  // member function to return element

	Minkowski& operator=(const Minkowski&);  // copy assignment 
	Minkowski& operator=(Minkowski&&) noexcept;  // move assignment

	double dot(const Minkowski&) const;  // overriden function to calculate dot product

	Minkowski Lorentz_boost(const vector&) const;  // member function to return boosted 4-vector

};

// Minkowski parameterized constructor 1 implementation
Minkowski::Minkowski(double ct, double x, double y, double z) : vector(4)
{
	vector_data[0] = ct; vector_data[1] = x; vector_data[2] = y; vector_data[3] = z;  // set values
}

// Minkowski parameterized constructor 2 implementation
Minkowski::Minkowski(double ct, vector& vector_input) : vector(4)
{
	// check if vector input has the correct size
	if (vector_input.get_size() != 3) {
		std::cerr << "Error: vector input does not have size 3" << std::endl;
		exit(1);
	}

	// set values of Minkowski vector
	vector_data[0] = ct;
	for (int i{ 1 }; i <= vector_input.get_size(); i++) {
		vector_data[i] = vector_input[i];
	}
}

// Minkowski copy assignment implemenation
Minkowski& Minkowski::operator=(const Minkowski& Minkowski_input)
{
	if (&Minkowski_input == this) return *this;  // don't allow self assignment

	delete[] vector_data; vector_data = 0;  // delete 'this' info
	size = Minkowski_input.get_size();  // set size

	vector_data = new double[size];  // declare new array of correct size
	for (int i{ 0 }; i < size; i++) vector_data[i] = Minkowski_input.vector_data[i];  // deep copy to new vector

	return *this;
}

// Minkowski move assignment implemenation
Minkowski& Minkowski::operator=(Minkowski&& Minkowski_input) noexcept
{
	// swap object info
	std::swap(vector_data, Minkowski_input.vector_data);
	std::swap(size, Minkowski_input.size);

	return *this;
}

// Minkowski copy constructor implemenation
Minkowski::Minkowski(const Minkowski& Minkowski_input)
{
	vector_data = 0; size = Minkowski_input.get_size();  // copy size of input Minkowski vector
	vector_data = new double[size];  // decalre new Minkowski vector of appropriate size
	for (int i{ 0 }; i < size; i++) vector_data[i] = Minkowski_input.vector_data[i];  // deep copy values
}

// Minkowski move constructioon implemenation
Minkowski::Minkowski(Minkowski&& Minkowski_input) noexcept
{
	// steal data from input vector
	size = Minkowski_input.get_size();
	vector_data = Minkowski_input.vector_data;

	// reset input array
	Minkowski_input.size = 0;
	Minkowski_input.vector_data = nullptr;
}

// Minkowski dot product implementation
double Minkowski::dot(const Minkowski& Minkowski_input) const
{
	// calculate (ct)^2-x^2-y^2-z^2
	double dot_product{ vector_data[0] * Minkowski_input.vector_data[0] };
	for (int i{ 1 }; i < Minkowski_input.size; i++) {
		dot_product -= vector_data[i] * Minkowski_input.vector_data[i];
	}
	return dot_product;
}

// Minkowski overload [] operator to return element
double& Minkowski::operator[](int element) const
{
	// if element is not in range, throw error
	if (element < 1 || element > 4) {
		std::cerr << "Error: Minkowski element out of range" << std::endl;
		exit(1);
	}

	return vector_data[element - 1];  // return element
}

// Minkowski boosted 4-vector implementation
Minkowski Minkowski::Lorentz_boost(const vector& input_velocity) const
{
	const double c{ 3e8 };  // speed of light
	vector beta(input_velocity[1] / c, input_velocity[2] / c, input_velocity[3] / c);  // beta
	vector pos(vector_data[1], vector_data[2], vector_data[3]);  // position r
	double gamma{ 1 / pow(1 - pow(beta.magnitude(),2),0.5) };  // gamma

	// decalre temp Minkowski and calculate elements
	Minkowski temp_Minkowski;
	temp_Minkowski[1] = gamma * (vector_data[0] - beta.dot(pos));
	temp_Minkowski[2] = vector_data[1] + ((gamma - 1) * ((pos.dot(beta)) / (pow(beta[1], 2))) - gamma * vector_data[0]) * beta[1];
	temp_Minkowski[3] = vector_data[2] + ((gamma - 1) * ((pos.dot(beta)) / (pow(beta[2], 2))) - gamma * vector_data[0]) * beta[2];
	temp_Minkowski[4] = vector_data[3] + ((gamma - 1) * ((pos.dot(beta)) / (pow(beta[3], 2))) - gamma * vector_data[0]) * beta[3];

	return temp_Minkowski;
}

// Minkowski friend function to overload << (insertion operator)
std::ostream& operator<<(std::ostream& os, const Minkowski& Minkowski_input)
{
	// if size non-zero
	if (Minkowski_input.get_size() != 0) {

		// format Minkowski ouput as (ct,x,y,z)
		os << "(";
		for (int i{ 1 }; i <= Minkowski_input.get_size(); i++) {
			if (i != 4) os << Minkowski_input[i] << ",";
			else os << Minkowski_input[i] << ")" << std::endl;
		}
	}
	// if vector empty
	else {
		os << "( )" << std::endl;
	}

	return os;
}

// Minkowski friend function to overload >> (extraction operator)
Minkowski& operator>>(std::istream& is, Minkowski& Minkowski_input)
{
	// declare input as a string
	std::string string_input;
	is >> string_input;

	std::stringstream stream_input{ string_input }; // initialise a string stream

	Minkowski temp_Minkowski(0, 0, 0, 0);  // declare temp Minkowski 
	int element_count{ 0 }; double element{ 0 }; char vector_start{ 0 }; char breaker{ 0 };  // set some variables for reading

	stream_input >> vector_start;  // extract the '('
	// read in data from vector
	while (!stream_input.eof()) {
		stream_input >> element >> breaker;
		temp_Minkowski[element_count + 1] = element;
		element_count++;
		if (breaker == ')') break;
	}

	// move temp matrix and output it 
	Minkowski_input = std::move(temp_Minkowski);
	return Minkowski_input;
}
// End of Minkowski class decleration


// Particle class decleration
class particle
{
	// make function to overload << operator a friend of the vector class
	friend std::ostream& operator<<(std::ostream&, const particle&);

private:

	double mass;
	vector vector_3;
	Minkowski vector_4;

public:

	particle() : mass{ 0 }, vector_3{ vector(3) }, vector_4{ Minkowski() } {};  // default constructor
	particle(double, vector&, Minkowski&);  // parameterized constructor
	~particle() {};  // destructor

	// access functions
	double& four_component(int component) const { return vector_4[component]; }  // return 4 vector component

	double gamma() const;  // member function to calculate gamma
	double energy(const double&) const;  // member function to calculate energy
	double momentum(const double&) const;  // member function to calculate momentum

};

// particle parameterized constructor implementation
particle::particle(double m, vector& input_vector_3, Minkowski& input_vector_4) : mass{ 0 }, vector_3{ vector(3) }, vector_4{ Minkowski() }
{

	// check mass is greater than zero and set it
	if (m > 0) mass = m;
	else std::cerr << "Error: mass cannot be less than 0" << std::endl;

	// if vectors of incorrect size, throw error
	if (input_vector_3.get_size() != 3 || input_vector_4.get_size() != 4) {
		std::cerr << "Error: vectors must be of size 3 and 4" << std::endl;
		exit(1);
	}
	// if vectors correct size, fill them
	else {
		for (int i{ 1 }; i <= input_vector_3.get_size(); i++) vector_3[i] = input_vector_3[i];
		for (int j{ 1 }; j <= input_vector_4.get_size(); j++) vector_4[j] = input_vector_4[j];
	}
}

// particle member function to calculate gamma
double particle::gamma() const
{
	double beta{ vector_3.magnitude() };
	double gamma{ 1 / (pow(1 - pow(beta,2),0.5)) };
	return gamma;
}

// particle member function to calculate energy
double particle::energy(const double& gamma) const
{
	double energy{ gamma * mass };
	return energy;
}

// particle member function to calculate momentum
double particle::momentum(const double& gamma) const
{
	double momentum{ gamma * mass * vector_3.magnitude() };
	return momentum;
}

// particle friend functon to overload << operator
std::ostream& operator<<(std::ostream& os, const particle& particle_input)
{
	// initalise properties
	double gamma{ particle_input.gamma() };
	double energy{ particle_input.energy(gamma) };
	double momentum{ particle_input.momentum(gamma) };
	double mass{ particle_input.mass };
	vector beta{ particle_input.vector_3 };
	Minkowski vector_4{ particle_input.vector_4 };

	// output propertirs
	os << "Particle: \nmass m = " << mass << " Mev/c^2\nbeta = " << beta << "4-vector r = " << vector_4 <<
		"gamma = " << gamma << "\ntotal energy E = " << energy
		<< " Mev\ntotal momentum p = " << momentum << " Mev/c." << std::endl;

	return os;
}
// End of particle class decleration


// Begin main program
int main() {

	// Demonstrate main vector class functionality
	std::cout << "Demonstrate main vector class functionality:" << std::endl;
	std::cout << std::endl;

	// demonstrate default constructor
	std::cout << "Demonstrate vector default constructor" << std::endl;
	std::cout << "Default construction of a1" << std::endl;
	vector a1;
	std::cout << "a1 = " << a1;
	std::cout << std::endl;

	// demonstrate parameterised constructor
	std::cout << "Demonstrate vector parameterized constructor" << std::endl;
	std::cout << "Parameterized construction of b1" << std::endl;
	vector b1(3);
	std::cout << "b1 = " << b1;
	std::cout << "Set some values for b1" << std::endl;
	b1[1] = 5; b1[2] = -6; b1[3] = -8;
	std::cout << "b1 = " << b1;
	std::cout << std::endl;

	// demonstrate access functions
	std::cout << "Demonstrate vector access functions" << std::endl;
	std::cout << "Construct c1 of size 3 and set some values" << std::endl;
	vector c1(-5, 6, 4);
	std::cout << "c1 = " << c1;
	std::cout << "Size of vector = " << c1.get_size() << std::endl;
	std::cout << "2nd element = " << c1[2] << std::endl;
	std::cout << std::endl;

	// demonstrate copy assignment
	std::cout << "Demonstrate vector copy assignment" << std::endl;
	std::cout << "Parameterized construction of c1 and set values" << std::endl;
	vector d1(1, -2, 3);
	std::cout << "d1 = " << d1;
	std::cout << "Parameterized contruction of d1" << std::endl;
	vector d2(3);
	std::cout << "d2 = " << d2;
	std::cout << "Copy c1 to d2 by assignment" << std::endl;
	d2 = d1;
	std::cout << "d2 = " << d2;
	std::cout << "Deep copy so d1 unchanged" << std::endl;
	std::cout << "d1 = " << d1;
	std::cout << std::endl;

	// demonstrate move assignment
	std::cout << "Demonstrate vector move assignment" << std::endl;
	std::cout << "Parameterized construction of e1 and set values" << std::endl;
	vector e1(-1, 4, 9);
	std::cout << "e1 = " << e1;
	std::cout << "Default construction of e2" << std::endl;
	vector e2;
	std::cout << "e2 = " << e2;
	std::cout << "Move values from e1 to e2 by assignment" << std::endl;
	e2 = std::move(e1);
	std::cout << "e2 = " << e2;
	std::cout << "e1 now empty" << std::endl;
	std::cout << "e1 = " << e1;
	std::cout << std::endl;

	// demonstrate copy construction
	std::cout << "Demonstrate vector copy construction" << std::endl;
	std::cout << "Parameterized construction of f1 and set values" << std::endl;
	vector f1(4, -3, -6);
	std::cout << "f1 = " << f1;
	std::cout << "Copy constructor to decalre f2 and deep copy f1 to f2" << std::endl;
	vector f2(f1);
	std::cout << "f2 = " << f2;
	std::cout << "Deep copy so f1 unchanged" << std::endl;
	std::cout << "f1 = " << f1;
	std::cout << std::endl;

	// demonstrate move construcion
	std::cout << "Demonstrate vector move construction" << std::endl;
	std::cout << "Parameterized construction of g1 and set values" << std::endl;
	vector g1(-8, 1, 4);
	std::cout << "g1 = " << g1;
	std::cout << "Move to constructor to construct g2 and move g1 to g2" << std::endl;
	vector g2(std::move(g1));
	std::cout << "g2 = " << g2;
	std::cout << "g1 now empty" << std::endl;
	std::cout << "g1 = " << g1;
	std::cout << std::endl;

	// demonstrate dot product
	std::cout << "Demonstrate vector dot product" << std::endl;
	std::cout << "Parameterized construction of h1 and h2, set values for both" << std::endl;
	vector h1(7, 2, -6);
	std::cout << "h1 = " << h1;
	vector h2(3);
	h2[1] = -9; h2[2] = 5; h2[3] = -1;
	std::cout << "h2 = " << h2;
	std::cout << "h1 . h2 = " << h1.dot(h2) << std::endl;
	std::cout << std::endl;

	// demonstrate vector insertion
	std::cout << "Demonstrate vector insertion" << std::endl;
	std::cout << "Insert a vector of form '(a1,a2,...)':";
	vector input_vector1;
	std::cin >> input_vector1;
	std::cout << "input vector 1 = " << input_vector1;
	std::cout << "Insert another vector of same size:";
	vector input_vector2;
	std::cin >> input_vector2;
	std::cout << "input vector 2 = " << input_vector2;
	std::cout << "Inner product = " << input_vector1.dot(input_vector2) << std::endl;
	std::cout << std::endl;


	// Demonstrate Minkowski class functionality
	std::cout << "Demonstrate derived Minkowski class functionality:" << std::endl;
	std::cout << std::endl;

	// demonstrate Minkowski default contructor
	std::cout << "Demonstrate Minkowski default constructor" << std::endl;
	Minkowski m1;
	std::cout << "m1 = " << m1;
	std::cout << std::endl;

	// demonstrate Minkowski parameterized constructor 1
	std::cout << "Demonstrate Minkowski parameterized constructor 1" << std::endl;
	Minkowski m2(1, 2, 3, 4);
	std::cout << "m2 = " << m2;
	std::cout << std::endl;

	// demonstrate Minkowski parameterized constructor 2
	std::cout << "Demonstrate Minkowski parameterized constructor 2" << std::endl;
	vector v1(2, -5, 9);
	std::cout << "v1 = " << v1;
	Minkowski m3(8, v1);
	std::cout << "m3 = " << m3;
	std::cout << std::endl;

	// demonstrate Minkowski copy assignment
	std::cout << "Demonstrate Minkowski copy assignment" << std::endl;
	std::cout << "Parameterized construction of m4 and set values" << std::endl;
	Minkowski m4(1, 2, 3, 4);
	std::cout << "m4 = " << m4;
	std::cout << "Default contruction of m5" << std::endl;
	Minkowski m5;
	std::cout << "m5 = " << m5;
	std::cout << "Copy m4 to m5 by assignment" << std::endl;
	m5 = m4;
	std::cout << "m5 = " << m5;
	std::cout << "Deep copy so m4 unchanged" << std::endl;
	std::cout << "m4 = " << m4;
	std::cout << std::endl;

	// demonstrate Minkowski move assignment
	std::cout << "Demonstrate Minkowski move assignment" << std::endl;
	std::cout << "Parameterized construction of m6 and set values" << std::endl;
	Minkowski m6(1, 2, 3, 4);
	std::cout << "m6 = " << m6;
	std::cout << "Default construction of m7" << std::endl;
	Minkowski m7;
	std::cout << "m7 = " << m7;
	std::cout << "Move values from m6 to m7 by assignment" << std::endl;
	m7 = std::move(m6);
	std::cout << "m7 = " << m7;
	std::cout << "m6 now empty" << std::endl;
	std::cout << "m6 = " << m6;
	std::cout << std::endl;

	// demonstrate Minkowski copy construction
	std::cout << "Demonstrate Minkowski copy construction" << std::endl;
	std::cout << "Parameterized construction of m8 and set values" << std::endl;
	Minkowski m8(1, 2, 3, 4);
	std::cout << "m8 = " << m8;
	std::cout << "Copy constructor to decalre m9 and deep copy m8 to m9" << std::endl;
	Minkowski m9(m8);
	std::cout << "m9 = " << m9;
	std::cout << "Deep copy so m8 unchanged" << std::endl;
	std::cout << "m8 = " << m8;
	std::cout << std::endl;

	// demonstrate Minkowski move construcion
	std::cout << "Demonstrate Minkowski move construction" << std::endl;
	std::cout << "Parameterized construction of m10 and set values" << std::endl;
	Minkowski m10(1, 2, 3, 4);
	std::cout << "m10 = " << m10;
	std::cout << "Move to constructor to construct m11 and move m10 to m11" << std::endl;
	Minkowski m11(std::move(m10));
	std::cout << "m11 = " << m11;
	std::cout << "m10 now empty" << std::endl;
	std::cout << "m10 = " << m10;
	std::cout << std::endl;

	// demonstrate Minkowski dot product
	std::cout << "Demonstrate Minkowski dot product" << std::endl;
	std::cout << "Parameterized construction of m12 and m13, set values for both" << std::endl;
	Minkowski m12(1, 2, 3, 4);
	std::cout << "m12 = " << m12;
	Minkowski m13(5, 6, 7, 8);
	std::cout << "m13 = " << m13;
	std::cout << "m12 . m13 = " << m12.dot(m13) << std::endl;
	std::cout << std::endl;

	// demonstrate Minkowski insertion
	std::cout << "Demonstrate Minkowski insertion" << std::endl;
	std::cout << "Insert a Minkowski vector of form '(ct,x,y,z)':";
	Minkowski Minkowski_input_1;
	std::cin >> Minkowski_input_1;
	std::cout << "inputted Minkowski 1 = " << Minkowski_input_1;
	std::cout << "Insert another Minkowski vector '(ct,x,y,z)':";
	Minkowski Minkowski_input_2;
	std::cin >> Minkowski_input_2;
	std::cout << "inputted Minkowski 2 = " << Minkowski_input_2;
	std::cout << "Inner product = " << Minkowski_input_1.dot(Minkowski_input_2) << std::endl;
	std::cout << std::endl;

	// Demonstrate Minkowski boosted 4-vector
	std::cout << "Demonstrate Minkowski boosted 4-vector" << std::endl;
	vector velocity(200000, 200000, 200000);
	Minkowski unboosted(10, 3, 7, 4);
	Minkowski boosted{ unboosted.Lorentz_boost(velocity) };
	std::cout << "Lorentze boost of," << "\n" << "unboosted = " << unboosted << "by velocity," << "\nv = "
		<< velocity << "is, \nboosted = " << boosted << std::endl;


	// Demonstrate particle class
	std::cout << "Demonstrate particle class" << std::endl;
	vector beta(0.1, 0.2, 0.3);
	Minkowski position(1, 2, 3, 4);
	double mass{ 938.272 };  // initiliase mass in MeV
	particle proton(mass, beta, position);  // parameterized construction of proton
	double gamma{ proton.gamma() };  // calculate gamma
	std::cout << proton;  // output properties
	std::cout << "Demonstrate 4 vector component access:" << std::endl;
	std::cout << "ct = " << proton.four_component(1) << "\nx = " << proton.four_component(2)
		<< "\ny = " << proton.four_component(3) << "\nz = " << proton.four_component(4) << std::endl;


	return 0;
}  // End of main program


