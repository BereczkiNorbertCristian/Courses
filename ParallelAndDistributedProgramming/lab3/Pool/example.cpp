#include <iostream>
#include <chrono>
#include<vector>

#include "ThreadPool.h"

using namespace std;

vector<vector<int>> A,B,RES,RES_ONE_THREAD;
int n,m,k;
int workers;

bool mul(int begIdx,int endIdx){

    for(int i=begIdx;i<endIdx;++i){
        for(int ki=0;ki<k;++ki){
            RES[i][ki] = 0;
            for(int j=0;j<m;++j){
                RES[i][ki]+=A[i][j]*B[j][ki];
            }
        }
    }
    return true;
}

void doOneThread(){

    for(int i=0;i<n;++i){
        for(int ki=0;ki<k;++ki){
            for(int j=0;j<m;++j){
                RES_ONE_THREAD[i][ki] += A[i][j] * B[j][ki];
            }
        }
    }
}

void withOneThread(){

    auto t1 = std::chrono::high_resolution_clock::now();
    
    doOneThread();
    auto t2 = std::chrono::high_resolution_clock::now();

    cout << "\n";
    cout << "DURATION WITH ONE THREAD: " << '\n';
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';
    cout << '\n';
}

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("input.in","r",stdin);
    #endif

    srand(time(NULL));

    cin >> n >> m >> k;

    cout << "FIRST MATRIX" << '\n';
    A.resize(n);
    for(int i=0;i<n;++i){
        A[i].resize(m);
        for(int j=0;j<m;++j){
            A[i][j] = rand() % 5;
            if(n < 5) cout << A[i][j] << ' ';
        }
        if(n<5) cout << '\n';
    }
    cout << "SECOND MATRIX" << '\n';
    B.resize(m);
    for(int i=0;i<m;++i){
        B[i].resize(k);
        for(int j=0;j<k;++j){
            B[i][j] = rand() % 5;
            if(m < 5) cout << B[i][j] << ' ';
        }

        if(m < 5) cout << '\n';
    }
    RES.resize(n);
    RES_ONE_THREAD.resize(n);
    for(int i=0;i<n;++i){
        RES[i].resize(k);
        RES_ONE_THREAD[i].resize(k);
    }

    cout << n << ' ' << ' ' <<  m << ' ' << k << '\n';

    withOneThread();

    cin >> workers;
    cout << workers << '\n';

    ThreadPool pool(workers);

    vector<future<bool>> tasks;

    int step = n / workers;
    int stepi = 0;
    auto t1 = std::chrono::high_resolution_clock::now();
    while(stepi < n){

        int endi = stepi + step;
        if(endi > n)
            endi = n;

        tasks.emplace_back(
            pool.enqueue([stepi,endi]{
                return mul(stepi,endi);
            })
        );

        stepi+= step;
    }

    for(int i=0;i<tasks.size();++i){
        tasks[i].get();
    }
    auto t2 = std::chrono::high_resolution_clock::now();

    cout << "DURATION WITH MORE WORKERS: " << '\n';
    cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t2-t1).count() << '\n';

    return 0;
}