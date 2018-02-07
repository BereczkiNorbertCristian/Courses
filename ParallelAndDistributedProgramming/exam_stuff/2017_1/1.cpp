#include<bits/stdc++.h>

using namespace std;

#define int long long

const int maxn = 1000;

int n, k, T, m;
vector<int> g[maxn];
atomic<int> cnt;

// Precondition: G is a tree
bool dfs(int p, int x,vector<int> const& colors) {
	for (int ch : g[x]) {
		if (ch == p)
			continue;
		if (colors[ch] == colors[x] || !dfs(x, ch, colors)){
			return false;
		}
	}
	return true;
}

void print_vector(vector<int> const& v) {
	for(int x : v) 
		cout << x << ' ';
	cout << '\n';
}

void solve_basic(vector<int> colors,int beg_idx,int end_idx) {
	
	if(colors.size() == n) {
		if(dfs(-1,1,colors)) 
			cnt++;
		return;
	}
	for(int i = beg_idx; i < end_idx; ++i) {
		colors.push_back(i);
		solve_basic(colors,0,k);
		colors.pop_back();
	}
}

void solve(vector<int> colors, int T) {

	if(colors.size() == n) {
		if(dfs(-1,1,colors))
			cnt++;
	}
	if (T >= k && T > 1) {
		vector<future<void>> futures;
		for (int i = 0; i < k; ++i) {
			futures.push_back(async([&colors,T,i]() {
				colors.push_back(i);
				solve(colors, T / k + (i < T % k));
				colors.pop_back();
			}));
		}
		for(auto& f : futures) f.get();
	}
	else {
		vector<future<void>> futures;
		int step = k / T;
		int beg_step = step;
		while(beg_step < k) {
			int end_step = min(beg_step + step,k);
			futures.push_back(async([&colors,beg_step,end_step](){
				solve_basic(colors,beg_step,end_step);
			}));
			beg_step += step;
		}
		solve_basic(colors,0,step);
		for(auto& f : futures) f.get();
	}
}

int32_t main() {

	freopen("input.in", "r", stdin);

	cin >> n >> m >> k >> T;
	int u,v;

	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}

	solve(vector<int>(),T);

	cout << cnt << '\n';

	return 0;
}