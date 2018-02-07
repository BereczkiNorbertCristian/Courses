#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>

typedef uint32_t Element;

void add(Element* el, uint64_t iterations)
{
	for(uint64_t i=0 ; i<iterations ; ++i) {
		*el += (i & 0xFFu);
	}
}

Element expected(uint64_t iterations)
{
	uint64_t const cycles = iterations / 0x100u;
	unsigned remaining = iterations % 0x100u;
	uint64_t cycleLen = 0xFFu*0x100u/2u;
	return Element(cycleLen*cycles + (remaining*(remaining+1u))/2u);
}

int main(int argc, char** argv)
{
	int alignment;
	if(argc != 2 || 1!=sscanf(argv[1], "%d", &alignment)){
		fprintf(stderr, "usage: false-sharing <alignment>\n");
		return 1;
	}
	if(alignment <= 0 || alignment % sizeof(Element) != 0) {
		fprintf(stderr, "Alignment must me a positive multiple of %lu\n", sizeof(Element));
		return 1;
	}

	unsigned const nrThreads = 8;
	size_t const allocated = (nrThreads+1)*alignment;
	size_t every = alignment/sizeof(Element);
	
	std::unique_ptr<char[]> buf { new char[allocated] };
	size_t const offset = size_t(buf.get()) % alignment;
	Element* const elements = reinterpret_cast<Element*>(buf.get() + 
		(offset==0 ? 0 : alignment-offset));
	
	printf("Allocated from %p to %p (%lu bytes)\n", buf.get(), buf.get()+allocated, allocated);
	for(unsigned i=0 ; i<nrThreads ; ++i) {
		printf("  elements[%d] at %p ... %p\n", i, elements+i*every, elements+i*every+1);
	}
	
	uint64_t const nrIterations = 0x100000000;
	std::vector<std::thread> threads;
	threads.reserve(nrThreads);
	for(unsigned i=0 ; i<nrThreads ; ++i){
		elements[i*every] = 0;
	}
	for(unsigned i=0 ; i<nrThreads ; ++i){
		threads.emplace_back(add, elements+i*every, nrIterations);
	}
	for(unsigned i=0 ; i<nrThreads ; ++i){
		threads[i].join();
	}
	
	Element const e = expected(nrIterations);
	bool ok = true;
	for(unsigned i=0 ; i<nrThreads ; ++i){
		if(e != elements[i*every]) {
			ok=false;
			printf("For i=%u: expected %u, actual %u\n", i, e, elements[i*every]);
		}
	}
	printf("%s\n", (ok ? "ok" : "WRONG"));
}