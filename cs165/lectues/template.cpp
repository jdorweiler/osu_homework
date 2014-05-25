#include <iostream>
#include <string>


// void swap(int &a, int &b)
// {
// 	int tmp = a;
// 	a = b;
// 	b = tmp;

// 	return;
// }

// void swap(char &a, char &b)
// {
// 	char tmp = a;
// 	a = b;
// 	b = tmp;

// 	return;
// }

// void swap(std::set<int> &a, std::set<int> &b)
// {
// 	std::set<int> tmp = a;
// 	a = b;
// 	b = tmp;

// 	return;
// }

// void swap(double &a, double &b)
// {
// 	double tmp = a;
// 	a = b;
// 	b = tmp;

// 	return;
// }


template <typename T1, typename T2, typename T3>
T1 foo(T2 a, T3 b)
{
	//do something here
}


template <typename T>
void swap(T &a, T &b)
{
	T tmp = a;
	a = b;
	b = tmp;

	return;
}

int main(int argc, char **argv)
{
	int ia = 7;
	int ib = 8;

	std::cout << ia << " " << ib << std::endl;
	swap(ia, ib);
	std::cout << ia << " " << ib << std::endl;

	char ca = 't';
	char cb = 'e';

	std::cout << ca << " " << cb << std::endl;
	swap(ca, cb);
	std::cout << ca << " " << cb << std::endl;

	std::string sa = "thing1";
	std::string sb = "thing2";

	std::cout << sa << " " << sb << std::endl;
	swap(sa, sb);
	std::cout << sa << " " << sb << std::endl;


	double da = 3.14;
	double db = 2.71;

	std::cout << da << " " << db << std::endl;
	swap(da, db);
	std::cout << da << " " << db << std::endl;


	return 0;
}
