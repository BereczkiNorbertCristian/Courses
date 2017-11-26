#include<iostream>
#include<future>
#include<thread>
#include<vector>

#define pb push_back

using namespace std;

const int SIZEN = 100;

mutex mtx;

int computeFenwick(vector<int>& vIn,vector<int>& vOut,int begIdx,int endIdx){

	if(begIdx == endIdx){
		return vIn[begIdx];
	}
	int mid = (begIdx + endIdx) / 2;
	
	future<int> future1 = std::async(std::launch::async,[&](){return computeFenwick(vIn,vOut,begIdx,mid);});
	future<int> future2 = std::async(std::launch::async,[&](){return computeFenwick(vIn,vOut,mid+1,endIdx);});

	int res1 = future1.get();
	int res2 = future2.get();

	vOut[endIdx] = res1 + res2;
	return res1 + res2;
}


void propagete(vector<int>& vOut,int begIdx,int endIdx){

	if(begIdx == endIdx){
		return;
	}
	int mid = (begIdx + endIdx) / 2;
	mtx.lock();
	int tmp = vOut[mid];
	vOut[mid] = vOut[endIdx];
	vOut[endIdx]+=tmp;
	mtx.unlock();
	future<void> f1 = async(launch::async,[&](){propagete(vOut,begIdx,mid);});
	future<void> f2 = async(launch::async,[&](){propagete(vOut,mid+1,endIdx);});

}

vector<int> generate(int n){

	vector<int> res;
	res.reserve(n);

	srand(time(0));
	for(int i=0;i<n;++i){
		// res.pb(rand()%100);
		res.pb(i+1);
	}
	return res;
}

void deb(vector<int>& v){

	for(int x : v){
		cerr << x << ' ';
	}
	cerr << '\n';
}

int main(){

	vector<int> vIn = generate(SIZEN);
	vector<int> vOut = generate(SIZEN);

	computeFenwick(vIn,vOut,0,SIZEN-1);

	int tmp = vOut[SIZEN-1];
	vOut[SIZEN-1] = 0;
	propagete(vOut,0,SIZEN-1);
	vOut.pb(tmp);
	deb(vOut);

	return 0;
}

