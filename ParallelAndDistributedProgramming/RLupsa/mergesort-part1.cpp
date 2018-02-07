#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <future>

using namespace std;

void merge(int* begin1, int* end1, int* begin2, int* end2, int* merged)
{
    int* curr1 = begin1;
    int* curr2 = begin2;
    while(curr1<end1 || curr2<end2) {
        if(curr2>=end2 || (curr1<end1 && *curr1<*curr2)) {
            *merged = *curr1;
            ++curr1;
        } else {
            *merged = *curr2;
            ++curr2;
        }
        ++merged;
    }
}

void mergeSortRec(size_t n, int* in, int* buf, bool& isResultInInput, size_t nrThreads)
{
    if(n <= 1) {
        isResultInInput = true;
        return;
    }
    size_t k = n/2;
    bool r1;
    bool r2;
    if(nrThreads >= 2) {
        size_t th = nrThreads/2;
        future<void> f1 = async(launch::async, [k,in,buf,&r1,th]()->void{mergeSortRec(k, in, buf, r1, th);});
        future<void> f2 = async(launch::async, [n,k,in,buf,&r2,nrThreads,th]()->void{mergeSortRec(n-k, in+k, buf+k, r2, nrThreads - th);});
        f1.wait();
        f2.wait();
    } else {
        mergeSortRec(k, in, buf, r1, 1);
        mergeSortRec(n-k, in+k, buf+k, r2, 1);
    }
    if(r2 != r1){
        if(r2){
            copy(in+k, in+n, buf+k);
        } else {
            copy(buf+k, buf+n, in+k);
        }
    }
    if(r1) {
        merge(in, in+k, in+k, in+n, buf);
        isResultInInput = false;
    } else {
        merge(buf, buf+k, buf+k, buf+n, in);
        isResultInInput = true;
    }
}

void mergeSort(int* v, size_t n, size_t nrThreads)
{
    unique_ptr<int[]> buf { new int[n] };
    bool isResultInInput;
    mergeSortRec(n, v, buf.get(), isResultInInput, nrThreads);
    if(!isResultInInput) {
        copy(buf.get(), buf.get()+n, v);
    }
}

void generate(int* v, size_t n, size_t nrThreads)
{
    vector<future<void>> futures;
    futures.reserve(nrThreads);
    size_t start = 0;
    for(size_t th=0 ; th<nrThreads ; ++th) {
        size_t sz = (n-start)/(nrThreads-th);
        futures.push_back(async([v,start,sz]()->void {
            for(size_t i=0 ; i<sz ; ++i) {
                //v[start+i]=rand();
                v[start+i]=(i*101) % 123456;
            }
        }));
        start += sz;
    }
    for(future<void>& f : futures) {
        f.wait();
    }
}

bool isSorted(int const* const& v, size_t n)
{
    for(size_t i=1 ; i<n ; ++i) {
        if(v[i-1]>v[i]) return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    size_t n = 0;
    size_t nrThreads = 0;
    if(argc != 3 || 1!=sscanf(argv[1], "%u", &n) || 1!=sscanf(argv[2], "%u", &nrThreads)){
        fprintf(stderr, "usage: mergesort <n> <nrThreads>\n");
        return 1;
    }
    unique_ptr<int[]> v{new int[n]};
    generate(v.get(), n, nrThreads);
    fprintf(stderr, "generated\n");
    chrono::high_resolution_clock::time_point const beginTime = chrono::high_resolution_clock::now();
    
    mergeSort(v.get(), n, nrThreads);
    
    chrono::high_resolution_clock::time_point const endTime = chrono::high_resolution_clock::now();

    cout << (isSorted(v.get(), n) ? "ok" : "WRONG") << "; time="<<  (chrono::duration_cast<chrono::milliseconds>(endTime-beginTime)).count() <<"ms\n";
}