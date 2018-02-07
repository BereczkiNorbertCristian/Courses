#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>


std::unique_ptr<int[]> a, b;

void func(size_t start, size_t len, size_t iterations)
{
    for(size_t k=0 ; k<iterations ; ++k) {
        for(uint64_t i=0 ; i<len ; ++i) {
            a[start + i] = b[start + i] * b[start + i] * int(k);
        }
    }
}

int main(int argc, char** argv)
{
    long long nrThreads;
    long long lenPerThread;
    long long iterations;
    if(argc != 4 || 1!=sscanf(argv[1], "%lld", &nrThreads)
            || 1!=sscanf(argv[2], "%lld", &lenPerThread)
            || 1!=sscanf(argv[3], "%lld", &iterations)){
        fprintf(stderr, "Usage: vector_sum_multithread nrThreads lenPerThread iterations\n");
        return 1;
    }
    long long totalSize = nrThreads*lenPerThread;
    a.reset(new int[totalSize]);
    b.reset(new int[totalSize]);

    std::vector<std::thread> threads;
    threads.reserve(nrThreads);
    for(unsigned i=0 ; i<nrThreads ; ++i){
        threads.emplace_back(func, lenPerThread*i, lenPerThread, iterations);
    }
    for(unsigned i=0 ; i<nrThreads ; ++i){
        threads[i].join();
    }
}