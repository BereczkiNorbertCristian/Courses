#include<bits/stdc++.h>

using namespace std;

// #define int long long

const int maxn = 100003;
const int maxk = 1003;

template <typename T>
int to(T t,T t1) {
  return t + t1;
}

template <typename T>
int to(T t) {
  return t;
}


// The recursive case: we take a number, alongside
// some other numbers, and produce their sum.
template <typename T, typename... Rest>
int sum(T t, Rest... rest) {
  return t + to(rest...);
}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int a = 1;
	int b = 2;

	cout << sum(1,4) << '\n';


	return 0;
}