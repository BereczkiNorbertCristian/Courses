#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<condition_variable>

using namespace std;

vector<vector<int>> A,B,C,RES,INTER,INTER_ONE,RES_ONE;
int n,m,k,t,workers;
queue<pair<int,int>> complLines;
condition_variable cv;
mutex mtx;
bool valueIsSet = false;

void deb(string s){
	cout << s << '\n';
	cout.flush();
}

void initMatrix(vector<vector<int>>& X,int n,int m,int defVal=-1){

	X.resize(n);
	for(int i=0;i<n;++i){
		X[i].resize(m);
		for(int j=0;j<m;++j){
			if(defVal != -1)
				X[i][j] = defVal;
			else
				X[i][j] = rand()% 10; 
		}
	}
}

void producer(int begIdx,int endIdx){

	for(int i=begIdx;i<endIdx;++i){
		for(int j=0;j<k;++j){
			INTER[i][j] = 0;
			for(int ii=0;ii<m;++ii){
				INTER[i][j] += A[i][ii]*B[ii][j];
			}
		}
	}
	unique_lock<mutex> lock(mtx);
	complLines.push({begIdx,endIdx});
	valueIsSet = true;
	cv.notify_one();
}

void consumer(){

	unique_lock<mutex> lock(mtx);
	while(!valueIsSet)
		cv.wait(lock);
	pair<int,int> lines = complLines.front();
	complLines.pop();

	for(int line = lines.first;line < lines.second; ++line){
		for(int i=0;i<t;++i){
			RES[line][i] = 0;
			for(int j=0;j<k;++j){
				RES[line][i]+= INTER[line][j]*C[j][i];
			}
		}
	}

}

void doOneThread(){

	for(int i=0;i<n;++i){
		for(int j=0;j<k;++j){
			INTER_ONE[i][j] = 0;
			for(int ki=0;ki<m;++ki){
				INTER_ONE[i][j] += A[i][ki]*B[ki][j];
			}
		}
	}

	for(int i=0;i<n;++i){
		for(int j=0;j<t;++j){
			RES_ONE[i][j] = 0;
			for(int ki=0;ki<k;++ki){
				RES_ONE[i][j] += INTER_ONE[i][ki] * C[ki][j];
			}
		}
	}

}

void printMatrix(vector<vector<int>>& MAT){

	for(int i=0;i<n;i++){
		for(int j=0;j<t;j++){
			cout << MAT[i][j] << ' ';
		}
		cout << '\n';
	}
}

void doMoreThreads(){
	thread producers[10];
	thread consumers[10];
	int step = n/workers;
	int stepi = 0;
	int noThrs=  0;
	while(stepi < n){

		int endStep = stepi + step;
		if(endStep >= n){
			endStep = n;
		}
		producers[noThrs] = thread(producer,stepi,endStep);
		consumers[noThrs++] = thread(consumer);
		stepi = endStep;
	}

	for(int i=0;i<noThrs;++i){
		producers[i].join();
		consumers[i].join();
	}
}

template<typename F>
void seeExecTime(F&& f){
	auto t1 = std::chrono::high_resolution_clock::now();
	f();
	auto t2 = std::chrono::high_resolution_clock::now();
	cout << "Duration nanos:" << '\n';
	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
}

int32_t main(){

	freopen("input.in","r",stdin);
	srand(time(NULL));

	n = 500;
	m = 500;
	k = 500;
	t = 500;
	workers = 10;

	initMatrix(A,n,m,1);
	initMatrix(B,m,k,2);
	initMatrix(C,k,t,3);
	initMatrix(RES,n,t,0);
	initMatrix(INTER,n,k,0);
	initMatrix(INTER_ONE,n,k,0);
	initMatrix(RES_ONE,n,t,0);

	cout << "One Thread" << '\n';
	seeExecTime([](){doOneThread();});
	cout << "More Threds" << '\n';
	seeExecTime([](){doMoreThreads();});

	if(n < 6 && t < 6){
		printMatrix(RES);
		printMatrix(RES_ONE);
	}



	return 0;
}