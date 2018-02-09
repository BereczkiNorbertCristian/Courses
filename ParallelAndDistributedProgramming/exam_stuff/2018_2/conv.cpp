#include<bits/stdc++.h>

using namespace std;

void solve(vector<int> a, vector<int> b, int T ) {

	vector<future<void>> futures;
	int n = a.size();
	vector<int> r(n);
	for (int ti = 0; ti < T; ++ti) {
		futures.push_back(async([a, b, ti, n, &r,T]() {
			for (int i = ti; i < n; i += T) {
				for (int j = 0; j < n; ++j) {
					r[i] += a[j] * b[(i - j + n) % n];
				}
			}
		}));
	}

	for (auto& f : futures) f.get();
	for(int x : r) 
		cout << x << '\n';
}

int main() {

	solve({1, 2, 3}, {1, 2, 3}, 1);

	return 0;
}