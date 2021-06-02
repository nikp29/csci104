#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename F>
void forEach(vector<int> &values, F &&func)
{
	// TO DO: change to range based loop
	for (auto &j : values)
	{
		func(j);
	}
}

// TO DO: turn into lambda function
void square(int &number)
{
	number *= number;
}

void print(const vector<int> &values)
{
	// TO DO: change to range based loop
	for (int j : values)
	{
		cout << j << " ";
	}
	cout << endl;
}

int main()
{
	vector<int> values = {4, 8, 15, 16, 23, 42};
	cout << "BEFORE:" << endl;
	print(values);

	for_each(values.begin(), values.end(), [](int &number) { number *= number; });

	cout << "AFTER:" << endl;
	print(values);
}