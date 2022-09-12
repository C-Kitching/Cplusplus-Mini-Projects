# Cplusplus Mini Projects
A series of miniature programming projects in C++ focused around object-orientated programming.  
Based on the OOP C++ course given at the University of Manchester.  
I sat this course myself in the 2019-2020 academic year.  
I have been a demonstrator for the course since the 2021-22 academic year.  

WARNING: Current students of this course are free to use these materials but should be aware that the University runs a very strict plagorism policy. Any code submitted as your own work undergoes automatic similarity checks against all other submitted work. So it is strongly advised that you do not copy these solutions directly.

## Contents

1. **Photon energy calculator**  
Given an atomic number and the initial and final photon energy levels, determine the energy of an emitted photon in J or eV using the Bohr model. 
Program will validate all user input. 
2. **Statistics from data**  
Program to compute the mean, standard deviation and standard error of the mean electron charge.  
Data is read in from a file.  
3. **University courselist interface**  
Program reads in university courses from a data file.   
User is able to input an arbitrary amount of courses to add to the data set by providing a course code (as integer) and a title (as string).   
Stringstreams are then used to create a string containing all the info which are stored in vectors.   
Inputted courses are then printed out using an iterator.  
The user can also select a year and a sort method, courses will be printed out as specified.  
4. **A class for galaxies**  
Demonstration of classes in C++.  
Classifying galaxies with classification, redshift, total mass and stellar mass fraction.  
5. **A class for complex numbers**   
A demonstration of classes applied to complex numbers.  
Class has many member functions that allow you to access the real and imaginary parts of the complex number, or calculate the modulus, arguement and complex conjugate.  
Member functions also exist to overload the +, -, \* and / operators.  
Friend functions have also been used to overload the insertion << and extraction operators for reading and writing complex numbers.  
6. **A class for matricies**  
A demonstration of classes applied to matricies.  
Matrix objects contain integers for the number of rows and columns as well as a pointer to a 1D array of doubles.  
The class contains basic access functions which allow one to get the number of rows or columns, or the index of the matrix element (m, n).  
There are member functions to overload the +, - and \* operators.  
There is a member function to overload the () operator to return the element (i, j)
Copy construction, copy assignment, move construction and move assignment have been implemented fully.  
A member function to calculate the determinant by recursively calling a function to calculate minors has been implemented.  
Friend functions to overload the << and >> operators have been written to read and write matricies from the console.  
7. **A class for vectors**  
A demonstration of classes applied to vectors.  
Vector objects contain the integer size of the vector and a pointer to a 1D array of doubles.  
Class contains member functions to access all basic information, including overloading [] to return the elements.   
There are also member function to calculate the dot product, overload * and get the magnitude.  
Copy construction, copy assignment, move construction and move assignment have been implemented fully.  
Friend functions to overload >> and << have been included for reading and writing vectors.  
A Minkowski class, to specifically handle 4-vectors of the type (ct, x, y, z), has been implemented as a derived class of vector.  
The Minkowski class contains a special member function for performing a Lorentz boost, as well as modifying the dot product to account for a different metric in Minkowski space.  
8. **A class for shapes**  
A demonstration of classes applied to shapes.  
An abstract base class for general shapes has been created, with a virtual destructor, and pure virtual functions for area and volume.  
The 2D and 3D shape classes are then derived from the shape class, also with pure virtual functions.  
The classes of square, rectangle, ellipse and circle are derived from the 2D class.  
The classes of cube, cuboid, sphere, ellipsoid and prism are derived from the 3D class.  
These classes override the area and volume functions.  
