#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
#include<ctime>
#include<thread>
#include<mutex>
#include<iterator>

#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define fi first
#define se second
#define sz size
#define pb push_back
#define mp make_pair
#define bg begin
#define nd end
using namespace std;

#define int long long

const int maxn = 100003;
const int maxk = 1003;

vector<int> g[maxn];
vector<int> perm;
map<pii,int> edges;
int N;
mutex permute;
int doN;
bool can_permute = true;

void printState(vector<int>& state){
	for(int i=0;i<state.size();++i){
		cout << state[i] << ' ';
	}
	cout << '\n';
}

void generate(int N,int M) {

	for(int i=0;i<N;++i){
		g[i].clear();
	}
	vector<int> sureToBe(N);
	for(int i=1;i<=N;++i){
		sureToBe[i-1] = i;
	}
	std::random_shuffle(sureToBe.begin(),sureToBe.end());
	printState(sureToBe);
	for(int i=1;i<N;++i){
		int nod1 = sureToBe[i-1];
		int nod2 = sureToBe[i];
		edges[{nod1,nod2}] = 1;
		edges[{nod2,nod1}] = 1;
		cout << nod1 << ' ' << nod2 << '\n';
	}
	for(int i=0;i<M;++i){
		int nod1 = rand()%N + 1;
		int nod2 = rand()%N + 1;
		edges[{nod1,nod2}] = 1;
		edges[{nod2,nod1}] = 1;
	}

	perm.resize(N);
	for(int i=0;i<N;++i){
		perm[i] = i+1;
	}
}

bool checkState(vector<int>& state){
	for(int i=0;i<state.size() - 1;++i){
		int nod1 = state[i];
		int nod2 = state[i+1];
		if(edges.find({nod1,nod2})==edges.end() && edges.find({nod2,nod1})==edges.end())
			return false;
	}
	return true;
}


void printPerm(){
	for(int p : perm){
		cout << p << ' ';
	}
	cout << '\n';
}

void tryHamiltonianPaths(){

	vector<int> state;

	bool doMore = true;

	while(doMore){
		permute.lock();
		if(doN){
			// printPerm();
			state.resize(0);
			copy(perm.begin(),perm.end(),back_inserter(state));
			next_permutation(perm.begin(),perm.end());
			--doN;
		}
		else{
			doMore = false;
		}
		permute.unlock();

		if(checkState(state))
			printState(state);
	}
}

int fact(int N){

	int p = 1;
	for(int i=0;i<N;++i){
		p*=(i+1);
	}
	return p;
}

int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	srand(time(0));

	N = 10;
	int M = 0;
	int WORKERS = 10;

	doN = fact(N);

	generate(N,M);

	thread t[WORKERS];

	for(int i=0;i<WORKERS;++i){
		t[i] = thread(tryHamiltonianPaths);
	}
	for(int i=0;i<WORKERS;++i){
		t[i].join();
	}


	return 0;
}