#include<iostream>
#include<vector>
#include<queue>
#include<thread>
#include<mutex>
#include<conditional_variable>

using namespace std;

vector<vector<int>> A,B,C,RES,INTER;
int n,m,k,t,workers;
queue<int> complLines;
conditional_variable cv;

void initMatrix(vector<vector<int>>& X,int n,int m,int defVal=-1){

	srand(time(NULL));

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

void firstMul(int lineBeg,int lineEnd){

	for(int i=lineBeg;i<lineEnd;++i){
		for(int ki=0;ki<k;++ki){
			for(int j=0;j<m;++j){
				INTER[i][ki]+=(A[i][j]*B[j][ki]);
			}
		}
		complLines.push(i);
	}
}

int32_t main(){

	freopen("input.in","r",stdin);

	n = 2;
	m = 2;
	k = 2;
	t = 2;
	workers = 2;

	initMatrix(A,n,m,1);
	initMatrix(B,m,k,2);
	initMatrix(C,k,t,3);
	initMatrix(RES,n,t,0);
	initMatrix(INTER,n,k,0);




	return 0;
}