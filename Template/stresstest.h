#include <bits/stdc++.h>

using namespace std;

template <typename T>
using pqmin = priority_queue<T, vector<T>, greater<T>>;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

template <typename T>
int ssiz(const T &a) {
	return int(a.size());
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

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 18.08.2025 <<
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());


class GenerateTest {
	public: 
		int MAXN, MINN, MAXV, MINV; 

	
	GenerateTest() = default; 
	~GenerateTest() = default;
		
	GenerateTest(int maxn, int minn, int maxv, int minv) 
		: MAXN(maxn), MINN(minn), MAXV(maxv), MINV(minv) {}

	int64_t randNum(int64_t l, int64_t r) {
		return uniform_int_distribution<int64_t>(l, r)(rng);
	}
		
	int64_t randNum(int64_t r) {
		return uniform_int_distribution<int64_t>(0, r)(rng);
	}	

	private:
		int randN() {
			return randNum(MINN, MAXN);
		}

		vector<int> randArr(int n) {
			vector<int> v; 

			for (int i = 0; i < n; ++i) {
				v.push_back(randNum(MINV, MAXV));
			}

			random_shuffle(v.begin(), v.end());

			return v; 
		}

		vector<int> randPermution(int n) {
			vector<int> v; 

			for (int i = 0; i < n; ++i) {
				v.push_back(randNum(1, n));
			}

			random_shuffle(v.begin(), v.end());

			return v; 
		}

		char randaz() {
			return char(randNum(0, 26) + 'a');
		}

		char randAZ() {
			return char(randNum(0, 26) + 'A');
		}

		vector<pair<int, int>> randTree(int numNode) {

			vector<int> prufer;
			for (int i = 0; i < numNode - 2; ++i) {
				prufer.push_back(randNum(1, numNode));
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

			while (edges.size() < numEdge) {
				int u = randNum(1, numNode);
				int v = randNum(1, numNode);
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

			while (edges.size() < numEdge) {
				int i = randNum(0, numNode - 2);
				int j = randNum(i + 1, numNode - 1);
				int u = nodes[i], v = nodes[j];
				if (edgeSet.count({u, v})) continue;
				edgeSet.insert({u, v});
				edges.emplace_back(u, v);
			}
			return edges;
		}
};

#define FILECODE ""

namespace Subtask {

	ofstream inp(FILECODE".inp");

	void subtask1(void) {

	}

};


int32_t main(void) {
	for (int numTest = 1; numTest <= 100; ++numTest) {
		system("cls");

		Subtask::subtask1();

		system(FILECODE".exe");
		system(FILECODE"__bf.exe");

		if (system("fc " FILECODE".out " FILECODE".ans") != 0) {
			return 1;
		} 
	}

	return 0; 
}
