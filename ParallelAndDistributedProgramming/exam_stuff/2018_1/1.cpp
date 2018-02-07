#include<bits/stdc++.h>

using namespace std;

#define int long long

int n;
atomic<int> res(0);
int fact[30];

bool pred(vector<int> const& v) {

	vector<bool> freq(n + 1);
	for (int x : v) {
		freq[x] = 1;
	}
	for (int i = 1; i <= n; ++i) {
		if (!freq[i]) return false;
	}
	return true;
}

void print_vector(vector<int>& v) {
	for(int x : v) {
		cout << x << ' ';
	}
	cout << '\n';
}

int get_ith(set<int>& S, int i) {
	int cnt = 0;
	for (set<int>::iterator it = S.begin(); it != S.end(); it++) {
		if (cnt == i) return *it;
		cnt++;
	}
	cout << i << '\n';
	assert(false);
}

vector<int> convert_to_perm(int x) {
	vector<int> ret(n);
	set<int> S;
	for (int i = 1; i <= n; ++i) S.insert(i);
	for (int i = 0; i < n; ++i) {
		int idx = i + 1;
		assert(x >= 0);
		int mul = (x / fact[n - idx]);
		int it = get_ith(S, mul);
		ret[i] = it;
		S.erase(it);
		x %= fact[n - idx];
	}
	return ret;
}

void solve_basic(int beg_perm, int end_perm) {

	for (int i = beg_perm; i < end_perm; ++i)
		if (pred(convert_to_perm(i))) res++;
}

void solve(int n, int perm, int cnt_threads) {

	vector<future<void>> threads;
	if (n <= cnt_threads && cnt_threads > 1 && n > 0) {
		for (int i = 0; i < n; ++i) {
			int perm_no = perm + i * fact[n - 1];
			int new_cnt_threads = cnt_threads / n + (i < cnt_threads % n);
			threads.emplace_back(async([n, perm_no, new_cnt_threads]() {solve(n - 1, perm_no, new_cnt_threads);}));
		}
	}
	else {
		if (cnt_threads == 0) cnt_threads = 1;
		int step = n / cnt_threads;
		for (int i = 0; i < n; i += step) {
			int end_step = min(n, i + step);
			int beg_perm = perm + i * step * fact[n - 1];
			int end_perm = perm + end_step * fact[n - 1];
			threads.emplace_back(async([beg_perm, end_perm]() {solve_basic(beg_perm, end_perm);}));
		}
		if (n == 0) {
			solve_basic(perm, perm + 1);
		}
	}
	for (auto& t : threads) {
		t.get();
	}
}

void precompute_fact() {
	int pw = 1;
	fact[0] = 1;
	for (int i = 1; i <= 10; ++i) {
		fact[i] = (pw *= i);
	}
}

int32_t main() {

	freopen("input.in", "r", stdin);

	precompute_fact();

	int cnt_threads;

	cin >> n >> cnt_threads;

	solve(n, 0, cnt_threads);

	cout << res << '\n';

	return 0;
}