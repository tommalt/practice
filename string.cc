
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define eos(s) ((s) + strlen((s)))

void reverse_range(char *begin, char *end)
{
	char tmp;
	end--;
	while (begin < end) {
		tmp = *begin;
		*begin = *end;
		*end = tmp;
		begin++; end--;
	}
}

void reverse_words(char *s)
{
	char *begin, *end, *stop;

	stop = eos(s);
	begin = end = s;
	for (; begin < stop;) {
		while (end < stop && isalpha(*end))
			end++;
		reverse_range(begin, end);
		while (end < stop && !isalpha(*end))
			end++;
		begin = end;
	}
}


int main()
{
	char s[32];
	
	printf("Enter a string: ");
	fgets(s, sizeof s, stdin);
	*(eos(s) - 1) = '\0';

	fflush(stdout);
	printf("Entered: %s\n", s);
	reverse_words(s);
	// reverse_words(s, eos(s));
	printf("reversed: %s\n", s);

}
