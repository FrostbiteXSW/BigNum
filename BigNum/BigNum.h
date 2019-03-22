#pragma once

#include <iostream>
#include <list>

using std::istream;
using std::ostream;
using std::string;
using std::list;

class BigNum {
	/* ��������ֵ�洢��˳��ӵ�λ����λ�� */
	list<unsigned int> _num;
	/* �����ķ��š� */
	char _sign = sign_pos;

	/* ����ʼ��list */
	explicit BigNum(bool do_not_init_list);

protected:
	/* ÿһ�����Ļ����� */
	static constexpr int base = 1000000000;
	/* �������š� */
	static constexpr char sign_pos = '+';
	/* �������š� */
	static constexpr char sign_neg = '-';

public:
	/* ����һ������0�Ĵ����� */
	BigNum();
	/* ��������ת��Ϊ������ */
	BigNum(long long);
	/* ���ַ�����ʾ����ת��Ϊ������ */
	BigNum(const string&);
	/* �����д�������һ����ȵĴ��� */
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

	/* ���˴���ת��Ϊ�ȼ۵��ַ�����ʾ��ʽ�� */
	string ToString();
};