#include"BigInt.h"
#include <vector>
#include <string>
#include<iostream>
using namespace std;

BigInt::BigInt()
{
	//Default constructor
	cifre = std::vector<int>();
	negativ = false;
}

BigInt::BigInt(long long n)
{
	/*
	The integer constructor initializes the digits_ vector
	by repeatedly adding the last digit of n to the vector
	and then dividing n by 10.
	*/
	int m;
	string  str;
	negativ = false;
	m = n;
	if (m < 0)
	{
		negativ = true;
		str = to_string(m);
		str.erase(str.begin());
		m = stoi(str);
	}

	if (m == 0)
	{
		cifre.push_back(0);
		return;
	}
	if (m > 0)
	{
		while (m > 0)
		{
			cifre.push_back(m % 10);
			m /= 10;
		}
	}
}

BigInt::BigInt(const std::string& str)
{
	/*
	The string constructor initializes the digits_ vector
	by iterating through the characters of the string
	in reverse order and converting each character to an integer
	*/
	if (str.front() == '-')
	{
		int m;
		string s_str = str;
		negativ = true;
		s_str.erase(s_str.begin());
		m = stoi(s_str);
		while (m > 0)
		{
			cifre.push_back(m % 10);
			m /= 10;
		}
	}
	else
	{
		for (int i = str.size() - 1; i >= 0; i--)
		{
			if (isdigit(str[i]))
			{
				cifre.push_back(str[i] - '0');
			}
			else
			{
				throw("The string of cifre contains unaccepted characters");
			}
		}
		negativ = false;
	}
}
BigInt::BigInt(const BigInt& ob)
{
	//copy constructor
	cifre = ob.cifre;
	negativ = ob.negativ;

}


bool E0(const BigInt& ob)
{
	//checking if a given object has only one digit and that digit is 0.
	return ob.cifre.size() == 1 && ob.cifre[0] == 0;
}

BigInt& BigInt::operator=(const BigInt& ob)
{
	/*
	The assignment operator allows you to assign one BigInt object
	to another using the = operator.
	*/
	if (this != &ob)
	{
		int sz = 1;
		for (int i = 0; i < ob.cifre.size(); i++)
		{
			cifre.resize(sz++);
			cifre[i] = ob.cifre[i];
		}

	}
	negativ = ob.negativ;
	return *this;
}

std::istream& operator>>(std::istream& in, BigInt& ob)
{
	/*
	The input stream operator allows you to read a BigInt object
	from an input stream (such as std::cin) using the >> operator.
	*/
	std::string str;
	in >> str;
	ob.cifre.clear();
	for (int i = str.size() - 1; i >= 0; i--) {
		if (isdigit(str[i]))
		{
			ob.cifre.push_back(str[i] - '0');
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const BigInt& ob)
{
	/*
	The output stream operator allows you to print a BigInt
	object to an output stream (such as std::cout) using
	the << operator.
	*/

	if (ob.negativ)
		out << '-';
	for (int i = ob.cifre.size() - 1; i >= 0; i--)
	{

		out << ob.cifre[i];
	}
	return out;
}
BigInt operator+(const BigInt& ob1, const BigInt& ob2)
{
	/*
	Implementation of the operator+ function for a BigInt class,
	which allows you to add two big integers together.
	The function takes in two BigInt objects as arguments
	and returns a BigInt object as the result of the addition.
	*/
	BigInt result;
	int transport = 0;
	if (ob1.negativ == false && ob2.negativ == false)
		for (int i = 0; i < ob1.cifre.size() || i < ob2.cifre.size() || transport > 0; i++)
		{
			if (i < ob1.cifre.size())
				transport += ob1.cifre[i];
			if (i < ob2.cifre.size())
				transport += ob2.cifre[i];
			result.cifre.push_back(transport % 10);
			transport /= 10;
		}
	if (ob1.negativ == true && ob2.negativ == true)
		for (int i = 0; i < ob1.cifre.size() || i < ob2.cifre.size() || transport > 0; i++)
		{
			if (i < ob1.cifre.size())
				transport += ob1.cifre[i];
			if (i < ob2.cifre.size())
				transport += ob2.cifre[i];
			result.cifre.push_back(transport % 10);
			transport /= 10;
			result.negativ = true;
		}
	//
	if (ob1.negativ == false && ob2.negativ == true)
	{
		BigInt  a, b;
		a = ob1;
		b = ob2;
		int borrow = 0;
		for (size_t i = 0; i < a.cifre.size(); i++)
		{
			int diff = a.cifre[i] - borrow;
			if (i < b.cifre.size())
			{
				diff -= b.cifre[i];
			}
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}
			result.cifre.push_back(diff);
		}
		// remove leading zeros
		while (result.cifre.size() > 1 && result.cifre.back() == 0)
		{
			result.cifre.pop_back();
		}
		if (ob1 > ob2)
			result.negativ = false;
		if (ob2 > ob1)
		{
			a = ob2;
			b = ob1;
			result = a + b;
			result.negativ = true;
		}
	}
	if (ob1.negativ == true && ob2.negativ == false)
	{
		BigInt  a, b;
		a = ob1;
		b = ob2;
		int borrow = 0;
		for (size_t i = 0; i < a.cifre.size(); i++)
		{
			int diff = a.cifre[i] - borrow;
			if (i < b.cifre.size())
			{
				diff -= b.cifre[i];
			}
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}
			result.cifre.push_back(diff);
		}
		// remove leading zeros
		while (result.cifre.size() > 1 && result.cifre.back() == 0)
		{
			result.cifre.pop_back();
		}
		if (ob1 > ob2)
			result.negativ = true;
		if (ob2 > ob1)
		{
			a = ob2;
			b = ob1;
			result = a + b;
			result.negativ = false;
		}
	}
	return result;
}

