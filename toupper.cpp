#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>

int main()
{
	std::string str{"abcdefg"};
	
	std::transform(str.begin(), str.end(), str.begin(), [](char x) { return std::toupper(x); });
	
	std::cout << str << std::endl;
		   
	return 0;
}
