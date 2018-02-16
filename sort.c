#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int *data = NULL;
#define ARRAY_SIZE(x) (sizeof (x) / sizeof (x)[0])
#define MIN(x,y) ((x) < (y) ? (x) : (y));

void swap(int *l, int *r)
{
	int tmp = *l;
	*l = *r;
	*r = tmp;
}
void show (int *b, int *e, int sep)
{
	while (b != e)
		printf("%d%c", *b++, sep);
}
int *quicksort_partition(int *begin, int *end)
{
	int pivot = *end;
	int *i = begin;
	for (int *j = begin; j < end; j++) {
		if (*j < pivot) {
			swap(i++, j);
		}
	}
	swap(i, end);
	return i;
}
void quicksort(int *begin, int *end)
{
	if (begin < end) {
		int *p = quicksort_partition(begin, end);
		quicksort(begin, p - 1);
		quicksort(p + 1, end);
	}
}
void bubblesort(int *begin, int *end)
{
	for (--end ; end > begin; end--) {
		for (int *b = begin; b != end; b++) {
			if (*b > *(b + 1)) {
				swap(b, b + 1);
			}
		}
	}
}
void insertion_sort(int *begin, int *end)
{
	int *i, *j;
	for (i = begin + 1; i != end; i++) {
		for (j = i; j > begin && *(j - 1) > *j; j--) {
			swap(j - 1, j);
		}
	}
}
void selection_sort(int *begin, int *end)
{
	for ( ; begin != end; begin++) {
		int *min = begin;
		for (int *p = begin; p != end; p++) {
			min = (*min < *p) ? min : p;
		}
		swap(begin, min);
	}
}
void shell_sort(int *begin, int *end)
{
	int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
	for (int g = 0; g < ARRAY_SIZE(gaps); g++) {
		int gap = gaps[g];
		for (int *i = begin + gap; i < end; i++) {
			int tmp = *i;
			int *j;
			for (j = i; (j >= begin + gap) && *(j - gap) > tmp; j -= gap) {
				*j = *(j - gap);
			}
			*j = tmp;
		}
	}
}
int *binary_search(int *begin, int *end, int x)
{
	ptrdiff_t diff = (end - begin) / 2;
	if (!diff) return (*begin == x) ? begin : NULL;
	int *middle = begin + diff;
	if (x < *middle) {
		return binary_search(begin, middle, x);
	} else if (x > *middle) {
		return binary_search(middle + 1, end, x);
	} else if (x == *middle) {
		return middle;
	}
	return NULL;
}
int main()
{
	int array[] = {
		9,6,9,10,7,2
	};
	data =array;
	int len = ARRAY_SIZE(array);
	//quicksort(array, array + ARRAY_SIZE(array) - 1);
	//insertion_sort(array, array + ARRAY_SIZE(array));
	//selection_sort(array, array + ARRAY_SIZE(array));
	shell_sort(array, array + len);
	show(array, array + ARRAY_SIZE(array), '\n');

}
