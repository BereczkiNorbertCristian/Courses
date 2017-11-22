#include<bits/stdc++.h>
#include<chrono>
using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

// By Euclid's algorithm
int gcd(int a, int b)
{
	while (a > 0)
    {
        int r = b % a;
        b = a;
        a = r;
    } 
    return b;
}

int countDigs(int x){
	int res = 0;
	while(x!=0){
		x/=10;
		++res;
	}
	return res;
}

int simpleGcd(int a,int b){

	int to = min(a,b);
	int d = 1;
	for(int i=1;i<=to;++i){
		if(a % i == 0 && b % i == 0){
			d = i;
		}
	}
	return d;
}

int extendedEuclid(int a,int b,int &x,int &y){

	if(b == 0){
		x = 1;
		y = 0;
		return a;
	}
	int x0,y0;
	int d = extendedEuclid(b,a%b,x0,y0);
	x = y0;
	y = x0 - (a/b)*y0;
	return d;
}
int n;

int32_t main(){

	freopen("algo2.in","r",stdin);
	freopen("algo2.out","w",stdout);

	cin >> n;
	int a,b;
	for(int i=0;i<n;i++){
		cin >> a >> b ;
		auto t1 = std::chrono::high_resolution_clock::now();
		int rs = simpleGcd(a,b);
		auto t2 = std::chrono::high_resolution_clock::now();
		cerr << rs << '\n';
		cout << countDigs(a) << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
	}


	return 0;
}
