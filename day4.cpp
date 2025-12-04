#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <queue>
#include <stack>

using namespace std;

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day4.txt");
	if (!infile.is_open()) {
		return -1;
	}

	vector<string> rolls;

	string in;
	while (infile >> in) {
		rolls.push_back(in);
	}

	int n = rolls.size();
	int m = rolls[0].size();

	vector<vector<int>> dirs = {
		{1, 0},
		{-1,0},
		{-1,-1},
		{1,-1},
		{0, -1},
		{0, 1},
		{1, 1},
		{-1,1},
	};

	int sol = 0;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (rolls[i][j] == '@') {
				int total_adj = 0;
				for (auto dir_pair: dirs) {
					int dx = i+dir_pair[0];
					int dy = j+dir_pair[1];
					if (dx < n && dx >= 0 && dy < n && dy >= 0) {
						if (rolls[dx][dy] == '@') {
							total_adj++;
						}
					}
				}

				if (total_adj < 4) {
					sol++;
				}
			}
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

vector<vector<int>> dirs = {
		{1,0},
		{-1,0},
		{-1,-1},
		{1,-1},
		{0,-1},
		{0,1},
		{1,1},
		{-1,1},
	};


int calcTotalAdj(int i, int j, vector<string>& rolls) {
	int total_adj = 0;
	int n = rolls.size();
	int m = rolls[0].size();

	for (auto dir_pair: dirs) {
		int dx = i+dir_pair[0];
		int dy = j+dir_pair[1];
		if (dx < n && dx >= 0 && dy < n && dy >= 0) {
			if (rolls[dx][dy] == '@') {
				total_adj++;
			}
		}
	}
	return total_adj;
}

void printQueueOfPairs(std::queue<std::pair<int, int>> q) { // Pass by value to create a copy
    while (!q.empty()) {
        std::pair<int, int> p = q.front();
        std::cout << "(" << p.first << ", " << p.second << ") ";
        q.pop();
    }
    std::cout << std::endl;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day4.txt");
	if (!infile.is_open()) {
		return -1;
	}

	vector<string> rolls;

	string in;
	while (infile >> in) {
		rolls.push_back(in);
	}

	int n = rolls.size();
	int m = rolls[0].size();


	queue<pair<int, int>> q;
	set<pair<int, int>> visited;

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (rolls[i][j] == '@') {
				int total_adj = calcTotalAdj(i, j, rolls);
				if (total_adj < 4) {
					visited.insert(make_pair(i, j));
					q.push(make_pair(i, j));
				}
			}
		}
	}


	int sol = 0;
	while(!q.empty()) {
		int size = q.size();
		while (size--) {
			pair<int,int> top = q.front();
			q.pop();
			sol++;
			rolls[top.first][top.second] = '.';

			for (auto dir_pair: dirs) {
				int dx = top.first+dir_pair[0];
				int dy = top.second+dir_pair[1];

				if (dx < n && dx >= 0 && dy < n && dy >= 0 &&
					visited.find(make_pair(dx, dy)) == visited.end() &&
					calcTotalAdj(dx, dy, rolls) < 4 &&
					rolls[dx][dy] == '@') {
					visited.insert(make_pair(dx, dy));
					q.push(make_pair(dx, dy));
				}
			};
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}