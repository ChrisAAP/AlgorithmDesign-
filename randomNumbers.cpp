#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int main()
{
	ofstream numbers;
	numbers.open("1000000.txt");
	for(int i = 0; i < 1000000; ++i)
	{
		numbers << rand() % 10000 << "\n";
	}
	numbers.close();
	return 0; 
}
