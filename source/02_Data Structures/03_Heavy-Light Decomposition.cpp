//vertex value, klo edge value, turunin nilainya ke vertex bawahnya
class HLD {
public:
	static const int N = 100005;
	int seg[N*4], in[N], out[N], sz[N], dep[N], par[N], root[N], idx[N], val[N], t, n;
	vector<int> edge[N];
	//idx -> actual index, in -> visited time
	HLD():t(0) {}
	HLD(int n):n(n) {
		root[1] = par[1] = 1;
		t = 0;
	}
	void upd(int id, int l, int r, int x, int v) {
		if(l == r) {
			seg[id] = val[x] = v;
			return ;
		}
		int m = l + r >> 1;
		if(in[x] <= m) upd(id<<1, l, m, x, v);
		else upd(id<<1|1, m + 1, r, x, v);
		seg[id] = seg[id<<1] ^ seg[id<<1|1];
	}
	int que(int id, int l, int r, int tl, int tr) {
		if(r < tl || l > tr) return 0;
		if(tl <= l && r <= tr) return seg[id];
		int m = l + r >> 1;
		return que(id<<1, l, m, tl, tr) ^ que(id<<1|1, m + 1, r, tl, tr);
	}
	void build(int id, int l, int r) {
		if(l == r) {
			seg[id] = val[idx[l]];
			return ;
		}
		int m = l + r >> 1;
		build(id<<1, l, m);
		build(id<<1|1, m + 1, r);
		seg[id] = (seg[id<<1] ^ seg[id<<1|1]);
	}
	void dfs(int u = 1, int p = 1, int d = 0) {
		par[u] = p; dep[u] = d; sz[u] = 1;
		int mx = -1;
		for(int &v : edge[u]) {
			if(v == p) continue;
			dfs(v, u, d + 1);
			sz[u] += sz[v];
			if(mx < sz[v]) {
				mx = sz[v];
				swap(v, edge[u][0]);
			}
		}
	}
	void dfsHLD(int u = 1, int p = 1) {
		idx[++t] = u; in[u] = t;
		for(int &v : edge[u]) {
			if(v == p) continue;
			root[v] = (v == edge[u][0] ? root[u] : v);
			dfsHLD(v, u);
		}
		// out[u] = t;
	}
	int lca(int x, int y) {
		int res = 0;
		while(root[x] != root[y]) {
			if(dep[root[x]] < dep[root[y]]) swap(x, y);
			res ^= que(1, 1, n, in[root[x]], in[x]);
			x = par[root[x]];
		}
		if(dep[x] > dep[y]) swap(x, y);
		res ^= que(1, 1, n, in[x], in[y]);
		return res;
	}
	void reset() {
		t = 0;
		for(int i = 1 ; i <= n ; ++i) edge[i].clear();
	}
};
// HLD hld;
// hld = HLD(n);
// hld.dfs();
// hld.dfsHLD();
// hld.build(1, 1, n);
	// hld.upd(1, 1, n, u, v);
	// hld.lca(u, v);
