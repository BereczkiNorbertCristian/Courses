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

const int maxn = 1000003;
const int maxk = 1003;

int prim[maxn];

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

void bruteForceCarmichael(int upperBound){

	int counter = 0;
	for(int i=3;i<upperBound;++i){
		if(isCarmichael(i)){
			cout << i << '\n';
			++counter;
		}
	}
	cout << "There were: " << counter << " carmichael numbers" << '\n';


}

vector<int> getSieve(int N){

	vector<int> res;
	int i;
	int j;
	for (i = 2; i <= N; ++i)
        prim[i] = 1;
    for (i = 2; i <= N; ++i)
        if (prim[i])
        {
            res.pb(i);
            for (j = i+i; j <= N; j += i)
                prim[j] = 0;
        }
    return res;
}

bool checkSquareFree(int x,vector<int>& sieve){

	int i = 0;
	while(i < sieve.size() && sieve[i]*sieve[i] <= x){
		if(x % (sieve[i]*sieve[i]) == 0) return false;
		++i;
	}
	return true;
}

void smartCarmichael(int upperBound){

	int cnt = 0;
	vector<int> sieve = getSieve(upperBound);
	for(int i=3;i<upperBound;++i){
		if(i%2 == 0) continue;
		bool cool = true;
		int divs = 0;
		for(int d=2;d*d<=i;++d){
			divs+= (i%d == 0) ? 1 : 0;
			if(i%d == 0){
				if(prim[d]){
					cool &= ((i-1)%(d-1) == 0);
				}

				if(prim[i/d]){
					cool &= ((i-1)%((i/d)-1) == 0);
				}
			}

		}
		cool &= checkSquareFree(i,sieve);
		if(cool && divs > 0){
			cout << i << '\n';
			++cnt;
		}
	}
	cout << cnt << '\n';
}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	// bruteForceCarmichael(n);
	smartCarmichael(n);


	
	return 0;
}