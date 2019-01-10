/*
 * SOURCE: https://www.youtube.com/watch?v=dnmBJMffcUA
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int find_missing(vector<int> const& v1, vector<int> const& v2)
{
	std::set<int> s2(v2.begin(), v2.end());

	for (auto x : v1) {
		auto found = s2.find(x);
		if (found == s2.end()) {
			return x;
		}
	}
	return -1;
}

int find_missing_xor(vector<int> const& v1, vector<int> const& v2)
{
	int a, b;

	a = b = 0;
	for (auto x : v1) {
		a ^= x;
	}
	for (auto x : v2) {
		b ^= x;
	}
	return a ^ b;
}

int main()
{
	vector<int> v1 = {4,8,12,9,3};
	vector<int> v2 = {4,8,9,3};

	// int m = find_missing(v1,v2);
	int m = find_missing_xor(v1,v2);
	printf("%d\n", m);
}
