#include<bits/stdc++.h>

using namespace std;

class A {
public:
	int nebunie() {
		cout << "PPP" << '\n';
		return 1;
	}
};

int do_stuff(int (func*)(void)) {
	func();
	return 1;
}

int main(){ 

	A a;

	do_stuff(a.nebunie());

	return 0;
}