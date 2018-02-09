#include<bits/stdc++.h>

using namespace std;

atomic<int> ans;

bool pred(vector<int> const& v) {
	if (v.size() == 0) return false;
	return v[0] % 2 == 0;
}

void print_vector(vector<int> const& v) {
	for (int u : v) cout << u << ' ';
	cout << '\n';
}

void solve(vector<int> r, int k, int n, int T) {

	if (r.size() == k) {
		if (pred(r)) {++ans;
			print_vector(r);
		}
		return;
	}

	int last = 0;
	if ( r.size() > 0) last = r[r.size() - 1];
	if (T > 1) {
		vector<int> aux(r);
		thread t([&aux, last, n, k, T]() {
			for (int i = last + 1; i <= n; i += 2) {
				aux.push_back(i);
				solve(aux, k, n, T / 2);
				aux.pop_back();
			}
		});
		for (int i = last + 2; i <= n; i += 2) {
			r.push_back(i);
			solve(r, k, n, T - T / 2);
			r.pop_back();
		}
		t.join();
	}
	else if ( T == 1) {
		for (int i = last + 1; i <= n; ++i) {
			r.push_back(i);
			solve(r, k, n, T);
			r.pop_back();
		}
	}
	else {
		assert(false);
	}
}


int main() {

	int k = 3;
	int n = 6;
	int T = 1;

	solve(vector<int>(), k, n, T);

	cout << ans << '\n';

	return 0;
}