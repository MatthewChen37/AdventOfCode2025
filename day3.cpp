#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream infile("inputs/day3.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string in;
	long long sol = 0;
	while (infile >> in) {
		int first_ptr = 0;
		int second_ptr = 1;
		int max_second_ptr = 1;

		int n = in.size();

		while (second_ptr < n) {
			if (second_ptr != n - 1 && (in[second_ptr] - '0') > (in[first_ptr] - '0')) {
				first_ptr = second_ptr;
				max_second_ptr = 0;
			} else {
				max_second_ptr = max(max_second_ptr, in[second_ptr] - '0');
			}
			second_ptr++;
		}

		int max = (in[first_ptr] - '0') * 10 + max_second_ptr;
		sol += max;
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

int toInt(char c) {
	return c - '0';
}

void printStack(stack<int> s) { // Pass by value to create a copy
    if (s.empty()) {
        cout << "Stack is empty." << endl;
        return;
    }

	cout << "Stack Size: " << s.size() << " Stack elements (reversed):" << endl;
	string reversed = "";
    while (!s.empty()) {
        reversed += to_string(s.top()) + " ";
		s.pop();
	}
	reverse(reversed.begin(), reversed.end());
	cout << reversed << endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream infile("inputs/day3.txt");
	if (!infile.is_open()) {
		return -1;
	}

	const int DIGITS = 12;	

	string in;
	long long sol = 0;
	while (infile >> in) {
		int n = in.size();

		stack<int> dec_monotonic_stack;
		for (int i = 0; i < n; ++i) {
			// At most we can pop is n - i IF n - 12 < i < n
			while (!dec_monotonic_stack.empty() && dec_monotonic_stack.top() < toInt(in[i]) && dec_monotonic_stack.size() + n - i > 12) {
				dec_monotonic_stack.pop();
			}
			dec_monotonic_stack.push(toInt(in[i]));

			while (dec_monotonic_stack.size() > DIGITS) {
				dec_monotonic_stack.pop();
			}
		}
		long long max = 0;
		for (int i = 0; i < DIGITS; ++i) {
			max += dec_monotonic_stack.top() * pow(10, i);
			dec_monotonic_stack.pop();
		}
		sol += max;
	}

	cout << "Solution: " << sol << endl;
	return 0;
}
