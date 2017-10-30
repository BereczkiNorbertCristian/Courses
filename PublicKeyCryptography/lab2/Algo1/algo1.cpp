#include<bits/stdc++.h>
#include<chrono>
using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

// By repeated substractions
int gcd(int a, int b)
{
    // Everything divides 0 
    if (a == 0 || b == 0)
       return 0;
 
    // base case
    if (a == b)
        return a;
 
    // a is greater
    if (a > b)
        return gcd(a-b, b);
    return gcd(a, b-a);
}

int countDigs(int x){
	int res = 0;
	while(x!=0){
		x/=10;
		++res;
	}
	return res;
}

int n;

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("algo1.in","r",stdin);
	freopen("algo1.out","w",stdout);
	#endif

	ios_base::sync_with_stdio(false);

	cin >> n;
	int a,b;
	for(int i=0;i<n;i++){
		cin >> a >> b ;
		auto t1 = std::chrono::high_resolution_clock::now();
		gcd(a,b);
		auto t2 = std::chrono::high_resolution_clock::now();
		cout << countDigs(a) << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
	}


	return 0;
}