BigInt operator+=(BigInt& ob1, const BigInt& ob2)
{
	/*
	The function takes in two arguments: a reference to
	a BigInt object called ob1 and a constant reference to
	a BigInt object called ob2.
	The function returns a reference to the modified ob1 object.
	The function simply calls the operator+ function using
	ob1 and ob2 as arguments and assigns the result to ob1.
	It then returns a reference to ob1.
	*/
	ob1 = ob1 + ob2;
	return ob1;
}

BigInt operator-(const BigInt& ob1, const BigInt& ob2)
{
	/*
	The function first initializes two BigInt objects called
	a and b, and a BigInt object called result which will store
	the result of the subtraction. It then checks the signs of
	the two input BigInt objects. If both objects are positive
	or both objects are negative, it performs the subtraction
	and sets the negativ attribute of the result object appropriately
	based on the comparison of the two input objects.
	If one object is positive and the other is negative, it performs
	addition instead of subtraction by setting the negativ attribute
	of both input objects to false and calling the operator+ function.
	The function then removes any leading zeros from the result
	object and returns it.
	*/
	BigInt result, a, b;
	if (ob1.negativ == false && ob2.negativ == false)
	{
		if (ob1 < ob2)
		{
			result.negativ = true;
		}
		else
			result.negativ = false;

		if (result.negativ)
		{
			a = ob2;
			b = ob1;
		}
		else
		{
			a = ob1;
			b = ob2;
		}

		int borrow = 0;
		for (size_t i = 0; i < a.cifre.size(); i++) {
			int diff = a.cifre[i] - borrow;
			if (i < b.cifre.size())
			{
				diff -= b.cifre[i];
			}
			if (diff < 0) {
				diff += 10;
				borrow = 1;
			}
			else {
				borrow = 0;
			}
			result.cifre.push_back(diff);
		}
		// remove leading zeros
		while (result.cifre.size() > 1 && result.cifre.back() == 0)
		{
			result.cifre.pop_back();
		}
	}
	else if (ob1.negativ == true && ob2.negativ == false)
	{
		a = ob1;
		b = ob2;
		a.negativ = false;
		b.negativ = false;
		result = a + b;
		result.negativ = true;
	}
	else if (ob1.negativ == false && ob2.negativ == true)
	{
		a = ob1;
		b = ob2;
		a.negativ = false;
		b.negativ = false;
		result = a + b;
		result.negativ = false;

	}
	else if (ob1.negativ == true && ob2.negativ == true)
	{
		if (ob2 < ob1)
		{
			a = ob1;
			b = ob2;
			a.negativ = false;
			b.negativ = false;
			result = a - b;
			result.negativ = true;
		}
		if (ob1 <= ob2)
		{
			a = ob1;
			b = ob2;
			a.negativ = false;
			b.negativ = false;
			result = a - b;
			result.negativ = false;
		}
	}
	return result;
}

