#include <vector>
#include <set>
#include <utility>
#include <iostream>
#include <type_traits>

using namespace std;

template <typename Iter>
Iter remove_duplicates(Iter begin, Iter end)
{
	set<std::remove_reference_t<decltype(*begin)> > seen;
	Iter endptr;

	endptr = end;

	for (; begin != end; ) {
		auto found = seen.find(*begin);
		if (found == seen.end()) {
			seen.insert(*begin);
			begin++;
		} else {
			int quit = 0;
			while (found != seen.end()) {
				--endptr;
				if (begin == endptr) {
					quit = 1;
					break;
				}
				swap(*begin, *endptr);
				found = seen.find(*begin);
			}
			if (quit) {
				break;
			}
		}
	}
	return begin;
}


template <typename C>
void show(C && c)
{
	for (auto x : c) {
		cout << x << ' ';
	}
	cout << '\n';
}

int main()
{
	vector<int> nums = {1, 2, 1, 3, 4, 4, 2};

	show(nums);

	auto index = remove_duplicates(nums.begin(), nums.end());
	nums.erase(index, nums.end());

	show(nums);
}
