#include "BigNum.h"
#include <string>
#include <sstream>
#include <iomanip>

using std::exception;
using std::stringstream;

BigNum::BigNum(bool) { }

BigNum::BigNum() {
	_num.push_back(0);
}

BigNum::BigNum(const long long num) {
	if (num < 0)
		_sign = sign_neg;
	auto abs_num = abs(num);
	while (abs_num > 0) {
		_num.push_back(abs_num % base);
		abs_num /= base;
	}
}

BigNum::BigNum(const string& string) {
	if (string.length() <= 0 || (string[0] == '+' || string[0] == '-') && string.length() <= 1)
		throw exception("Invalid number.");

	auto cpy_string(string);
	if (cpy_string[0] == '+' || cpy_string[0] == '-') {
		if (cpy_string[0] == '-')
			_sign = sign_neg;
		cpy_string = cpy_string.substr(1, cpy_string.length() - 1);
	}

	for (auto c : cpy_string)
		if (c < '0' || c > '9')
			throw exception("Invalid number.");

	const auto base_length = std::to_string(base).length() - 1;
	while (cpy_string.length() > 0) {
		auto cnt = cpy_string.length() % base_length;
		if (cnt == 0) cnt = base_length;
		auto temp = cpy_string.substr(0, cnt);
		cpy_string = cpy_string.substr(cnt);
		_num.push_front(atoi(temp.c_str()));
	}
}

BigNum::BigNum(BigNum* num) {
	_sign = num->_sign;
	for (auto value : num->_num)
		_num.push_back(value);
}

BigNum::~BigNum() {
	_num.clear();
}

BigNum& BigNum::operator=(const BigNum& num) {
	_sign = num._sign;
	_num.clear();
	for (auto value : num._num)
		_num.push_back(value);
	return *this;
}

string BigNum::ToString() {
	stringstream result;
	if (_sign == sign_neg)
		result << sign_neg;
	result << _num.back();
	const auto base_length = std::to_string(base).length() - 1;
	auto p = _num.end();
	--p;
	while (p != _num.begin()) {
		--p;
		result << std::setw(base_length) << std::setfill('0') << *p;
	}
	return result.str();
}

BigNum operator+(const BigNum& num) {
	const auto& result(num);
	return result;
}

BigNum operator-(const BigNum& num) {
	auto result(num);
	result._sign = num._sign == BigNum::sign_pos ? BigNum::sign_neg : BigNum::sign_pos;
	return result;
}

BigNum operator+(const BigNum x, const BigNum y) {
	if (x._sign == BigNum::sign_neg && y._sign == BigNum::sign_neg)
		return -(-x + -y);
	if (x._sign == BigNum::sign_neg)
		return y - -x;
	if (y._sign == BigNum::sign_neg)
		return x - -y;

	BigNum result(true);
	auto px = x._num.begin(), 
		 py = y._num.begin();
	auto up = 0;
	while (px != x._num.end() || py != y._num.end()) {
		const auto x_value = px == x._num.end() ? 0 : *px,
			       y_value = py == y._num.end() ? 0 : *py;
		result._num.push_back(x_value + y_value + up);
		if (result._num.back() >= BigNum::base) {
			result._num.back() %= BigNum::base;
			up = 1;
		}
		else
			up = 0;
		if (px != x._num.end()) ++px;
		if (py != y._num.end()) ++py;
	}
	if (up)
		result._num.push_back(1);
	return result;
}

BigNum operator-(const BigNum x, const BigNum y) {
	if (x._sign == BigNum::sign_neg && y._sign == BigNum::sign_neg)
		return -y - -x;
	if (x._sign == BigNum::sign_neg)
		return -(-x + y);
	if (y._sign == BigNum::sign_neg)
		return x + -y;
	
	BigNum result(true);
	auto px = x._num.begin(), 
		 py = y._num.begin();
	auto up = 0;
	while (px != x._num.end() || py != y._num.end()) {
		const auto x_value = px == x._num.end() ? 0 : *px,
			       y_value = py == y._num.end() ? 0 : *py;
		if (x_value < y_value + up) {
			result._num.push_back(x_value + BigNum::base - y_value - up);
			up = 1;
		}
		else {
			result._num.push_back(x_value - y_value - up);
			up = 0;
		}
		if (px != x._num.end()) ++px;
		if (py != y._num.end()) ++py;
	}
	if (up) {
		result._sign = BigNum::sign_neg;
		result._num.back() = BigNum::base - result._num.back();
	}
	while (result._num.back() == 0 && result._num.size() > 1)
		result._num.pop_back();
	return result;
}

bool operator>(BigNum x, BigNum y) {
	if (x._sign == BigNum::sign_neg && y._sign == BigNum::sign_pos)
		return false;
	if (x._sign == BigNum::sign_pos && y._sign == BigNum::sign_neg)
		return true;

	if (x._num.size() > y._num.size())
		return x._sign == BigNum::sign_pos;
	if (x._num.size() < y._num.size())
		return x._sign != BigNum::sign_pos;

	auto px = x._num.end(), 
		 py = y._num.end();
	while (px != x._num.begin()) {
		--px;
		--py;
		const auto x_value = *px,
			       y_value = *py;
		if (x_value > y_value)
			return x._sign == BigNum::sign_pos;
		if (x_value < y_value)
			return x._sign != BigNum::sign_pos;
	}

	return false;
}

bool operator>=(BigNum x, BigNum y) {
	if (x._sign == BigNum::sign_neg && y._sign == BigNum::sign_pos)
		return false;
	if (x._sign == BigNum::sign_pos && y._sign == BigNum::sign_neg)
		return true;

	if (x._num.size() > y._num.size())
		return x._sign == BigNum::sign_pos;
	if (x._num.size() < y._num.size())
		return x._sign != BigNum::sign_pos;

	auto px = x._num.end(), 
		 py = y._num.end();
	while (px != x._num.begin()) {
		--px;
		--py;
		const auto x_value = *px,
			       y_value = *py;
		if (x_value > y_value)
			return x._sign == BigNum::sign_pos;
		if (x_value < y_value)
			return x._sign != BigNum::sign_pos;
	}

	return true;
}

bool operator<(const BigNum& x, const BigNum& y) {
	return !(x >= y);
}

bool operator<=(const BigNum& x, const BigNum& y) {
	return !(x > y);
}

bool operator==(BigNum x, BigNum y) {
	if (x._sign != y._sign)
		return false;
	if (x._num.size() != y._num.size())
		return false;

	auto px = x._num.end(), 
		 py = y._num.end();
	while (px != x._num.begin()) {
		--px;
		--py;
		const auto x_value = *px,
			       y_value = *py;
		if (x_value != y_value)
			return false;
	}

	return true;
}

BigNum& operator+=(BigNum& x, const BigNum& y) {
	x = x + y;
	return x;
}

BigNum & operator-=(BigNum& x, const BigNum& y) {
	x = x - y;
	return x;
}

BigNum operator++(BigNum& num) {
	num += 1;
	return num;
}

BigNum operator++(BigNum& num, int) {
	auto result(num);
	num += 1;
	return result;
}
