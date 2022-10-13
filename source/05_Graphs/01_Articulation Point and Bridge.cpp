const int SZ = 100005;
vector<int> to[SZ];
int vis[SZ], in[SZ], lw[SZ], n, T;
set<int> ap;
set<pii> bridge;
void tarjan(int u, int p = -1) {
	vis[u] = true;
	in[u] = lw[u] = ++T;
	int child = 0;
	for(int &v : to[u]) {
		if(v == p) continue;
		if(vis[v]) {
			lw[u] = min(lw[u], in[v]);
		} else {
			++child;
			tarjan(v, u);
			lw[u] = min(lw[u], lw[v]);
			if(lw[v] >= in[u] && p != -1) ap.insert(u);
			if(lw[v] > in[u]) bridge.insert({u, v});
		}
	}
  if(p == -1 && child > 1)
    ap.insert(u);
}
void getTarjan() {
	for(int i = 1 ; i <= n ; ++i) if(!vis[i]) {
		tarjan(i);
	}
}