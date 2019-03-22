#include "../BigNum/BigNum.h"
#include <conio.h>

using namespace std;

int main() {
	try {
		char x_c[1000], y_c[1000];
		cout << "Input number x: ";
		cin >> x_c;
		cout << "Input number y: ";
		cin >> y_c;
		const string x_s = x_c, y_s(y_c);
		BigNum x(x_s), y = y_s;

		cout << "+x = " << (+x).ToString().c_str() << endl;
		cout << "-y = " << (-y).ToString().c_str() << endl;
		cout << "x + y = " << (x + y).ToString().c_str() << endl;
		cout << "x - y = " << (x - y).ToString().c_str() << endl;
		cout << "x > y ? " << boolalpha << (x > y) << endl;
		cout << "x >= y ? " << boolalpha << (x >= y) << endl;
		cout << "x < y ? " << boolalpha << (x < y) << endl;
		cout << "x <= y ? " << boolalpha << (x <= y) << endl;
		cout << "x == y ? " << boolalpha << (x == y) << endl;
		cout << "x -= y ? " << (x -= y).ToString().c_str() << endl;
		cout << "y += x ? " << (y += x).ToString().c_str() << endl;
		cout << "x++ ? " << x++.ToString().c_str() << endl;
		cout << "++x ? " << (++x).ToString().c_str() << endl;

		cout << endl << "Press any key to exit..." << endl;
		_getche();
	}
	catch (...) {
		char msg[1000];
		strerror_s(msg, errno);
		cout << endl << "Oops! An error happens: " << msg << endl;
		cout << endl << "Press any key to exit..." << endl;
		_getche();
		return -1;
	}
}
