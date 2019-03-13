#include <stdio.h>
#include <string>
#include <algorithm>

using namespace std;

void println(string s)
{
	printf("%s\n", s.c_str());
}

string collapse(string s)
{
	string ret;
	
	if (s.empty())
		return "";

	ret.reserve(s.size());
	auto p = s.begin();
	int count = 1;
	char last = *p;
	ret.push_back(*p++);
	for (; p != s.end(); p++) {
		if (*p == last) {
			if (++count < 3) {
				ret.push_back(*p);
			}
		} else {
			ret.push_back(*p);
			last = *p;
			count = 1;
		}
	}
	return ret;
}

string collapse2(string s)
{
	string ret;
	if (s.empty())
		return "";

	ret.reserve(s.size());
	auto p = s.begin();
	char last = *p++;
	int count = 1;
	for (; p != s.end(); p++) {
		if (*p == last) {
			count++;
			if (count == 3) {
				ret.push_back(*p);
				count = 0;
				last = *(p + 1);
			}
		} else {
			for (int i = 0; i < count; i++)
				ret.push_back(last);
			last = *p;
			count = 1;
		}
	}
	for (int i = 0; i < count; i++)
		ret.push_back(last);
	return ret;
}

void replace(string & s)
{
	char current;
	int count;
	int n_spaces;

	if (s.empty())
		return;

	n_spaces = 0;
	auto read = s.begin();
	auto write = s.begin();
	current = *read++;
	count = 1;
	for (;; read++) {
		if (read != s.end() && *read == current) {
			count++;
		} else {
			if (count < 3) {
				read = read - count;
				for (int i = 0; i < count; i++) {
					*write++ = *read++;
				}
			} else { // count >= 3
				n_spaces += count;
			}
			if (read == s.end())
				break;
			count = 1;
			current = *read;
		}
	}
	for (int i = 0; i < n_spaces; i++)
		*write++ = ' ';
}

void prints(string s)
{
	printf("\"%s\"\n", s.c_str());
}

int main()
{
	string test;

	test = "aaabbbcddddd";
	prints(test);
	replace(test);
	prints(test);

	test = "xxaaavbbbc";
	prints(test);
	replace(test);
	prints(test);

	test = "xavvvarrrt";
	prints(test);
	replace(test);
	prints(test);

}
