#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool check_is_ip(string ip){
	for (int i = 0; i < 4; i++)
	{
		int index = ip.find_first_of('.');
		index = index > 0 ? index : ip.size();
		string number = ip.substr(0, index);
		ip.erase(0, index + 1);
		if (number.size() == 0) return false;
		if (stoi(number) > 255 || stoi(number) < 0) return false;
	}

	return true;
}


string weird_copy(string s1, string s2){
	string result ="";
	int index = s1.find(s2);
	while (index != -1){
		string ourSubStr = s1.substr(0, index);
		s1.erase(0, index + 1);
		result = result + ourSubStr + "(" + s2 + ")";
		index = s1.find(s2);
	}
	result += s1;
	return result;
}

string sum_inside_string(string s1){
	string result="";
	string local_symbol="", local_number="";
	int local_sum=0;
	for (int i = 0; i < s1.size(); i++)
	{

		if (s1[i] >= 48 && s1[i] <= 57){
			local_symbol = s1.substr(i, 1);
			local_number += local_symbol;
		}
		else {
			local_sum += stoi(local_number);
			local_number = "";
			if (s1[i] != '+'){
				if (local_sum != 0){
					result += to_string(local_sum);
				}
				result += s1.substr(i, 1);
				local_sum = 0;
			}
		}
	}
	local_sum += stoi(local_number);
	if(local_sum != 0){
		result += to_string(local_sum);
	}
	return result;
}

string open_brackets(string s){
	string result = "", str_start;
	vector <string> brackets_strings;
	int index = s.find_first_of('{');
	str_start = s.substr(0, index);
	s.erase(0, index + 1);
	string local_bracket_string;
	index = s.find_first_of(",");
	while (index != -1){
		local_bracket_string = s.substr(0, index);
		s.erase(0, index + 1);
		brackets_strings.push_back(local_bracket_string);
		index = s.find_first_of(",");
	}
	index = s.find_first_of('}');
	local_bracket_string = s.substr(0, index);
	brackets_strings.push_back(local_bracket_string);
	s.erase(0, index + 1);
	for (string x : brackets_strings){
		result += str_start + x + s + ",";
	}
	
	return result.substr(0,result.size()-1);
}


int _tmain(int argc, _TCHAR* argv[])
{
	cout << check_is_ip("155.152.12.555") <<endl;
	cout << weird_copy("ertabcsdftyuabczevbh", "abc")<<endl;
	cout << sum_inside_string("56+55+10-72+35gh32+45")<<endl;
	cout << open_brackets("abc{def,gh,ijkl}mn")<<endl;
	system("pause");
	return 0;
}

