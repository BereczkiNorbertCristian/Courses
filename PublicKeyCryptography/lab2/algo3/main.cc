#include<iostream>
#include<NTL/ZZ.h>
#include<chrono>
#include<string>

using namespace std;

NTL::ZZ ZZ_ZERO_VAL{0};

NTL::ZZ my_gcd(NTL::ZZ a,NTL::ZZ b){

	while(a > ZZ_ZERO_VAL){
		NTL::ZZ rest;
		rest = b % a;
		b = a;
		a = rest;
	}

	return b;
}

int main(){

	// freopen("algo3.in","r",stdin);
	// freopen("algo3.out","w",stdout);
	freopen("input.in","r",stdin);

	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	string a,b;
	cerr << n << '\n';
	for(int i=0;i<n;i++){
		cin >> a;
		cin >> b;
		NTL::ZZ azz(NTL::INIT_VAL,a.c_str());
		NTL::ZZ bzz(NTL::INIT_VAL,b.c_str());
		auto t1 = std::chrono::high_resolution_clock::now();
		NTL::ZZ reszz = my_gcd(azz,bzz);
		auto t2 = std::chrono::high_resolution_clock::now();
		cerr << reszz << '\n';
		cout << a.length() << ' ' << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
	}

	return 0;
}


