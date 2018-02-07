#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <iostream>

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

void mergeSortRec(size_t n, int* in, int* buf, bool& isResultInInput)
{
    if(n <= 1) {
        isResultInInput = true;
        return;
    }
    size_t k = n/2;
    bool r1;
    bool r2;
    mergeSortRec(k, in, buf, r1);
    mergeSortRec(n-k, in+k, buf+k, r2);
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

void mergeSort(vector<int>& v)
{
    size_t const n = v.size();
    unique_ptr<int[]> buf { new int[n] };
    bool isResultInInput;
    mergeSortRec(n, v.data(), buf.get(), isResultInInput);
    if(!isResultInInput) {
        copy(buf.get(), buf.get()+n, v.data());
    }
}

void generate(vector<int>& v, size_t n)
{
    v.clear();
    v.reserve(n);
    for(size_t i=0 ; i<n ; ++i) {
        v.push_back(rand());
        //v.push_back((i*101) % 123456);
    }
}

bool isSorted(vector<int> const& v)
{
    for(size_t i=1 ; i<v.size() ; ++i) {
        if(v[i-1]>v[i]) return false;
    }
    return true;
}

int main(int argc, char** argv)
{
    size_t n = 0;
    if(argc != 2 || 1!=sscanf(argv[1], "%u", &n)){
        fprintf(stderr, "usage: mergesort <n>\n");
        return 1;
    }
    vector<int> v;
    generate(v, n);
    
    chrono::high_resolution_clock::time_point const beginTime = chrono::high_resolution_clock::now();
    
    mergeSort(v);
    
    chrono::high_resolution_clock::time_point const endTime = chrono::high_resolution_clock::now();

    cout << (isSorted(v) ? "ok" : "WRONG") << "; time="<<  (chrono::duration_cast<chrono::milliseconds>(endTime-beginTime)).count() <<"ms\n";
}