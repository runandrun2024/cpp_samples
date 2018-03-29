#include <thread>
#include <iostream>

int main()
{
	std::cout << "concurrency=" << std::thread::hardware_concurrency() << std::endl;

	return 0;
	

}
