#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <iterator>

using namespace std;

void generate_impl(int n, vector<string> *out)
{
	if (n == 0)
		return;
	if (n == 1) {
		out->emplace_back("(");
		out->emplace_back(")");
	} else {
		generate_impl(--n, out);
		vector<string> new_output;
		new_output.reserve(out->size() * 2);
		string s1, s2;
		for (auto s : *out) {
			s1 = s2 = s;
			s1.push_back('(');
			s2.push_back(')');
			new_output.push_back(s1);
			new_output.push_back(s2);
		}
		out->assign(make_move_iterator(new_output.begin()), make_move_iterator(new_output.end()));
	}
}

vector<string> generate(int n)
{
	vector<string> output;
	generate_impl(n, &output);
	return output;
}

int isvalid(string s)
{
	string stack;

	if (s.size() % 2 != 0 || s.front() != '(' || s.back() != ')')
		return 0;

	for (auto c : s) {
		if (c == '(') {
			stack.push_back(c);
		} else {
			if (!stack.empty() && stack.back() == '(') {
				stack.pop_back();
			} else {// stack is empty or stop of tack is not open bracket - invalid
				return 0;
			}
		}
	}
	if (stack.empty()) {
		return 1;
	}
	return 0;
}

int main()
{
	for (int i = 0; i < 10; i++) {
		cout << "I = " << i << '\n';
		auto brackets = generate(i);
		for (auto s : brackets) {
			// cout << s << '\n';
			int valid = isvalid(s);

			cout << s;
			if (valid) {
				cout << " VALID\n";
			} else {
				cout << " INVALID\n";
			}
		}
	}
}
