#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Fraction{
private:
	int p, q;
	void reduce(){
		int n = nod();
		p /= n;//p/q
		q /= n;
	}
	int nod(){
		int max = p >= q ? p : q;
		int min = p <= q ? p : q;
		int max_old; 
		while (max % min != 0){
			max_old = max;
			max = min;
			min = max_old % min;
		}
		return min;
	};
public:
	Fraction(){
		p = 1;
		q = 1;
	}
	Fraction(const int new_p, const int new_q){
		p = new_p;
		q = new_q;
		reduce();
	}

	Fraction operator+ (Fraction b){
		Fraction result((this->q)*b.p + b.q*(this->p), this->q * b.q);
		return result;
	}
	Fraction operator- (Fraction b){
		Fraction result(-(this->q)*b.p + b.q*(this->p), this->q * b.q);
		return result;
	}
	Fraction operator* (Fraction b){
		Fraction result(this->p * b.p, this->q * b.q);
		return result;
	}
	Fraction operator/ (Fraction b){
		Fraction result(this->p * b.q, this->q * b.p);
		return result;
	}
	bool operator > (Fraction b){
		return this->p * b.q - this->q * b.p >0;
	}
	bool operator >= (Fraction b){
		return this->p * b.q - this->q * b.p >=0;
	}
	bool operator < (Fraction b){
		return !(*this > b);
	}
	bool operator <= (Fraction b){
		return !(*this >= b);
	}
	bool operator == (Fraction b){
		return (this->p == b.p) && (this->q == b.q);
	}
	bool operator != (Fraction b){
		return (this->p != b.p) || (this->q != b.q);
	}
	void print(){
		cout << p << "/" << q << endl;
	}
};


int _tmain(int argc, _TCHAR* argv[])
{
	Fraction fr1(2, 3);
	Fraction fr2(1, 2);
	Fraction fr3(2, 4);
	cout << (fr1>fr2) << endl;
	cout << (fr1<fr2) << endl;
	cout << (fr1 == fr2) << endl;
	cout << (fr1 != fr2) << endl;
	cout << (fr3 == fr2) << endl;
	cout << (fr3 >= fr2) << endl;
	Fraction z1 = fr1 + fr2;
	Fraction z2 = fr1 * fr2;
	Fraction z3 = fr1 - fr2;
	Fraction z4 = fr1 / fr2;
	z1.print();
	z2.print();
	z3.print();
	z4.print();
	system("pause");
	return 0;
}

