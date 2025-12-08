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
#include <cmath>
#include <limits.h>
#include <functional>

using namespace std;

// From https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/
class UnionFind {
public:
	vector<int> Parent;
    vector<int> Size;

    UnionFind(int n) {      
        Parent.resize(n);
        for (int i = 0; i < n; i++) {
            Parent[i] = i;
        }

        // Initialize Size array with 1s
        Size.resize(n, 1);
    }

    // Function to find the representative (or the root
    // node) for the set that includes i
    int find(int i) {
        int root = Parent[i];
      
        if (Parent[root] != root) {
            return Parent[i] = find(root);
        }
      
        return root;
    }

    // Unites the set that includes i and the set that
    // includes j by size
    void unionBySize(int i, int j) {
      
        // Find the representatives (or the root nodes) for
        // the set that includes i
        int irep = find(i);

        // And do the same for the set that includes j
        int jrep = find(j);

        // Elements are in the same set, no need to unite
        // anything.
        if (irep == jrep)
            return;

        // Get the size of i’s tree
        int isize = Size[irep];

        // Get the size of j’s tree
        int jsize = Size[jrep];

        // If i’s size is less than j’s size
        if (isize < jsize) {
          
            // Then move i under j
            Parent[irep] = jrep;

            // Increment j's size by i's size
            Size[jrep] += Size[irep];
        }
        // Else if j’s size is less than i’s size
        else {
            // Then move j under i
            Parent[jrep] = irep;

            // Increment i's size by j's size
            Size[irep] += Size[jrep];
        }
    }
};

vector<double> split(string& s, string& delimiter) {
	vector<double> tokens;
	int idx = 0;
	string token; 

	while ((idx = s.find(delimiter)) != string::npos) {
		token = s.substr(0, idx);
		tokens.push_back(stod(token));
		s.erase(0, idx + delimiter.length());
	}

	tokens.push_back(stoi(s));
	return tokens;
}

double distFunc(vector<double>&a, vector<double> & b) {
	return sqrt(pow(a[0] - b[0], 2) + pow(a[1] - b[1], 2) + pow(a[2] - b[2], 2));
}

void print2DVector(const vector<vector<double>>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) { // Iterate through rows
        for (size_t j = 0; j < vec[i].size(); ++j) { // Iterate through elements in each row
            std::cout << vec[i][j] << " "; // Print the element
        }
        cout << endl; // Move to the next line after printing a row
    }
}

void printHeap(auto heap) {
	auto temp_heap = heap;
	while (!temp_heap.empty()) {
		vector<double> top = temp_heap.top();
		cout << "Dist: " << top[0] << " between points " << top[1] << " and " << top[2] << endl;
		temp_heap.pop();
	}
}

int mainPart1() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day8.txt");
	if (!infile.is_open()) {
		return -1;
	}
	string COMMA = ",";
	string in;
	vector<vector<double>> coords;
	while(getline(infile, in)) {
		vector<double> parsed = split(in, COMMA);
		coords.push_back(parsed);
	}
	int n = coords.size();
	cout << "Number of coordinates: " << n << endl;

	int MAX_HEAP_SIZE = 100000;
	struct Compare {
		bool operator()(vector<double>&a, vector<double>&b) {
			return a[0] < b[0];
		}
	};

	priority_queue<vector<double>, vector<vector<double>>, Compare> dist_min_heap;

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; j++) {
			// top smallest elements
			dist_min_heap.push({distFunc(coords[i], coords[j]), static_cast<double>(i), static_cast<double>(j)});
			while (dist_min_heap.size() > MAX_HEAP_SIZE) {
				dist_min_heap.pop();
			}
		}
	}

	cout << "Heap Size: " << dist_min_heap.size() << endl;
	printHeap(dist_min_heap);

	UnionFind uf(n);

	while (!dist_min_heap.empty()) {
		vector<double> top = dist_min_heap.top();
		uf.unionBySize(top[1], top[2]);
		dist_min_heap.pop();
	}

	sort(uf.Size.begin(), uf.Size.end(), greater<int>());

	int sol = 1;
	for (int i = 0; i < 3; ++i) {
		sol *= uf.Size[i];
	}

	cout << "Solution: " << sol << endl;
	return 0;
}

void printVector(vector<int> & v) {
	cout << "Vector elements: ";
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
}

bool isSizeN(UnionFind uf, int n) {	
	for (int i = 0; i < uf.Size.size(); ++i) {
		if (uf.Size[i] == n) {
			return true;
		}
	}
	return false;
}

int mainPart2() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	ifstream infile("inputs/day8.txt");
	if (!infile.is_open()) {
		return -1;
	}
	string COMMA = ",";
	string in;
	vector<vector<double>> coords;
	while(getline(infile, in)) {
		vector<double> parsed = split(in, COMMA);
		coords.push_back(parsed);
	}
	int n = coords.size();
	cout << "Number of coordinates: " << n << endl;

	struct Compare {
		bool operator()(vector<double>&a, vector<double>&b) {
			return a[0] > b[0]; // NOTICE THE CHANGE HERE
		}
	};

	priority_queue<vector<double>, vector<vector<double>>, Compare> dist_max_heap;

	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; j++) {
			// MAX HEAP THIS TIME
			dist_max_heap.push({distFunc(coords[i], coords[j]), static_cast<double>(i), static_cast<double>(j)});
		}
	}

	UnionFind uf(n);
	long sol;
	while (!dist_max_heap.empty()) {
		vector<double> top = dist_max_heap.top();
		uf.unionBySize(top[1], top[2]);

		if (isSizeN(uf, n)) {
			sol = coords[top[1]][0] * coords[top[2]][0];
			break;
		} 
		dist_max_heap.pop();
	}

	cout << "Heap Size: " << dist_max_heap.size() << endl;

	cout << "Solution: " << sol << endl;
	return 0;
}