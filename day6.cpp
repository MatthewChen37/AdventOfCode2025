#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <stack>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>

using namespace std;

vector<string> special_split(string s, char delimiter) {
	int idx = 0;
	vector<string> tokens;
	string token;

	while (idx != string::npos && s[idx] == delimiter) {
		idx++;
	}
	s.erase(0, idx);

	while ((idx = s.find(delimiter)) != string::npos) {
		int proceeding_ws = 0;
		while (idx + proceeding_ws != string::npos && s[idx + proceeding_ws] == delimiter) {
			proceeding_ws++;
		}
		token = s.substr(0, idx);
		// cout << "Token: " << token << " Length: " << token.size() <<  endl;
		tokens.push_back(token);
		s.erase(0, idx + proceeding_ws);
	}

	s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
	if (s.size() > 0) {
		tokens.push_back(s);
	}
	return tokens;
}

void printVecString(vector<string> strings) {
	string out = "Line: ";
	for (string s: strings) {
		out += s + " ";
	}
	out = out + "Length: " + to_string(static_cast<int>(strings.size())); 
	cout << out << endl;
}

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day6.txt");
	if (!infile.is_open()) {
		return -1;
	}


	long long sol = 0;
	char SPACE = ' ';
	string in;

	vector<string> operations;
	vector<vector<string>> lines;
	while (getline(infile, in)) {
		if (infile.peek() == EOF) {
			operations = special_split(in, SPACE);
			break;
		} else {
			printVecString(special_split(in, SPACE));
			lines.push_back(special_split(in, SPACE));
		}
	}
	cout << "Number of lines: " << lines.size() << endl;
	cout << "Numbers per line: " << lines[0].size() << endl;
	cout << "Number of operations: " << operations.size() << endl;

	int n = lines[0].size();
	int m = lines.size();
	string times = "*";
	string plus = "+";
	for (int i = 0; i < n; ++i) {
		long col_sol = 0;
		if (operations[i] == times) {
			col_sol = 1;
		}
		for (int j = 0; j < m; ++j) {
			if (operations[i] == times) {
				col_sol *= stoll(lines[j][i]);
			} else {
				col_sol += stoll(lines[j][i]);
			}
		}
		sol += col_sol;
	}

	cout << "Solution: " << sol << endl;

	return 0;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day6.txt");
	if (!infile.is_open()) {
		return -1;
	}

	long long sol = 0;
	char SPACE = ' ';
	string in;

	string operations;
	vector<string> lines;
	while (getline(infile, in)) {
		if (infile.peek() == EOF) {
			operations = in;
			break;
		} else {
			lines.push_back(in);
		}
	}
	cout << "Number of lines: " << lines.size() << endl;
	cout << "0 Line Length: " << lines[0].size() << endl;
	cout << "1 Line Length: " << lines[1].size() << endl;
	cout << "2 Line Length: " << lines[2].size() << endl;
	cout << "3 Line Length: " << lines[3].size() << endl;

	cout << "Number of operations: " << operations.size() << endl;

	int ops_size = operations.size();
	queue<pair<int, char>> op_q;
	for (int i = 0; i < ops_size; ++i) {
		if (operations[i] != ' ') {
			op_q.push(make_pair(i, operations[i]));
		}
	}

	int n = lines.size();
	int m = lines[0].size();
	char curr_op = op_q.front().second;
	long long running_group_val = curr_op == '*' ? 1 : 0;
	op_q.pop();
	for (int col_idx = 0; col_idx < m; col_idx++) {
		string running_col_num = "";
		if (col_idx == op_q.front().first - 1) {
			curr_op = op_q.front().second;
			op_q.pop();
			sol += running_group_val;
			running_group_val = curr_op == '*' ? 1 : 0;
			continue;
		}

		for (int row_idx = 0; row_idx < n; row_idx++) {
			if (lines[row_idx][col_idx] != ' ') {
				running_col_num += lines[row_idx][col_idx];
			}
		}
		long long running_col_num_l = stol(running_col_num);

		if (curr_op == '*') {
			running_group_val *= running_col_num_l;
		} else {
			running_group_val += running_col_num_l;
		}
	}
	
	sol += running_group_val;

	cout << "Solution: " << sol << endl;

	return 0;
}