#include<iostream>
#include<atomic>

using namespace std;

int32_t main() {

	atomic<int> atm(0);
	int res = atm.fetch_or(1);
	cout << res << '\n';
	res = atm.fetch_or(1);
	cout << res << '\n';

	return 0;
}
