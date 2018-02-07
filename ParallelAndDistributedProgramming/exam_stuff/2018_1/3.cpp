#include<bits/stdc++.h>

using namespace std;

#define int long long

int n;
int no_threads;
vector<bool> sieve;

int above_sqrt(int x, int sq) {
	int ret = x;
	while (ret <= sq) ret += x;
	return ret;
}

int32_t main() {

	freopen("input.in", "r", stdin);

	cin >> n >> no_threads;

	sieve.resize(n + 1, false);
	int sq = sqrt(n);
	vector<int> current_primes;
	for (int i = 2; i <= sq; ++i) {
		if (sieve[i]) continue;
		current_primes.push_back(i);
		for (int j = i + i; j <= sq; j += i)
			sieve[j] = true;
	}

	if (current_primes.size() < no_threads) no_threads = current_primes.size();

	int step = no_threads / current_primes.size() ;
	if (step == 0) ++step;
	vector<future<void>> futures;
	for (int i = 0; i < no_threads; ++i) {
		vector<int> work_primes;
		for (int j = i; j < current_primes.size(); j += step) {
			work_primes.push_back(current_primes[j]);
		}
		futures.emplace_back(async([work_primes, sq]() {
			for (int p : work_primes) {
				for (int pi = above_sqrt(p,sq); pi <= n; pi += p) {
					if (!sieve[pi]) sieve[pi] = true;
				}
			}
		}));
	}

	for (auto& f : futures) {
		f.get();
	}
	vector<int> primes;
	for (int i = 2; i <= n; ++i) if (!sieve[i]) primes.push_back(i);

	for (int p : primes) cout << p << ' ';
	cout << '\n';

	return 0;
}