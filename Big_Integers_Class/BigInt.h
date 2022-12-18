#pragma once
#include <iostream>
#include <vector>

class BigInt
{
private:
	std::vector<int> cifre;
	bool negativ;
public:

	//This is the default constructor, which initializes a new BigInt object to 0.
	BigInt();

	//This constructor initializes a new BigInt object from a long long integer.
	BigInt(long long);

	//This constructor initializes a new BigInt object from a string.
	BigInt(const std::string&);

	//This is the copy constructor, which initializes a new BigInt object from an existing BigInt object.
	BigInt(const BigInt&);

	//This is a friend function that returns true if the given BigInt object is equal to 0.
	friend bool E0(const BigInt&);

	//This is the assignment operator, which assigns one BigInt object to another.
	BigInt& operator = (const BigInt&);

	//This is the input stream operator, which reads a BigInt object from an input stream.
	friend std::istream& operator >> (std::istream&, BigInt&);

	//This is the output stream operator, which writes a BigInt object to an output stream.
	friend std::ostream& operator << (std::ostream&, const BigInt&);

	//This is the addition operator, which adds two BigInt objects together.
	friend BigInt operator + (const BigInt&, const BigInt&);

	//This is the compound assignment operator for addition, which adds a BigInt object to another BigInt object and stores the result in the first object.
	friend BigInt operator += (BigInt&, const BigInt&);

	//This is the subtraction operator, which subtracts one BigInt object from another.
	friend BigInt operator - (const BigInt&, const BigInt&);

	//This is the compound assignment operator for subtraction, which subtracts a BigInt object from another BigInt object and stores the result in the first object.
	friend BigInt operator -= (BigInt&, const BigInt&);

	//This is the multiplication operator, which multiplies two BigInt objects together.
	friend BigInt operator * (const BigInt&, const BigInt&);

	// This is the compound assignment operator for multiplication, which multiplies a BigInt object by another BigInt object and stores the result in the first object.
	friend BigInt operator *= (BigInt&, const BigInt&);

	//This is the division operator, which divides one BigInt object by another.
	friend BigInt operator / (const BigInt&, const BigInt&);

	// This is the compound assignment operator for division, which divides a BigInt object by another BigInt object and stores the result in the first object.
	friend BigInt operator /= (BigInt&, const BigInt&);

	//This is the modulus operator, which returns the remainder
	friend BigInt operator % (const BigInt&, const BigInt&);

	// This is the compound modulus operator for division, which divides a BigInt object by another BigInt object and stores the remainder in the first object.
	friend BigInt operator %= (BigInt&, const BigInt&);

	//function overloads the prefix ++ operator for the BigInt class, and returns a reference to the modified object. 
	BigInt& operator ++ ();

	//function overloads the postfix ++ operator for the BigInt class, and returns a copy of the object before it was incremented. 
	BigInt operator ++ (int fictiv);

	//functions work similarly, but for the decrement operator --.
	BigInt& operator -- ();
	BigInt operator -- (int fictiv);

	/*
	The next four functions are comparison operators.
		The == operator is the equality operator, and the != operator
	is the inequality operator.
		The <, <=, >, and >= operators are the less than, less than
	or equal to, greater than, and greater than or equal to
	operators, respectively.
		These functions take in two BigInt objects as arguments and
	return a boolean value indicating whether the comparison is true
	or false.
	*/
	friend bool operator == (const BigInt&, const BigInt&);
	friend bool operator != (const BigInt&, const BigInt&);
	friend bool operator < (const BigInt&, const BigInt&);
	friend bool operator <= (const BigInt&, const BigInt&);
	friend bool operator > (const BigInt&, const BigInt&);
	friend bool operator >= (const BigInt&, const BigInt&);

	/*
	overloads the array subscript operator []. This allows you to
	access the elements of a BigInt object as if it were an array.
	The function takes in an integer as an argument and returns the
	element at that index in the BigInt object.
	*/
	int operator [] (const int) const;
};