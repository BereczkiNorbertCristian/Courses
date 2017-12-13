#include<iostream>
#include<fstream>

#include<NTL/ZZ.h>
#include<NTL/vector.h>

#include<chrono>
#include<string>

using namespace std;
using namespace NTL;

ZZ ZZ_ZERO_VAL{0};
ZZ ZZ_ONE_VAL{1};
ZZ ZZ_TWO_VAL{2};

int degree;
Vec<ZZ> poly;

ZZ f(ZZ x) {
	ZZ res{0};
	ZZ xPows{1};
	for(int i=0;i<=degree;++i) {
		res = res + xPows*poly[i];
		xPows = xPows * x;
	}
	return res;
}

ZZ mod(ZZ x,ZZ n) {
	return x % n;
}

ZZ do2j(ZZ j,ZZ xj,ZZ n) {
	for(ZZ i=j+ZZ_ONE_VAL;i<=ZZ_TWO_VAL*j;i = i + ZZ_ONE_VAL) {
		xj = mod(f(xj),n);
	}
	return xj;
}

ZZ absolute(ZZ x){
	if( x < ZZ_ZERO_VAL)
		return ZZ_ZERO_VAL - x;
	return x;
}

ZZ pollardp(ZZ n) {

	ZZ xj{2};
	ZZ j{1};
	bool found = false;
	bool fail = false;
	ZZ res{-1};

	int cnt = 1000000;

	// SHOULD FIND FACTOR IN UNDER cnt OPERATIONS ELSE MIGHT BE PRIME

	while(!found && !fail && cnt--) {
		xj = mod(f(xj),n);
		ZZ x2j = do2j(j,xj,n);
		ZZ d = GCD(absolute(x2j-xj),n);
		if( ZZ_ONE_VAL < d && d < n)
			found = true; // SUCCESS
		if(d == n)
			fail = true; //FAILURE
		res = d;
		j = j + ZZ_ONE_VAL;
	}

	if(found)
		cout << "FOUND" << '\n';
	if(fail)
		cout << "FAIL" << '\n';
	return res;
}

int main(){

	freopen("input.in","r",stdin);
	ifstream fpoly("poly.in");
	ofstream fstats("stats.out");

	string ss;

	fpoly >> degree;
	poly.SetLength(degree + 1);
	for(int i=0;i<=degree;++i) {
		fpoly >> ss;
		ZZ nZZ(INIT_VAL,ss.c_str());
		poly[i] = nZZ;
	}

	int t;
	cin >> t;
	fstats << t;
	for(int i=0;i<t;++i) {
		cin >> ss;
		ZZ nZZ(INIT_VAL,ss.c_str());
		auto t1 = std::chrono::high_resolution_clock::now();
		ZZ reszz = pollardp(nZZ);
		auto t2 = std::chrono::high_resolution_clock::now();
		cout << reszz << '\n';
		fstats << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
	}

	return 0;
}


