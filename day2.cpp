#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<string> split(string& s, string& delimiter) {
	// Identical to Python's string.split()
	vector<string> tokens;
	int idx = 0;
	string token; 

	while ((idx = s.find(delimiter)) != string::npos) {
		token = s.substr(0, idx);
		tokens.push_back(token);
		s.erase(0, idx + delimiter.length());
	}

	tokens.push_back(s);
	return tokens;
}


int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream infile("inputs/day2.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string in;
	infile >> in;

	unsigned long long sol = 0;
	string COMMA = ",";
	string DASH = "-";

	vector<string> id_ranges = split(in, COMMA);
	for (auto & range: id_ranges) {
		vector<string> ids = split(range, DASH);
		unsigned long long id_start = stoll(ids[0]);
		unsigned long long id_end = stoll(ids[1]);

		for (unsigned long long i = id_start; i <= id_end; ++i) {
			string as_string = to_string(i);
			int size = as_string.size();
			if (size % 2 == 0) {
				if (as_string.substr(0, (size / 2)) == as_string.substr((size / 2))) {
					sol += i;
				}

			}
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

bool isInvalid(string & s, int length) {
	int n = s.size();
	string prefix = s.substr(0, length);

	int end = n / length;
	if (n % length != 0) {
		end++;
	}
	for (int i = 1; i < end; i++) {
		if (s.substr(i * length, length) != prefix) {
			return false;
		}
	}
	return true;
}

int mainPart2() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	ifstream infile("inputs/day2.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string in;
	infile >> in;

	unsigned long long sol = 0;
	string COMMA = ",";
	string DASH = "-";

	vector<string> id_ranges = split(in, COMMA);
	for (auto & range: id_ranges) {
		vector<string> ids = split(range, DASH);
		unsigned long long id_start = stoll(ids[0]);
		unsigned long long id_end = stoll(ids[1]);

		for (unsigned long long i = id_start; i <= id_end; ++i) {
			string as_string = to_string(i);
			int size = as_string.size();
			for (int length = 1; length <= size / 2; ++length) {
				if (isInvalid(as_string, length)) {
					sol += i;
					break; // avoid double counting
				}
			}
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}