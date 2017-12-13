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

int f(int x) {
	return x * x + 1;
}

int mod(int x,int n) {
	while(x >= n) x-=n;
	while(x < 0) x+=n;
	return x;
}



int do2j(int j,int xj,int n) {
	for(int i=j+1;i<=2*j;++i) {
		xj = mod(f(xj),n);
	}
	return xj;
}

void doPollardp(int n) {

	int xj = 2;
	int j = 1;
	bool found = false;
	bool fail = false;
	int res = -1;
	while(!found && !fail) {
		xj = mod(f(xj),n);
		int x2j = do2j(j,xj,n);
		int d = __gcd(abs(x2j-xj),n);
		if( 1 < d && d < n)
			found = true; // SUCCESS
		if(d == n)
			fail = true; //FAILURE
		res = d;
	}
	cout << res << '\n';
	if(found)
		cout << "FOUND" << '\n';
	if(fail)
		cout << "FAIL" << '\n';
}


int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ifstream fpoly("poly.in","r");


	int t,n;
	cin >> t;
	for(int ti=0;ti < t; ++ti) {
		cin >> n;
		auto t1 = std::chrono::high_resolution_clock::now();
		doPollardp(n);
		auto t2 = std::chrono::high_resolution_clock::now();
	}

	return 0;
}