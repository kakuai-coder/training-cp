struct PersistentSegTree {
	struct Node {
		int val, l, r;
		Node() {
			val = 0;
			l = r = -1;
		}

		Node(int _val, int _l, int _r) : val(_val), l(_l), r(_r) {}
	};

	Node tree[maxN * 20];

	int root[maxN];

	int cnt_node = 0;

	int build(int l, int r) {
		int id = cnt_node++;
		if (l == r) {
			tree[id] = Node(0, -1, -1);
			return id;
		}

		int m = (l + r) >> 1;
		tree[id].l = build(l, m);
		tree[id].r = build(m+1, r);


		return id;
	}

	int update(int prev, int l, int r, int pos, int val) {
		if (l > pos || pos > r) return prev;

		int id = cnt_node++;

		tree[id] = tree[prev];

		if (l == r) {
			tree[id].val += val;
			return id;
		}

		int mid = (l + r) >> 1;

		if (pos <= mid) {
			tree[id].l = update(tree[prev].l, l, mid, pos, val);
		} else {
			tree[id].r = update(tree[prev].r, mid + 1, r, pos, val);
		}

		tree[id].val = 0;

		if (tree[id].l != -1) tree[id].val += tree[tree[id].l].val;
		if (tree[id].r != -1) tree[id].val += tree[tree[id].r].val;

		return id;
	}

	int query(int id, int l, int r, int u, int v) {
		if (v < l || r < u) return 0;

		if (u <= l && r <= v) return tree[id].val;

		int mid = (l + r) >> 1;

		return query(tree[id].l, l, mid, u, v) + query(tree[id].r, mid + 1, r, u, v);
	}
};
PersistentSegTree seg;
