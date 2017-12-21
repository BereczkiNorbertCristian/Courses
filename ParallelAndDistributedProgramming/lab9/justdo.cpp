#include<bits/stdc++.h>

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define sz size
#define pb push_back
#define mp make_pair
#define bg begin
#define nd end
using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

void initA(int* x, int n, int val) {
	for (int i = 0; i < n; ++i) {
		x[i] = val;
	}
}

int32_t main() {

#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n = 16;

	int *a = (int*) malloc(n * sizeof(int));
	int *b = (int*) malloc(n * sizeof(int));
	int *res = (int*) malloc((2 * n - 1) * sizeof(int));
	initA(a, n, 1);
	initA(b, n, 1);
	initA(res, 2 * n - 1 , 0);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			res[i + j] += a[i] * b[j];
		}
	}

	for (int i = 0; i < 2 * n - 1; ++i) {
		cout << res[i] << ' ';
	}
	cout << '\n';

	free(a);
	free(b);
	free(res);
	return 0;
}