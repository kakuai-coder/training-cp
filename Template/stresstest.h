/*
Author: kakuai
created: ${CURRENT_YEAR}.${CURRENT_MONTH}.${CURRENT_DATE}
*/
#include <bits/stdc++.h>

using namespace std;

namespace std {

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maximize(T &a, const T &b) {
	return a < b ? a = b, true : false;
}
template <typename T>
bool minimize(T &a, const T &b) {
	return a > b ? a = b, true : false;
}

template <typename T>
int size32(const T &a) {
	return (int)a.size();
}

template <typename T, int D>
struct Vec : public vector<Vec<T, D - 1>> {
	static_assert(D >= 1, "Error");
	template <typename... Args>
	Vec(int n = 0, Args... args)
		: vector<Vec<T, D - 1>>(n, Vec<T, D - 1>(args...)) {}
};
template <typename T>
struct Vec<T, 1> : public vector<T> {
	Vec(int n = 0, const T &val = T()) : vector<T>(n, val) {}
};
}  // namespace std

#define cherry ""

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

namespace GenrateTest {
	int64_t randInt(int64_t l, int64_t r) {
		return uniform_int_distribution<int64_t> (l, r) (rng);
	}

	pair<int, int> randRange(int lo, int n) {
		int l = randInt(lo, max(lo, n / 2)); 

		int r = randInt(l, n);

		return {l, r};
	}

	vector<int> randArr(int n, int maxNumber) {
		vector<int> v; 

		for (int i = 0; i < n; ++i) {
			v.push_back(randInt(0, maxNumber));
		}

		random_shuffle(v.begin(), v.end());

		return v; 
	}

	vector<int> randPermution(int n) {
		vector<int> v; 

		for (int i = 0; i < n; ++i) {
			v.push_back(randInt(1, n));
		}

		random_shuffle(v.begin(), v.end());

		return v; 
	}

	char randaz() {
		return char(randInt(0, 26) + 'a');
	}

	char randAZ() {
		return char(randInt(0, 26) + 'A');	
	}

	vector<pair<int, int>> randTree(int numNode) {

		vector<int> prufer;
		for (int i = 0; i < numNode - 2; ++i) {
			prufer.push_back(randInt(1, numNode));
		}
		vector<int> degree(numNode + 1, 1);
		for (int x : prufer) degree[x]++;
		set<int> leaves;
		for (int i = 1; i <= numNode; ++i) {
			if (degree[i] == 1) leaves.insert(i);
		}
		vector<pair<int, int>> edges;
		for (int x : prufer) {
			int leaf = *leaves.begin();
			leaves.erase(leaves.begin());
			edges.emplace_back(leaf, x);
			if (--degree[x] == 1) leaves.insert(x);
		}

		auto it = leaves.begin();
		int u = *it++;
		int v = *it;
		edges.emplace_back(u, v);
		return edges;
	}

	vector<pair<int, int>> randGraph(int numNode, int numEdge) {
		set<pair<int, int>> edgeSet;
		vector<pair<int, int>> edges;

		while (size32(edges) < numEdge) {
			int u = randInt(1, numNode);
			int v = randInt(1, numNode);
			if (u == v) continue;
			if (u > v) swap(u, v);
			if (edgeSet.count({u, v})) continue;
			edgeSet.insert({u, v});
			edges.emplace_back(u, v);
		}

		return edges;
	}

	vector<pair<int, int>> randDAG(int numNode, int numEdge) {
		vector<int> nodes(numNode);
		
		iota(nodes.begin(), nodes.end(), 1);
		shuffle(nodes.begin(), nodes.end(), rng);
		
		set<pair<int, int>> edgeSet;
		vector<pair<int, int>> edges;

		while (size32(edges) < numEdge) {
			int i = randInt(0, numNode - 2);
			int j = randInt(i + 1, numNode - 1);
			int u = nodes[i], v = nodes[j];
			if (edgeSet.count({u, v})) continue;
			edgeSet.insert({u, v});
			edges.emplace_back(u, v);
		}
		return edges;
	}


}

using namespace GenrateTest;

void kakuai(void) {
	// voi26 = winner
	ofstream cout(cherry ".inp"); 
	// genarate test here...
	

	cout.close();
}

int32_t main(void) {

	for (int i = 1; i <= 100; ++i) {
		kakuai(); 

		system(cherry ".exe"); 
		system(cherry "_bf.exe");

		if (system("fc " cherry ".out " cherry ".ans") != 0) {
			return 0;	
		}
	}

	return 0;
}