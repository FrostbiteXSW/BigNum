#pragma once

#include <iostream>
#include <list>

using std::istream;
using std::ostream;
using std::string;
using std::list;

class BigNum {
	/* 大数的数值存储，顺序从低位到高位。 */
	list<unsigned int> _num;
	/* 大数的符号。 */
	char _sign = sign_pos;

	/* 不初始化list */
	explicit BigNum(bool do_not_init_list);

protected:
	/* 每一段数的基数。 */
	static constexpr int base = 1000000000;
	/* 正数符号。 */
	static constexpr char sign_pos = '+';
	/* 负数符号。 */
	static constexpr char sign_neg = '-';

public:
	/* 创建一个等于0的大数。 */
	BigNum();
	/* 将整型数转换为大数。 */
	BigNum(long long);
	/* 将字符串表示的数转换为大数。 */
	BigNum(const string&);
	/* 从现有大数创建一个相等的大数 */
	BigNum(BigNum*);
	
	~BigNum();
	
    BigNum& operator=(const BigNum&);
	friend BigNum operator+(const BigNum&);
	friend BigNum operator-(const BigNum&);
	friend BigNum operator+(BigNum, BigNum);
	friend BigNum operator-(BigNum, BigNum);
	friend bool operator>(BigNum, BigNum);
	friend bool operator>=(BigNum, BigNum);
	friend bool operator<(const BigNum&, const BigNum&);
	friend bool operator<=(const BigNum&, const BigNum&);
	friend bool operator==(BigNum, BigNum);
	friend BigNum& operator+=(BigNum&, const BigNum&);
	friend BigNum& operator-=(BigNum&, const BigNum&);
	friend BigNum operator++(BigNum&);
	friend BigNum operator++(BigNum&, int);

	/* 将此大数转换为等价的字符串表示形式。 */
	string ToString();
};