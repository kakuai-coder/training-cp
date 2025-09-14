#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool maxim(T &a, T b) {
	return a < b ? a = b, 1 : 0;
}

template <typename T>
bool minim(T &a, T b) {
	return a > b ? a = b, 1 : 0;
}

#define fio(cherry) if (fopen(cherry ".inp", "r")) \
		freopen(cherry ".inp", "r", stdin),  \
		freopen(cherry ".out", "w", stdout); \
// > kakuai < <cherry> >> 04.09.2025 <<
// mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

const int MAXN = 2e5 + 5;
const int64_t INF = (int64_t)1e15 + 11; 

int n, a[MAXN], b[MAXN], c[MAXN], wa[MAXN], wb[MAXN], wc[MAXN];

namespace Subtask1 {
	bool check(void) {
		if (n > 400) return false; 
		return true; 
	}

	int cnt[6 * MAXN]; 
	int64_t suma[MAXN], sumb[MAXN], sumc[MAXN];

	void reset(int *a, int en) {
		for (int i = 1; i <= en; ++i) cnt[a[i]]--;
	} 

	void solve(void) {

		for (int i = 1; i <= n; ++i) {
			suma[i] = suma[i - 1] + wa[i];
			sumb[i] = sumb[i - 1] + wb[i];
			sumc[i] = sumc[i - 1] + wc[i];
		}

		int64_t ans = -INF; 

		for (int x = 0; x <= n; ++x) {
			cnt[a[x]]++; 

			if (x && cnt[a[x]] == 2) break; 

			bool okb = 0; 

			for (int y = 0; y <= n; ++y) {
				cnt[b[y]]++; 

				if (y && cnt[b[y]] == 2) {
					reset(b, y);
					okb = 1;
					break;
				}

				bool okc = 0;

				for (int z = 0; z <= n; ++z) {
					cnt[c[z]]++;
					if (z && cnt[c[z]] == 2) {
						reset(c, z);
						okc = 1; 
						break;
					}

					// cout << x << ' ' << y << ' ' << z << '\n';

					maxim(ans, suma[x] + sumb[y] + sumc[z]);
				}
				if (!okc) reset(c, n);

			}
			if (!okb) reset(b, n);
		}

		cout << ans; 
 	}
}

namespace Subtask2 {
	bool check(void) {
		if (n > 5000) return false; 
		return true; 
	}
	
	int cnt[6 * MAXN];

	int64_t suma[MAXN], sumb[MAXN], sumc[MAXN];
	int64_t maxSA[MAXN], maxSB[MAXN], maxSC[MAXN], lim0[MAXN], lim1[MAXN], lim2[MAXN]; 

	void reset(int *a, int en) {
		for (int i = 1; i <= en; ++i) cnt[a[i]]--;
	} 

	void solve(void) {
		for (int i = 1; i <= n; ++i) {
			suma[i] = suma[i - 1] + wa[i];
			sumb[i] = sumb[i - 1] + wb[i];
			sumc[i] = sumc[i - 1] + wc[i];

			maxSA[i] = max(maxSA[i - 1], suma[i]);
			maxSB[i] = max(maxSB[i - 1], sumb[i]);
			maxSC[i] = max(maxSC[i - 1], sumc[i]);
		}

		memset(lim0, -1, sizeof(lim0));
		memset(lim1, -1, sizeof(lim1));
		memset(lim2, -1, sizeof(lim2));
		
		int i;

		for (i = 0; i <= n; ++i) {
			cnt[a[i]]++; 
			if (i && cnt[a[i]] == 2) {
				
				break; 
			}

			int j;

			for (j = 0; j <= n; ++j) {
				cnt[b[j]]++; 

				if (j && cnt[b[j]] == 2) {
					break;
				}
			}

			lim0[i] = j - 1; 
			reset(b, j);
		}

		reset(a, i); 


		for (i = 0; i <= n; ++i) {
			cnt[a[i]]++; 
			if (i && cnt[a[i]] == 2) {
				break; 
			}

			int j;

			for (j = 0; j <= n; ++j) {
				cnt[c[j]]++; 

				if (j && cnt[c[j]] == 2) {
					break;
				}
			}

			// cout << j - 1 << '\n';

			lim1[i] = j - 1; 
			reset(c, j);
		}

		reset(a, i); 		

		for (i = 0; i <= n; ++i) {
			cnt[b[i]]++; 
			if (i && cnt[b[i]] == 2) {
				break; 
			}

			int j;

			for (j = 0; j <= n; ++j) {
				cnt[c[j]]++; 

				if (j && cnt[c[j]] == 2) {
					break;
				}
			}

			lim2[i] = j - 1; 
			reset(c, j);
		}

		reset(b, i);
		
		int64_t ans = 0; 

		for (int x = 0; x <= n; ++x) {
			for (int y = 0; y <= lim0[x]; ++y) if (lim1[x] != -1 && lim2[y] != -1) {
				// cout << x << ' ' << y <<  ' ' << min(x, y) << '\n';  
				maxim(ans, maxSA[x] + maxSB[y] + maxSC[min(lim1[x], lim2[y])]);
			}
		}

		cout << ans; 
	}
}

