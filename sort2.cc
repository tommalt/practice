#include <stdio.h>

#include <vector>
#include <iostream>
#include <utility>

using namespace std;

template <typename Iter>
void show(Iter begin, Iter end)
{
	cout << *begin++;
	for (; begin != end; begin++)
		cout << ' ' << *begin;
	cout << '\n';
}

template <typename C>
void show(C && cc)
{
	if (!cc.empty()) {
		show(cc.begin(), cc.end());
	}
}

template <typename Iter>
Iter quicksort_partition(Iter begin, Iter end)
{
	int pivot = *end;
	Iter left, right;
	left = right = begin;
	while (right < end) {
		if (*right <= pivot) {
			std::swap(*left++, *right++);
		} else {
			right++;
		}
	}
	swap(*left, *end);
	return left;
}

template <typename Iter>
void quicksort_impl(Iter begin, Iter end)
{
	if (begin < end) {
		Iter middle = quicksort_partition(begin, end);
		quicksort_impl(begin, middle - 1);
		quicksort_impl(middle + 1, end);
	}
}

template <typename Iter>
void quicksort(Iter begin, Iter end)
{
	quicksort_impl(begin, --end);
}

template <typename Iter>
Iter quicksort_hoar_partition(Iter begin, Iter end)
{
	Iter middle = begin + (end - begin) / 2;
	int pivot = *middle;
	--begin;
	++end;
	for (;;) {
		do {
			++begin;
		} while (*begin < pivot);

		do {
			--end;
		} while (*end > pivot);

		if (begin >= end)
			return end;

		swap(*begin, *end);
	}

}

template <typename Iter>
void quicksort_hoar_impl(Iter begin, Iter end)
{
	if (begin < end) {
		auto tmp = end; tmp++;
		printf("Before partition\n");
		show(begin, tmp);
		Iter p = quicksort_hoar_partition(begin, end);
		printf("After partition\n");
		show(begin, tmp);
		quicksort_hoar_impl(begin, p);
		quicksort_hoar_impl(p + 1, end);
	}
}

template <typename Iter>
void quicksort_hoar(Iter begin, Iter end)
{
	quicksort_hoar_impl(begin, --end);
}

template <typename Iter>
Iter binary_search_impl(Iter begin, Iter end, typename std::iterator_traits<Iter>::value_type x)
{
	if (begin < end) {
		Iter mid = begin + (end - begin) / 2;
		if (*mid > x) {
			return binary_search_impl(begin, mid - 1, x);
		} else if (*mid < x) {
			return binary_search_impl(mid + 1, end, x);
		} else {
			return mid;
		}
	} else {
		return begin;
	}
}

template <typename Iter>
Iter binary_search(Iter begin, Iter end, typename std::iterator_traits<Iter>::value_type x)
{
	return binary_search_impl(begin, --end, x);
}


int main()
{
	vector<int> a = {6,5,4,3,2,1};
	quicksort_hoar(a.begin(), a.end());

	show(a);

	auto found = binary_search(a.begin(), a.end(), 6);
	if (found != a.end()) {
		cout << "Found! " << *found << '\n';
	} else {
		cout << "Element not found\n";
	}
}
