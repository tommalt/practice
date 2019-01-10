/*
 * A sorted array has been rotated so that the elements might
 * appear in the order 3 4 5 6 7 1 2.
 * how would you find the minimum element?
 * Assume that the array has all unique elements
 */
#include <stdio.h>

#include <algorithm>
#include <vector>

using namespace std;

#define MIN(a,b) ((a) < (b)) ? (a) : (b)

template <typename BiIter>
int find_min_impl(BiIter b, BiIter m, BiIter e)
{
	if ((m - b) <= 1 && (e - m) <= 1) {
		int m1 = MIN(*b, *m);
		int m2 = MIN(*m, *e);
		return MIN(m1, m2);
	}
	if (*m > *e) {
		return find_min_impl(m, m + (e - m) / 2, e);
	} else if (*b < *m) {
		return *b;
	} else {
		return find_min_impl(b, b + (m - b) / 2, m);
	}
}

int find_min(vector<int> const & a)
{
	auto b = a.begin();
	auto e = a.end() - 1;
	if (b == e)
		return *b;
	return find_min_impl(b, b + (e - b) / 2, e);
}


int main()
{
	vector<int> a;
	a.resize(65536);
	for (int i = 0; i < a.size(); i++)
		a[i] = i + 1;

	printf("Running tests ...\n");
	for (int i = 1; i < a.size(); i++) {
		std::rotate(a.begin(), a.begin() + 1, a.end());
		int min = find_min(a);
		if (min != 1) {
			printf("ERROR ON ROTATION %d. min = %d\n", i, min);
			return 1;
		}
	}
	printf("Done.\n");
	return 0;
}
