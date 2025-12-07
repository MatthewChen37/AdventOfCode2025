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

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day7.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string in;
	vector<string> manifold;
	int sol = 0;
	while (getline(infile, in)) {
		manifold.push_back(in);
	}
	

	int n = manifold.size();
	int m = manifold[0].size();
	cout << "Manifold layers: " << n << endl;
	int start_idx = manifold[0].find('S');
	manifold[1][start_idx] = '|';
	for (int i = 2; i < n; i++)  {
		for (int j = 0; j < m; j++) {
			if (manifold[i][j] == '.') {
				if (manifold[i - 1][j] == '|'){
					manifold[i][j] = '|';
				}
			} else if (manifold[i][j] == '^') {
				if (manifold[i - 1][j] == '|') {
					if (j - 1 >= 0) { // Left
						manifold[i][j - 1] = '|';
					}
					if (j + 1 < n) {
						manifold[i][j + 1] = '|';
					}
					sol++;
				}
			}
		}
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

int sol = 0;

void backtrack(vector<string> & manifold, int layer_idx, int n) {
	if (layer_idx == n - 1) {
		sol += 1;
		return;
	}

	int prev_layer_beam_idx = manifold[layer_idx - 1].find('|');

	if (manifold[layer_idx][prev_layer_beam_idx] == '.') {
		manifold[layer_idx][prev_layer_beam_idx] = '|';
		backtrack(manifold, layer_idx + 1, n);
		manifold[layer_idx][prev_layer_beam_idx] = '.';
		return;
	} else {
		// cout << manifold[layer_idx][prev_layer_beam_idx - 1] << endl;
		// ^ case
		if (prev_layer_beam_idx - 1 >= 0) {
			char temp = manifold[layer_idx][prev_layer_beam_idx - 1];
			manifold[layer_idx][prev_layer_beam_idx - 1] = '|';
			backtrack(manifold, layer_idx + 1, n);
			manifold[layer_idx][prev_layer_beam_idx - 1] = temp;
		}

		if (prev_layer_beam_idx + 1 < n) {
			char temp = manifold[layer_idx][prev_layer_beam_idx + 1];
			manifold[layer_idx][prev_layer_beam_idx + 1] = '|';
			backtrack(manifold, layer_idx + 1, n);
			manifold[layer_idx][prev_layer_beam_idx + 1] = temp;
		}
		return;
	}
}

void print2DVector(const std::vector<std::vector<long>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) { // Iterate through rows
        for (size_t j = 0; j < vec[i].size(); ++j) { // Iterate through elements in each row
            std::cout << vec[i][j] << " "; // Print the element
        }
        std::cout << std::endl; // Move to the next line after printing a row
    }
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day7.txt");
	if (!infile.is_open()) {
		return -1;
	}

	string in;
	vector<string> manifold;
	while (getline(infile, in)) {
		manifold.push_back(in);
	}
	

	int n = manifold.size();
	int m = manifold[0].size();
	cout << "Manifold layers: " << n << endl;
	cout << "Manifold length: " << m << endl;
	int start_idx = manifold[0].find('S');
	manifold[1][start_idx] = '|';
	// Brute force backtracking will take too long
	// backtrack(manifold, 2, n); 
	vector<vector<long>> dp(n, vector<long>(m, 0));
	dp[0][start_idx] = 1;
	dp[1][start_idx] = 1;
	for (int i = 2; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (manifold[i][j] == '.') {
				long paths_in = 0;
				if (j == 0) {
					if (manifold[i][j + 1] == '^') {
						paths_in += dp[i - 1][j + 1];
					}
					paths_in += dp[i - 1][j];
					dp[i][j] = paths_in;
				} else if (j == m - 1) {
					if (manifold[i][j - 1] == '^') {
						paths_in += dp[i - 1][j - 1];
					}
					paths_in += dp[i - 1][j];
					dp[i][j] = paths_in;
				} else {
					if (manifold[i][j - 1] == '^') {
						paths_in += dp[i - 1][j - 1];
					}
					if (manifold[i][j + 1] == '^') {
						paths_in += dp[i - 1][j + 1];
					}

					paths_in += dp[i - 1][j];
					dp[i][j] = paths_in;
				}
			}
		}
	}

	long sol = 0;
	for (int j = 0; j < m; ++j) {
		sol += dp[n - 1][j];
	}

	// print2DVector(dp);

	cout << "Solution: " << sol << endl;
	return 0;
}