BigInt operator-=(BigInt& ob1, const BigInt& ob2)
{
	/*
	The function takes in two arguments: a reference to a BigInt
	object called ob1 and a constant reference to a BigInt object
	called ob2.
	The function returns a reference to the modified ob1 object.
	The function simply calls the operator- function using ob1 and ob2
	as arguments and assigns the result to ob1. It then returns
	a reference to ob1.
	*/
	ob1 = ob1 - ob2;
	return ob1;
}

BigInt operator*(const BigInt& ob1, const BigInt& ob2)
{
	/*The function first checks if either of the input BigInt
	objects is equal to zero, and if so, it returns that object.
	This is done using a helper function E0, which checks if a BigInt
	object is equal to zero.
	If neither input BigInt object is zero, the function performs
	the multiplication using the standard multiplication algorithm.
	It does this by iterating over the digits of the first input
	BigInt object and multiplying each digit by every digit of the
	second input BigInt object. It then stores the intermediate
	results in a current BigInt object and adds them to the result
	BigInt object.
	After the multiplication is complete, the function sets the
	negativ attribute of the result object appropriately based on the
	signs of the input BigInt objects.
	Finally, it removes any leading zeros from the result object
	and returns it.
	*/
	if (E0(ob1))
	{
		return ob1;
	}
	if (E0(ob2))
	{
		return ob2;
	}
	BigInt result;
	for (int i = 0; i < ob1.cifre.size(); i++)
	{
		int carry = 0;
		BigInt current(0);
		for (int j = 0; j < ob2.cifre.size(); j++)
		{
			int product = ob1.cifre[i] * ob2.cifre[j] + carry;
			current.cifre.push_back(product % 10);
			carry = product / 10;
		}
		if (carry > 0)
		{
			current.cifre.push_back(carry);
		}
		for (int j = 0; j < i; j++)
		{
			current.cifre.insert(current.cifre.begin(), 0);
		}
		result = result + current;
	}
	if (ob1.negativ && ob2.negativ)
	{
		result.negativ = false;
	}
	else if (ob1.negativ || ob2.negativ)
	{
		result.negativ = true;
	}
	result.cifre.erase(result.cifre.begin());
	return result;
}
BigInt operator*=(BigInt& ob1, const BigInt& ob2)
{
	/*
	The function takes in two arguments: a reference to a BigInt
	object called ob1 and a constant reference to a BigInt
	object called ob2. The function returns a reference to the
	modified ob1 object.
	The function simply calls the operator* function using ob1 and ob2
	as arguments and assigns the result to ob1. It then returns
	a reference to ob1.
	*/
	ob1 = ob1 * ob2;
	return ob1;
}

