#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

char first_repeating_char(string s)
{
	int ascii[256];

	memset(ascii, 0, sizeof ascii);

	for (auto c : s) {
		if (++ascii[(int)c] > 1)
			return c;
	}
	return '\0';
}

int main()
{
	string test;

	test = "foo";
	printf("%c\n", first_repeating_char(test));

	test = "bar";
	printf("%c\n", first_repeating_char(test));

	test = "bazooka gum";
	printf("%c\n", first_repeating_char(test));
}
