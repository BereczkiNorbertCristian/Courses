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

int t;
int n;

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	freopen("fact.out","w",stdout);
	#endif

	ios_base::sync_with_stdio(false);

	cin >> t;
	for(int i=0;i<t;++i){
		cin >> n;
		vector<int> dvs;
		auto t1 = std::chrono::high_resolution_clock::now();
		int div = 2;
		while(n!=1) {
			if(n % div == 0) {
				while(n % div == 0 ) n /= div;
				dvs.pb(div);
			}
			++div;
			if(div > n) break;
		}
		auto t2 = std::chrono::high_resolution_clock::now();
		cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
		for(int ch : dvs) {
			cerr << ch << ' ';
		}
		cerr << '\n';
	}

	return 0;
}