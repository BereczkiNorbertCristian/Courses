#include<bits/stdc++.h>
#include<chrono>
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

void initArrays(){

	srand(time(0));
	for(int i=0;i<n;++i){
		X[i] = rand() % 1000;
	}
	for(int i=0;i<n;++i){
		Q[i] = rand() % 1000;
	}

}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	n = 1000;
	X.resize(n);Q.resize(n);RES.resize(2*n,0);
	

	auto t1 = std::chrono::high_resolution_clock::now();
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			RES[i + j] += X[i] * Q[j];
		}
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';



	return 0;
}