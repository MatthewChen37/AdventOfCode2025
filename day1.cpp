#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day1.txt");
	if (!infile.is_open()) {
		return -1;
	}

	int curr = 50;
	int sol = 0;

	string in;
	while (infile >> in) {
		char dir = in[0];
		int mag = stoi(in.substr(1, in.size() - 1));

		if (dir == 'L') {
			curr = (curr - mag + 100) % 100;
		} else {
			curr = (curr + mag) % 100;
		}

		if (!curr) {
			sol++;
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

int mainPart2() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day1.txt");
	if (!infile.is_open()) {
		return -1;
	}

	int curr = 50;
	int sol = 0;

	string in;
	while (infile >> in) {
		char dir = in[0];
		int mag = stoi(in.substr(1, in.size() - 1));

		if (dir == 'L') {
			int temp = curr;
			curr = (curr - mag);
			if (curr <= 0) {
				if (temp == 0) {
					sol += (abs(curr) / 100);
				} else {
					sol += 1 + (abs(curr) / 100);
				}
			}
			curr = (curr%100 + 100) % 100;
		} else {
			curr = (curr + mag);
			if (curr >= 100) {
				sol += curr / 100;
			}
			curr %= 100;
		}


		// cout << "In: " << in << " Curr: " << curr << " Sol: " << sol << endl;

	}

	cout << "Solution: " << sol << endl;
	return 0;
}