BigInt operator/(const BigInt& ob1, const BigInt& ob2)
{
	/*
		The function first checks if the divisor is equal to zero,
	and if it is, it throws an exception.
		Next, it checks if the divisor is larger than the dividend.
	If it is, the function returns zero, as the result of the
	division will be zero.
		The function then sets the negativ field of the result BigInt
	to the opposite of the negativ fields of the two operands,
	indicating that the result will be negative if the operands
	have opposite signs, and positive if they have the same sign.
		The function then initializes a BigInt called remainder to the
	value of the dividend. It sets the negativ field of remainder
	to false, as we are interested in the absolute value of the
	remainder.
		The function then enters a loop, in which it repeatedly shifts
	the remainder left by one digit and subtracts the divisor from it,
	until the remainder becomes smaller than the divisor. The number
	of times the divisor is subtracted from the remainder is stored
	in a counter. The result of the division is the sum of all the
	counter values obtained in each iteration of the loop.
		Finally, the function removes any leading zeros from the result
	and returns it.
	*/
	BigInt result;
	if (ob2 == 0)
	{
		throw("Division by zero is not allowed");
	}
	if (ob2 > ob1)
	{
		result = 0;
		return result;
	}
	result.negativ = (ob1.negativ != ob2.negativ);
	BigInt divident;
	BigInt _ob1 = ob1;
	divident.cifre.push_back(_ob1.cifre.back());
	BigInt divisor = ob2;
	int k = _ob1.cifre.size() - 1;
	while (1)
	{
		bool flag_point = false;
		BigInt cat = 0;
		BigInt produs = 0;
		do
		{
			while (divident <= divisor)
			{
				if (k)
				{
					k--;
					divident.cifre.insert(divident.cifre.begin(), _ob1.cifre[k]);
				}
			}
			produs += divisor;
			if (produs > divident)
				break;
			cat++;
			if (divident.cifre[divident.cifre.back()] == 0)
				cat--;

		} while (1);
		if (divident > divisor)
		{
			BigInt prod = cat * divisor;
			divident = divident - prod;
		}

		for (int i = cat.cifre.size() - 1; i >= 0; i--)
		{
			result.cifre.insert(result.cifre.begin(), cat.cifre[i]);
		}

		if (!k)
			break;
	}
	return result;
}
BigInt operator/=(BigInt& ob1, const BigInt& ob2)
{
	/*
	The function calls the division operator (/) for BigInts
	to perform the division and assign the result to the left-hand
	operand using the assignment operator (=).
	Finally, it returns the left-hand operand, which now holds
	the result of the division.
	*/
	ob1 = ob1 / ob2;
	return ob1;
}
BigInt operator%(const BigInt& ob1, const BigInt& ob2)
{
	/*
		The function first checks if the divisor is equal to zero,
	and if it is, it throws an exception indicating that division
	by zero is not allowed.
		Next, it checks if the dividend is smaller than the divisor.
	If it is, the function returns the dividend, as the remainder
	of the division will be the dividend itself.
		The function then initializes a BigInt called t to zero and
	enters a loop, in which it repeatedly shifts t left by one digit
	and adds the corresponding digit from the dividend, until
	t becomes larger than or equal to the divisor.
		After the loop, the function enters another loop, in which it
	repeatedly shifts t left by one digit and subtracts the divisor
	from it, until t becomes smaller than the divisor.
	The result of the modulo operation is the final value of t.
		Finally, the function sets the negativ field of the result
	to true if the dividend is negative,
	and to false otherwise.
		It then returns the result.
	*/
	BigInt result;
	if (ob2 == 0)
	{
		throw("Division by zero is not allowed");
	}
	if (ob2 > ob1)
	{
		result = 0;
		return result;
	}
	BigInt _ob1 = ob1;

	result.negativ = (ob1.negativ != ob2.negativ);
	BigInt divident;
	divident.cifre.push_back(_ob1.cifre.back());
	BigInt divisor = ob2;
	int k = _ob1.cifre.size() - 1;
	while (1)
	{
		BigInt cat = 0;
		BigInt produs = divisor;
		do
		{
			while (divident <= divisor)
			{
				k--;
				divident.cifre.insert(divident.cifre.begin(), _ob1.cifre[k]);
			}
			produs += divisor;
			cat++;
			if (divident.cifre[divident.cifre.back()] == 0)
				cat--;
		} while (produs <= divident);
		BigInt prod = cat * divisor;
		divident = divident - prod;
		if (divident == 0)
			break;
		if (!k)
			break;
	}
	result = divident;
	return result;
}
BigInt operator%=(BigInt& ob1, const BigInt& ob2)
{
	/*
	The function calls the modulo operator (%) for BigInts to perform
	the modulo operation and assigns the result to the left-hand
	operand using the assignment operator (=).
	Finally, it returns the left-hand operand, which now holds the
	result of the modulo operation.
	*/
	ob1 = ob1 % ob2;
	return ob1;
}
BigInt& BigInt::operator++()
{
	/*
	The function adds one to the BigInt using the addition operator
	(+) and the assignment operator (=). The value of the BigInt is
	updated in place and a reference to it is returned.
	This operator allows you to use the ++ operator to increment
	a BigInt by one
	*/
	*this = *this + 1;
	return *this;
}
BigInt BigInt::operator++(int fictiv)
{
	/*
	The function takes an additional dummy argument, fictiv, which is
	not used in the function body. This argument is included to
	distinguish the post-increment operator from the pre-increment
	operator, which does not take any arguments.
	The function first stores the current value of the BigInt in a
	temporary BigInt called temp. It then increments the BigInt using
	the pre-increment operator (++) and returns the value stored in
	temp, which is the original (unincremented) value.
	*/
	BigInt temp;
	temp = *this;
	++(*this);
	return temp;
}
BigInt& BigInt::operator--()
{
	/*
	Overloading of the pre-decrement operator (--) for BigInt objects.
	It decrements a BigInt by one and returns a reference to the
	decremented BigInt.
	The function subtracts one from the BigInt using the subtraction
	operator (-) and the assignment operator (=). The value of the
	BigInt is updated in place and a reference to it is returned.
	*/
	*this = *this - 1;
	return *this;
}
BigInt BigInt::operator--(int fictiv)
{
	/*
	 It is a postfix version of the decrement operator, which means
	 that it takes an integer argument fictiv (which is not used in
	 the function) and returns a copy of the BigInt object before it
	 was decremented.
	 The function first creates a temporary BigInt object called temp
	 and assigns the current object to it using the assignment
	 operator =. Then, it decrements the current object using the
	 prefix version of the decrement operator (--(*this)).
	 Finally, it returns the temp object, which is a copy of the
	 original object before it was decremented.
	*/
	BigInt temp;
	temp = *this;
	--(*this);
	return temp;
}

