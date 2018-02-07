#include<iostream>
#include<thread>
#include<atomic>

using namespace std;

int main(){

	atomic<int> cnt;
	cnt = 0;
	auto f = [&] {cnt++;};
	// thread t1{f},t2{f},t3{f};

	int tst_val = 0;
	int new_val = 2;
	int res = cnt.compare_exchange_strong(tst_val,new_val);
	cout << res << ' ' << cnt << '\n';

	res = cnt.compare_exchange_strong(tst_val,5);
	cout << res << ' ' << cnt << '\n';

	return 0;
}