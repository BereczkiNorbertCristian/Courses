#include<iostream>
#include<vector>
#include<thread>
#include<mutex>

using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

// SIMPLE MULTIPLICATION WITH THREADS

mutex mutexes[100];
vector<thread> threads;
vector<int> X,Q,RES;
int n;

void doWork(int startIdx,int endIdx){

	for(int i=startIdx;i<endIdx;++i){
		for(int j=0;j<n;++j){
			int idx = i + j;
			mutexes[idx].lock();
			RES[idx] += X[i] * Q[j];
			mutexes[idx].unlock();
		}
	}
}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	int workers = 3;

	cin >> n;
	X.resize(n);Q.resize(n);RES.resize(2*n,0);

	threads.resize(workers+1);


	for(int i=0;i<n;++i){
		cin >> X[i];
	}

	for(int i=0;i<n;++i){
		cin >> Q[i];
	}
	int crt = 0;
	int step = n/workers;
	int stepi =0;

	while(stepi < n){
		int endIdx = min(n,stepi + step);
		threads[crt++] = thread(doWork,stepi,endIdx);
		stepi+=step;
	}

	for(int i=0;i<workers;++i){
		threads[i].join();
	}

for(int i=0;i<2*n;++i){
		cout << RES[i] <<' ';
	}
	cout << '\n';


	return 0;
}