#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

template<typename T>
void print(T const& xs)
{
	std::cout << "[ ";
	for (auto const& x : xs)
		std::cout << x << ' ';
	std::cout << "]\n";
}

void f2(){
	vector <int> stack;
	char x = 'a';
	int number;
	while (cin >> x){
		if (isdigit(x)){
			cin.putback(x);
			cin >> number;
			stack.push_back(number);
		}else{
			int size = stack.size() - 1;
			int a = stack[size], b = stack[size - 1];
			stack.pop_back();
			stack.pop_back();
			if(x == '+') stack.push_back(a + b);
			else if (x == '-') stack.push_back(b - a);
			else if (x == '/') stack.push_back(b / a);
			else if (x == '*') stack.push_back(a * b);
			if (stack.size() == 1) break;
		}
	}
	cout << stack[0] << endl;
}

string f1(){
	vector <char> stack;
	char x = 'a';
	string number;
	string result = "";
	while (cin >> x){
		if (isdigit(x)){
			cin.putback(x);
			cin >> number;
			result += number + " ";
		}
		else{
			if (x == '+' || x == '-' || x == '/' || x == '*'){
				while (stack.size() != 0){
					char el = stack[stack.size() - 1];
					if ((x == '*' || x == '/') && (el == '+' || el == '-' )){
						break;
					}
					else if (el == '(') break;
					else{
						stack.pop_back();
						result += el;
						result += " ";
					}
				}
				stack.push_back(x);
			}
			else if (x == '(') stack.push_back(x);
			else if (x == ')') {
				char el = stack[stack.size() - 1];
				stack.pop_back();
				while (el != '('){
					cout << el << endl;
					result += el;
					result += " ";
					el = stack[stack.size() - 1];
					stack.pop_back();
				}
			}
		}
	}
	while (stack.size() != 0){
		char el = stack[stack.size() - 1];
		stack.pop_back();
		result += el;
		result += " ";
	}
	return result;
}

string f1_string(string s){
	vector <char> stack;
	char x = s[0];
	s.erase(0, 1);
	string number;
	string result = "";
	while (x != '\0'){
		if (isdigit(x)){
			number = x + s.substr(0,s.find(" "));
			s.erase(0,  s.find("") + 1);
			result += number + " ";
		}
		else{
			if (x == '+' || x == '-' || x == '/' || x == '*'){
				while (stack.size() != 0){
					char el = stack[stack.size() - 1];
					if ((x == '*' || x == '/') && (el == '+' || el == '-')){
						break;
					}
					else if (el == '(') break;
					else{
						stack.pop_back();
						result += el;
						result += " ";
					}
				}
				stack.push_back(x);
			}
			else if (x == '(') stack.push_back(x);
			else if (x == ')') {
				char el = stack[stack.size() - 1];
				stack.pop_back();
				while (el != '('){
					result += el;
					result += " ";
					el = stack[stack.size() - 1];
					stack.pop_back();
				}
			}
		}
		if (s.length() == 0) x = '\0';
		else x = s[0];
		s.erase(0, 1);
	}
	while (stack.size() != 0){
		char el = stack[stack.size() - 1];
		stack.pop_back();
		result += el;
		result += " ";
	}
	return result;
}
int f2_string(string s){
	vector <int> stack;
	char x = s[0];
	s.erase(0, 1);
	int number;
	while (x != '\0'){
		if (isdigit(x)){
			number = stoi(x + s.substr(0, s.find(" ")));
			s.erase(0, s.find("") + 1);
			stack.push_back(number);
		}else{
			int size = stack.size() - 1;
			int a = stack[size], b = stack[size - 1];
			stack.pop_back();
			stack.pop_back();
			if(x == '+') stack.push_back(a + b);
			else if (x == '-') stack.push_back(b - a);
			else if (x == '/') stack.push_back(b / a);
			else if (x == '*') stack.push_back(a * b);
			if (stack.size() == 1) break;
		}
		if (s.length() == 0) x = '\0';
		else x = s[0];
		if (x == ' ') { x = s[1]; s.erase(0, 1); };
		s.erase(0, 1);
	}
	return stack[0];
}

void f2_another_cin(string s){
	vector <int> stack;
	stringstream st;
	st << s;
	char x = 'a';
	int number;
	while (st >> x){
		if (isdigit(x)){
			st.putback(x);
			st >> number;
			stack.push_back(number);
		}
		else{
			int size = stack.size() - 1;
			int a = stack[size], b = stack[size - 1];
			stack.pop_back();
			stack.pop_back();
			if (x == '+') stack.push_back(a + b);
			else if (x == '-') stack.push_back(b - a);
			else if (x == '/') stack.push_back(b / a);
			else if (x == '*') stack.push_back(a * b);
			if (stack.size() == 1) break;
		}
	}
	cout << stack[0] << endl;
}

void f3(string s){
	string pol = f1_string(s);
	cout << f2_string(pol) << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	f2_another_cin("12 3 +");
	system("pause");
	return 0;
}

