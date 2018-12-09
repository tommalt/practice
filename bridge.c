#include <stdio.h>
#include <string.h>

int in_order(int *a)
{
	for (int i = 0; i < 32; i++)
		if (a[i] != i + 1)
			return 0;
	return 1;
}

void shuffle(int *cards)
{
	int tmp[32];
	int *l, *r, *w;
	l = cards; r = cards + 16;
	w = tmp;
	for (int i = 0; i < 16; i++) {
		*w++ = *l++;
		*w++ = *r++;
	}
	memcpy(cards, tmp, sizeof tmp);
}

int main()
{
	int cards[32];
	for (int i = 0; i < 32; i++) {
		cards[i] = i + 1;
	}

	shuffle(cards);
	int count = 0;
	do {
		shuffle(cards);
		count++;
	} while (!in_order(cards));

	printf("%d\n", count);
}
