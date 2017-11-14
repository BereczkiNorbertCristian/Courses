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

#define int int64_t

const int maxn = 100003;
const int maxk = 1003;

int mul(int a,int b,int n){
	return (a*b)%n;
}

int powMod(int p,int e,int n){

	int res = 1;
	for(int i=0;(1 << i) <= e; ++i){
		if((1<<i)&e)
			res = mul(res,p,n);
		p=mul(p,p,n);
	}
	return res;
}

bool isCarmichael(int x){

	if(x%2 == 0)
		return false;
	bool maybe = false;
	for(int i=2;i<x;++i)
		if(x%i == 0)
			maybe = true;
	if(!maybe)
		return false;
	// cout << "-----" << '\n';
	bool ok = true;
	for(int i=2;i<x;++i){
		// cout << __gcd(x,i) << '\n';
		ok &= __gcd(x,i)==1 ? (powMod(i,x-1,x) == 1) : true;
	}
	return ok;
}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	int counter = 0;
	for(int i=3;i<n;++i){
		if(isCarmichael(i)){
			cout << i << '\n';
			++counter;
		}
	}
	cout << "There were: " << counter << " carmichael numbers" << '\n';

	return 0;
}