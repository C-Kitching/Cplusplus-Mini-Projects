//GENERAL INFO
//File Name : Assignment 8
//Author : Christopher Kitching
//E - Mail: christopher.kitching@student.manchester.ac.uk
//Date Created : 16/03/20
//Date Last Edited : 16/03/20

// Description
// classes for shapes

// Definitions
#define _USE_MATH_DEFINES

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
#include <math.h>

// Abstract base class for shapes
class shape
{
public:
	virtual ~shape() {};  // virtual destructor
	virtual double area() = 0;  // pure virtual function for area
	virtual double volume() = 0;  // pure virtual function for volume
};


// Abstract derived class of shape for 2D shapes
class Dim2 : public shape
{
public:
	virtual ~Dim2() {};
	virtual double area() = 0;
	virtual double volume() { return 0; }  // 2D shapes have zero volume
};

// Abstract derived class of 1shape for 3D shapes
class Dim3 : public shape
{
public:
	virtual ~Dim3() {};
	virtual double area() = 0;
	virtual double volume() = 0;
};


// Derived class of 2D shapes for rectangle
class rectangle : public Dim2
{
private:
	double side_a, side_b;
public:
	rectangle() : side_a{ 0 }, side_b{ 0 } {};
	rectangle(double a, double b) : side_a{ a }, side_b{ b } {
		// check dimensions of shape valid
		if (a <= 0 || b <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~rectangle() {};

	double area() { return side_a * side_b; }
};

// Derived class of 2D shapes for square
class square : public Dim2
{
private:
	double side;
public:
	square() : side{ 0 } {};
	square(double a) : side{ a } {
		// check dimensions of shape valid
		if (a <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~square() {};

	double area() { return pow(side, 2); }
};

// Derived class of 2D shapes for ellipse
class ellipse : public Dim2
{
private:
	double semi_minor;
	double semi_major;
public:
	ellipse() : semi_minor{ 0 }, semi_major{ 0 } {};
	ellipse(double a, double b) : semi_minor{ a }, semi_major{ b } {
		// check dimensions of shape valid
		if (a <= 0 || b <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~ellipse() {};

	double area() { return M_PI * semi_minor * semi_major; }
};

// Derived class of 2D shapes for circle
class circle : public Dim2
{
private:
	double radius;
public:
	circle() : radius{ 0 } {};
	circle(double r) : radius{ r } {
		// check dimensions of shape valid
		if (r <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~circle() {};

	double area() { return M_PI * pow(radius, 2); }
};


// Derived class of 3D shapes for cuboid
class cuboid : public Dim3
{
private:
	double height, width, length;
public:
	cuboid() : height{ 0 }, width{ 0 }, length{ 0 } {};
	cuboid(double h, double w, double l) : height{ h }, width{ w }, length{ l } {
		// check dimensions of shape valid
		if (h <= 0 || w <= 0 || l <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~cuboid() {};

	double volume() { return height * width * length; }
	double area() { return 2 * height * width + 2 * height * length + 2 * width * length; }
};

// Derived class of 3D shapes for cube
class cube : public Dim3
{
private:
	double side;
public:
	cube() : side{ 0 } {};
	cube(double a) : side{ a } {
		// check dimensions of shape valid
		if (a <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~cube() {};

	double volume() { return pow(side, 3); }
	double area() { return 6 * pow(side, 2); }
};

// Derived class of 3D shapes for ellipsoid
class ellipsoid : public Dim3
{
private:
	double height, width, length;
	const double p{ 1.6075 };  // constant for approximate area formula
public:
	ellipsoid() : height{ 0 }, width{ 0 }, length{ 0 } {};
	ellipsoid(double h, double w, double l) : height{ h }, width{ w }, length{ l } {
		// check dimensions of shape valid
		if (h <= 0 || w <= 0 || l <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~ellipsoid() {};

	double volume() { return (4.0 / 3.0) * M_PI * height * width * length; }
	double area() { return 4.0 * M_PI * pow((pow(height * width, p) + pow(height * length, p) + pow(width * length, p)) / 3, 1 / p); }  // approximate area formula
};

// Derived class of 3D shapes for sphere
class sphere : public Dim3
{
private:
	double radius;
public:
	sphere() : radius{ 0 } {};
	sphere(double r) : radius{ r } {
		// check dimensions of shape valid
		if (r <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~sphere() {};

	double volume() { return (4.0 / 3.0) * M_PI * pow(radius, 3); }
	double area() { return 4.0 * M_PI * pow(radius, 2); }
};


// Derived class of shape for prism
class prism : public Dim3
{
private:
	double depth;
	shape* shape_ptr;
public:
	prism() : depth{ 0 }, shape_ptr{ 0 } {};
	prism(double d, shape* shape) : depth{ d }, shape_ptr{ shape } {
		// check dimensions of shape valid
		if (d <= 0) {
			std::cerr << "Error: cannot decalre shape with zero dimension(s)" << std::endl;
			exit(1);
		}
	};
	~prism() {};

	double volume() { return depth * (shape_ptr->area()); }
	double area() { return 0; }
};


// Begin main program
int main() {

	// creata a vector of pointers to various shapes
	std::vector<shape*> shape_vector;
	shape_vector.push_back(new rectangle(2, 3));
	shape_vector.push_back(new square(2));
	shape_vector.push_back(new ellipse(1, 2));
	shape_vector.push_back(new circle(2));
	shape_vector.push_back(new cuboid(2, 3, 4));
	shape_vector.push_back(new cube(2));
	shape_vector.push_back(new ellipsoid(2, 3, 4));
	shape_vector.push_back(new sphere(2));
	shape_vector.push_back(new prism(4, shape_vector[0]));

	// print out the data
	std::cout << "Shapes are specified with relevant dimensions in (), i.e rectangle(side a, side b) or circle(radius) etc." << std::endl;
	std::cout << "Rectangle(2,3) has area A = " << shape_vector[0]->area()
		<< " and volume V = " << shape_vector[0]->volume()
		<< std::endl;
	std::cout << "Square(2) has area A = " << shape_vector[1]->area()
		<< " and volume V = " << shape_vector[1]->volume()
		<< std::endl;
	std::cout << "Ellipse(1,2) has area A = " << shape_vector[2]->area()
		<< " and volume V = " << shape_vector[2]->volume()
		<< std::endl;
	std::cout << "Circle(2) has area A = " << shape_vector[3]->area()
		<< " and volume V = " << shape_vector[3]->volume()
		<< std::endl;
	std::cout << "Cuboid(2,3,4) has area A = " << shape_vector[4]->area()
		<< " and volume V = " << shape_vector[4]->volume()
		<< std::endl;
	std::cout << "Cube(2) has area A = " << shape_vector[5]->area()
		<< " and volume V = " << shape_vector[5]->volume()
		<< std::endl;
	std::cout << "Ellipsoid(2,3,4) has area A = " << shape_vector[6]->area()
		<< " and volume V = " << shape_vector[6]->volume()
		<< std::endl;
	std::cout << "Sphere(2) has area A = " << shape_vector[7]->area()
		<< " and volume V = " << shape_vector[7]->volume()
		<< std::endl;
	std::cout << "Prism(4, rectangle(2,3)) has volume V = " << shape_vector[8]->volume()
		<< std::endl;
	std::cout << std::endl;

	// delete shape_vector data
	std::cout << "shape_vector has initial size " << shape_vector.size() << "\nDeleting..." << std::endl;
	for (auto shape_vectorit = shape_vector.begin();
		shape_vectorit < shape_vector.end();
		++shape_vectorit) delete* shape_vectorit;
	shape_vector.clear();
	std::cout << "shape_vector has final size " << shape_vector.size() << std::endl;

	return 0;
}  // End main program