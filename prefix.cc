#include <string.h>

#include <iostream>
#include <vector>
#include <string>

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define eos(s) (s + strlen(s))

using namespace std;

int isop(string const & s)
{
	char c = s.front();
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int prec(string const & op)
{
	char c = op.front();
	if (c == '+' || c == '-')
		return 0;
	else if (c == '*' || c == '/')
		return 1;
	else
		return -1;
}


string format(string const& op, vector<string> const& values)
{
	char buffer[256];
	sprintf(buffer, "(%c", op[0]);
	for (auto it = values.rbegin(); it != values.rend(); it++) {
		sprintf(eos(buffer), " %s", (*it).c_str());
	}
	sprintf(eos(buffer), ")");
	return std::string(buffer);
}

void collapse(vector<string> *operators, vector<string> *values)
{
	auto op = operators->back(); operators->pop_back();
	vector<string> tmp_values;
	tmp_values.push_back(values->back()); values->pop_back();
	tmp_values.push_back(values->back()); values->pop_back();
	while (!operators->empty() && operators->back() == op) {
		operators->pop_back();
		tmp_values.push_back(values->back()); values->pop_back();
	}
	auto expr = format(op, tmp_values);
	values->push_back(expr);
}

int main()
{
	vector<string> operators;
	vector<string> values;
	string token;
	while (cin >> token) {
		if (!isop(token)) {
			values.push_back(token);
		} else {
			if (!operators.empty()) {
				if (prec(operators.back()) > prec(token) ||
				    (prec(operators.back()) == prec(token) && token != operators.back())) {
					collapse(&operators, &values);
					operators.push_back(token);
				} else {
					operators.push_back(token);
				}
			} else {
				operators.push_back(token);
			}
		}
	}

	while (!operators.empty()) {
		collapse(&operators, &values);
	}
	printf("%s\n", values[0].c_str());
}