bool operator==(const BigInt& ob1, const BigInt& ob2)
{
	/*
	The function compares the sizes of the cifre (digits) vectors
	of the two objects. If they are not equal, the function returns
	false immediately. Otherwise, it compares the digits of the
	two objects element by element, starting from the least
	significant digit. If all digits are equal, the function returns
	true, otherwise it returns false.
	*/
	int i;
	if (ob1.cifre.size() != ob2.cifre.size())
		return false;
	for (i = 0; i < ob1.cifre.size() && ob1.cifre[i] == ob2.cifre[i]; i++);
	return i == ob1.cifre.size();
}

bool operator!=(const BigInt& ob1, const BigInt& ob2)
{
	/*
	The function returns the logical negation of the result of the
	equality operator (==) applied to the two objects. This means
	that if the two objects are equal, the function will return false,
	and if they are not equal, the function will return true.
	*/
	return !(ob1 == ob2);
}

bool operator<(const BigInt& ob1, const BigInt& ob2)
{
	/*
	The function compares the sizes of the cifre (digits) vectors of
	the two objects. If the size of the first object's vector is less
	than the size of the second object's vector, the function returns
	true immediately.
	If the size of the first object's vector is greater than the size
	of the second object's vector, the function returns false
	immediately.
	If the sizes are equal, the function compares the digits of
	the two objects element by element, starting from the most
	significant digit. If all digits are equal, the function returns
	false, otherwise it returns true if the first object's digit is
	less than the second object's digit, and false otherwise.
	*/
	int i = 0;
	if (ob1.cifre.size() < ob2.cifre.size())
		return true;
	if (ob1.cifre.size() > ob2.cifre.size())
		return false;
	for (i = ob1.cifre.size() - 1; i >= 0 && ob1.cifre[i] == ob2.cifre[i]; i--);
	if (i == -1)
		return false;
	if (ob1.cifre[i] < ob2.cifre[i])
		return true;
	return false;

}
bool operator>(const BigInt& ob1, const BigInt& ob2)
{
	/*
	function takes two constant references to BigInt objects,
	ob1 and ob2, as arguments and returns a bool value indicating
	whether the first object is greater than the second object.
	It does this by returning the result of the < operator applied
	to the second object and the first object.
	*/
	return ob2 < ob1;
}
bool operator<=(const BigInt& ob1, const BigInt& ob2)
{
	/*
	 function takes two constant references to BigInt objects,
	 ob1 and ob2, as arguments and returns a bool value indicating
	 whether the first object is less than or equal to the second
	 object.
	 It does this by returning the logical negation of the result
	 of the > operator applied to the two objects.
	*/
	return !(ob1 > ob2);
}

bool operator>=(const BigInt& ob1, const BigInt& ob2)
{
	/*
	 function takes two constant references to BigInt objects,
	 ob1 and ob2, as arguments and returns a bool value indicating
	 whether the first object is greater than or equal to the second
	 object. It does this by returning the logical negation of the
	 result of the < operator applied to the two objects.
	*/
	return !(ob1 < ob2);
}
int BigInt::operator[](const int poz) const
{
	/*
	This is a function that overloads the square bracket operator ([])
	for the BigInt class. It takes an int value poz as an argument
	and returns the digit at the specified position in the
	cifre (digits) vector of the BigInt object. The function is
	marked as const, which means that it promises not to modify the
	object on which it is called.
	The function first checks if the value of poz is negative.
	If it is, the function throws an exception with the message
	"Range Error". Otherwise, it returns the element at the specified
	position in the cifre vector.
	*/
	if (poz < 0)
		throw("Range Error");
	return cifre[poz];
}
