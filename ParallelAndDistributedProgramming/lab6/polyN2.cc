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

// #define int long long

// SIMPLE MULTIPLICATION

const int maxn = 100003;
const int maxk = 1003;

vector<int> X,Q,RES;
int n;


int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	cin >> n;
	X.resize(n);Q.resize(n);RES.resize(2*n,0);
	for(int i=0;i<n;++i){
		cin >> X[i];
	}
	for(int i=0;i<n;++i){
		cin >> Q[i];
	}

	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			RES[i + j] += X[i] * Q[j];
		}
	}

	for(int i=0;i<2*n;++i){
		cout << RES[i] <<' ';
	}
	cout << '\n';

	return 0;
}