#include<iostream>
#include<thread>
#include<mutex>
#include<vector>

using namespace std;

// KARASTUBA WITH THREADS

// #define int long long

const int maxn = 100003;
const int maxk = 1003;

mutex decThreads;
int noThreads = 3;

    static const int N = (1 << 9);
    int A[N], B[N], R[6 * N];

    void gradeSchool(int A[], int B[], int R[], int n) {
        int i, j;
        for(i = 0; i < 2 * n; i++)
            R[i] = 0;
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                R[i + j] += A[i] * B[j];
    }

    void karatsuba(int A[], int B[], int R[], int n) {

        if(n <= 4)
            return gradeSchool(A, B, R, n);

        int *Ar = A, *Al = A + n/2,
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

        int setted = 0;
        vector<thread> thrs;
        thrs.resize(3);
        //FIRST THREAD
        decThreads.lock();
        if(noThreads > 0){
        	noThreads--;
        	thrs[0] = thread(karatsuba,Ar,Br,X1,n/2);
        	setted++;
        }
        else{
        	karatsuba(Ar,Br,X1,n/2);
        }
        decThreads.unlock();

        //SECOND THREAD
        decThreads.lock();
        if(noThreads > 0){
        	noThreads--;
        	thrs[1] = thread(karatsuba,Al,Bl,X2,n/2);
        	setted++;
        }
        else{
        	karatsuba(Al, Bl, X2, n/2);
        }
        decThreads.unlock();

        for(int ii=0;ii<setted;++ii){
        	thrs[ii].join();
        }

        //THIRD THREAD
        karatsuba(Asum, Bsum, X3, n/2);

        

        for(int i = 0; i < n; ++i)
            X3[i] = X3[i] - X1[i] - X2[i];
        for(int i = 0; i < n; ++i)
            R[i + n/2] += X3[i];
    }

    vector<int> Multiply(vector<int> &argA, vector<int> &argB) {

        int N = argA.size() + argB.size() + 1;
        while(N != (N & -N)) ++N;

        fill(A, A + N, 0);
        for(int i = 0; i < argA.size(); ++i)
            A[i] = argA[i];

        fill(B, B + N, 0);
        for(int i = 0; i < argB.size(); ++i)
            B[i] = argB[i];

        karatsuba(A, B, R, N);

        vector<int> ret(argA.size() + argB.size());
        for(int i = 0; i < ret.size(); ++i)
            ret[i] = R[i];

        return ret;
    }


int32_t main(){

	#ifndef ONLINE_JUDGE
	freopen("input.in","r",stdin);
	#endif

	ios_base::sync_with_stdio(false);

	vector<int> X,Q,RES;

	int n;
	cin >> n;
	X.resize(n);Q.resize(n);


	for(int i=0;i<n;++i){
		cin >> X[i];
	}

	for(int i=0;i<n;++i){
		cin >> Q[i];
	}


	RES = Multiply(X,Q);

	for(int ch : RES){
		cout << ch << ' ';
	}
	cout << '\n';

	return 0;
}