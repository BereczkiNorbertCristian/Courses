#include<bits/stdc++.h>

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

// SIMPLE KARATSUBA
const int maxn = 100003;
const int maxk = 1003;

	vector<int> X,Q,RES;

template<typename T>
struct KaratsubaSolver {
    static const int N = (1 << 11);
    T A[N], B[N], R[10 * N];

    void gradeSchool(T A[], T B[], T R[], int n) {
        int i, j;
        for(i = 0; i < 2 * n; i++)
            R[i] = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                R[i + j] += A[i] * B[j];
    }

    void karatsuba(T A[], T B[], T R[], int n) {

        if(n <= 4)
            return gradeSchool(A, B, R, n);

        T *Ar = A, *Al = A + n/2,
          *Br = B, *Bl = B + n/2,
          *Asum = R + n*5,
          *Bsum = R + n*5 + n/2,
          *X1 = R + n*0,
          *X2 = R + n*1,
          *X3 = R + n*2;


        for(int i = 0; i < n / 2; ++i) {
            Asum[i] = Al[i] + Ar[i];
            Bsum[i] = Bl[i] + Br[i];
        }

        karatsuba(Ar, Br, X1, n/2);
        karatsuba(Al, Bl, X2, n/2);
        karatsuba(Asum, Bsum, X3, n/2);

        for(int i = 0; i < n; ++i)
            X3[i] = X3[i] - X1[i] - X2[i];
        for(int i = 0; i < n; ++i)
            R[i + n/2] += X3[i];
    }

    vector<T> Multiply(vector<T> &argA, vector<T> &argB) {

        int N = argA.size() + argB.size() + 1;
        while(N != (N & -N)) ++N;


        fill(A, A + N, 0);
        for(int i = 0; i < argA.size(); ++i)
            A[i] = argA[i];

        fill(B, B + N, 0);
        for(int i = 0; i < argB.size(); ++i)
            B[i] = argB[i];

        karatsuba(A, B, R, N);

        vector<T> ret(argA.size() + argB.size());
        for(int i = 0; i < ret.size(); ++i)
            ret[i] = R[i];

        return ret;
    }

};


void initArrays(int n){

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

	int n;
	cin >> n;

	X.resize(n);Q.resize(n);

	for(int i=0;i<n;++i){
		cin >> X[i];
	}
	for(int i=0;i<n;++i){
		cin >> Q[i];
	}

	KaratsubaSolver<int> polmul;
	auto t1 = std::chrono::high_resolution_clock::now();
	RES = polmul.Multiply(X,Q);
	auto t2 = std::chrono::high_resolution_clock::now();

	cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';

	for(int ch : RES){
		cout << ch << ' ';
	}
	cout << '\n';

	return 0;
}