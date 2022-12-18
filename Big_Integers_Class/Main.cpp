#include"BigInt.h"
using namespace std;
int main()
{
	try
	{
		int x = 10, y = 6, z;
		BigInt a = 10, b = 6, c;
		z = x % y;
		c = a % b;
		cout << z << endl;
		cout << c << endl;
	}
	catch (const char* s)
	{
		std::cout << s;
	}
}