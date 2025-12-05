#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

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

	ifstream infile("inputs/day5.txt");
	if (!infile.is_open()) {
		return -1;
	}
	string DASH = "-";
	string in;
	vector<vector<long>> ranges;
	while (getline(infile, in) && in != "") {
		// cout << "In: " << in << endl;
		vector<string> range = split(in, DASH);
		ranges.push_back({stol(range[0]), stol(range[1])});
	}

	sort(ranges.begin(), ranges.end(), [](auto & a, auto & b) { return a[0] < b[0]; });

	int n = ranges.size();
	int sol = 0;
	while (infile >> in) {
		long input = stol(in);
		for (int i = 0; i < n; ++i) {
			if (input >= ranges[i][0] && input <= ranges[i][1]) {
				sol++;
				break;
			}
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

int mainPart2() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day5.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string DASH = "-";
	string in;
	vector<vector<long>> ranges;
	while (getline(infile, in) && in != "") {
		vector<string> range = split(in, DASH);
		ranges.push_back({stol(range[0]), stol(range[1])});
	}
	sort(ranges.begin(), ranges.end(), [](auto & a, auto & b) { return a[0] < b[0]; });

	int n = ranges.size();
	vector<vector<long>> merged_intervals;
	merged_intervals.push_back(ranges[0]);
	for (int i = 1; i < n; ++i) {
		if (ranges[i][0] <= merged_intervals.back()[1]) {
			vector<long> back = merged_intervals.back();
			merged_intervals.pop_back();
			merged_intervals.push_back({min(back[0], ranges[i][0]), max(back[1], ranges[i][1])});
		} else {
			merged_intervals.push_back(ranges[i]);
		}
	}

	long sol = 0;
	for (auto interval: merged_intervals) {
		sol += (interval[1] - interval[0] + 1);
	}

	cout << "Solution: " << sol << endl;
	return 0;
}