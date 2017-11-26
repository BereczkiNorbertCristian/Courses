#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

// SIMPLE MULTIPLICATION WITH THREADS

mutex mutexes[1000000];
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

void initArrays(){

	srand(time(0));
	for(int i=0;i<n;++i){
		X[i] = rand() % 1000;
	}
	for(int i=0;i<n;++i){
		Q[i] = rand() % 1000;
	}

}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	int workers = 4;

	n = 1000;
	X.resize(n);Q.resize(n);RES.resize(2*n,0);

	threads.resize(workers+1);

	initArrays();

	int crt = 0;
	int step = n/workers;
	int stepi =0;


	auto t1 = std::chrono::high_resolution_clock::now();
	while(stepi < n){
		int endIdx = min(n,stepi + step);
		threads[crt++] = thread(doWork,stepi,endIdx);
		stepi+=step;
	}

	for(int i=0;i<workers;++i){
		threads[i].join();
	}
	auto t2 = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';



	return 0;
}