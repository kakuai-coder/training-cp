/*
	Author: kakuai
	created: 2025.07.01 14:51:45
*/
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template <typename T>  bool maximize(T &a, const T &b) { return a < b ? a = b, true : false; }
template <typename T>  bool minimize(T &a, const T &b) { return a > b ? a = b, true : false; }
#if __cplusplus < 202002L
	template <class T> int ssize(const T &a) { return a.size(); }
#endif
//_____________________________________________________________________________________________

struct Pt {
  i64 x, y;
  bool operator < (const Pt &o) const {
    return x < o.x || (x == o.x && y < o.y);
  }
};

i64 cross(const Pt &a, const Pt &b, const Pt &c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

vector<Pt> convex_hull(vector<Pt> &pts) {
  int n = ssize(pts), k = 0;
  if (n <= 1) return pts;
  sort(pts.begin(), pts.end());
  vector<Pt> H(2 * n);
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && cross(H[k - 2], H[k - 1], pts[i]) <= 0) --k;
    H[k++] = pts[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; --i) {
    while (k >= t && cross(H[k - 2], H[k - 1], pts[i]) <= 0) --k;
    H[k++] = pts[i];
  }
  H.resize(k - 1);
  return H;
}

void kakuai() {
  int N;
  cin >> N;
  vector<Pt> pts(N);
  for (int i = 0; i < N; ++i) {
    cin >> pts[i].x >> pts[i].y;
  }

  vector<Pt> H = convex_hull(pts);
  int m = ssize(H);
  if (m < 4) {
    cout << "0.0\n";
    return;
  }

  auto area2 = [&](int i, int j, int k) {
    return abs(cross(H[i], H[j], H[k]));
  };

  i64 best2 = 0;
  for (int i = 0; i < m; ++i) {
    int k = (i + 1) % m;
    int l = (i + 3) % m;
    for (int j = (i + 2) % m; (j + 1) % m != i; j = (j + 1) % m) {
      while (area2(i, j, k) < area2(i, j, (k + 1) % m)) {
        k = (k + 1) % m;
      }
      while (area2(j, i, l) < area2(j, i, (l + 1) % m)) {
        l = (l + 1) % m;
      }
      i64 cur = area2(i, j, k) + area2(j, i, l);
      maximize(best2, cur);
    }
  }

  cout << fixed << setprecision(1) << (best2 / 2.0) << "\n";
}

//_____________________________________________________________________________________________
int32_t main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	#define cherry "d"
	if (fopen(cherry".inp", "r")) {
		freopen(cherry".inp", "r", stdin);
		freopen(cherry".out", "w", stdout);
	}

	// int Ntest; cin >> Ntest; while (Ntest--)
	kakuai();

	cerr <<"\n[runtime] " << (1.0 * clock() / CLOCKS_PER_SEC) << "s.";
	return 0;
}