namespace Subtask3 {
	
	struct SegmentTree {

		struct Node {
			int l, r;
			int64_t val; 

			Node() {
				l = r = -1; 
				val = 0; 
			}

			Node(int _l, int _r, int64_t _val) : l(_l), r(_r), val(_val) {} 
		};

		Node seg[4 * MAXN]; 

		void build(int id, int l, int r) {
			if (l == r) {
				seg[id] = Node(l, r, 0);

				return ;
			}

			int mid = (l + r) >> 1; 

			build(id << 1, l, mid); 
			build(id << 1 | 1, mid + 1, r);
			
			seg[id] = Node(l, r, 0);
		}

		void update(int id, int pos, int val) {
			if (seg[id].l > pos || seg[id].r < pos) return ; 
			if (seg[id].l == seg[id].r) {
				seg[id].val = val; 
				return ; 
			}

			update(id << 1, pos, val); 
			update(id << 1 | 1, pos, val); 
			
			seg[id].val = max(seg[id << 1].val, seg[id << 1 | 1].val);
		}

		int64_t query(int id, int l, int r) {
			if (seg[id].l > r || seg[id].r < l) return -INF; 

			if (l <= seg[id].l && seg[id].r <= r) return seg[id].val; 

			return max(query(id << 1, l, r), query(id << 1 | 1, l, r));
		}
	} segtree;

	int64_t maxs[3][MAXN], fw[3][MAXN];
	int  lim[3][MAXN], f[3][MAXN], fir[3][6 * MAXN];

	void solve(void) {
		for (int i = 1; i <= n; ++i) {
			f[0][i] = a[i]; 
			f[1][i] = b[i]; 
			f[2][i] = c[i];
			fw[0][i] = fw[0][i - 1] + wa[i]; 
			fw[1][i] = fw[1][i - 1] + wb[i]; 
			fw[2][i] = fw[2][i - 1] + wc[i];
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < 3; ++j) {
				maxs[j][i] = max(maxs[j][i - 1], fw[j][i]);
			}
		}

		for (int j = 0; j < 3; ++j) {
			for (int x = 1e6; ~x; --x) fir[j][x] = n + 2; 
			for (int i = 1; i <= n; ++i) {
				minim(fir[j][f[j][i]], i);
			}
		}

		int maxB = 0, maxA = 0; 

		memset(lim, -1, sizeof(lim));

		for (int i = 1; i <= n; ++i) {
			if (fir[0][f[0][i]] < i) break; 
			maxA = i; 

			lim[0][]
		}
	}
}

void kakuai(void) { 
	cin >> n; 

	for (int i = 1; i <= n; ++i) cin >> a[i]; 
	for (int i = 1; i <= n; ++i) cin >> wa[i]; 
	for (int i = 1; i <= n; ++i) cin >> b[i]; 
	for (int i = 1; i <= n; ++i) cin >> wb[i]; 
	for (int i = 1; i <= n; ++i) cin >> c[i]; 
	for (int i = 1; i <= n; ++i) cin >> wc[i];
	
	// if (Subtask2::check()) return void(Subtask2::solve());
}

int32_t main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int T = 1;
	// cin >> T;
	while (T--) kakuai();
}
