#include <iostream>

using namespace std;

	int main() {
		int user_input;

		cout << "Do you like VI? Enter 1 or 0" << endl;
		cin >> user_input;

		if (user_input == 1) {
			cout << "You love VI!" << endl;
		}	
		else { 
			cout << "you hate VI?" << endl;
		}
	}
