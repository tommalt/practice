#include <stdio.h>
#include <string>

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

	return ret;
}

int main()
{
	string test;

	test = "aaabbbccc";
	println(collapse2(test));

	test = "aabbbccc";
	println(collapse2(test));

	test = "aaaabbbccc";
	println(collapse2(test));

	test = "aaazbbbccc";
	println(collapse2(test));

}
