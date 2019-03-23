#include "../BigNum/BigNum.h"
#include <conio.h>
#include <random>
#include <ctime>

using namespace std;

void TestSimplePrint() {
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
}

void TestBin2Dec() {
	char bin[3001];
	const auto t = time(nullptr);
	default_random_engine rand(t);
	const uniform_int_distribution<int> dist(0,1);
	for (auto i = 0; i < 3000; i++)
		bin[i] = dist(rand) + '0';
	bin[3000] = '\0';
	cout << "Bin: " << bin << endl;

	BigNum dec;
	for (auto i = 0; i < 3000; i++)
		dec = bin[i] - '0' ? dec + dec : dec + dec + 1;
	cout << endl << "Dec: " << dec.ToString().c_str() << endl;
}

void Test1101001000(){
	// 数列1101001000...，判断某一位是0还是1
	int n;
	while (true) {
		cout << "Input index, 0 to exit: ";
		cin >> n;
		if (!n) return;
		const auto x = pow(1 + 8 * (n - 1), 0.5);
		cout << "The answer is " << (x - static_cast<long long>(x) == 0 ? '1' : '0') << endl;
	}
}

int main() {
	try {
		Test1101001000();

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
