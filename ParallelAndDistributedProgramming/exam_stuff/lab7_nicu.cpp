// lab7.cpp : Defines the entry point for the console application.
//
#include <cstdlib>
#include <cstdio>
#include <Windows.h>
#include <ctime>
using namespace std;



int a[1000000], b[1000000], n;
HANDLE tids[500];
HANDLE mutexes[1000000];

VOID
compute_f1(
    PVOID arg
)
{
    int k = (int)arg;
    int i;

    for (i = 2 * k - 1; i < n; i+=2*k)
    {
        WaitForSingleObject(mutexes[i], INFINITE);
        b[i] += b[i - k];
        ReleaseMutex(mutexes[i]);
    }

}

VOID
compute_f2(
    PVOID arg
)
{
    int k = (int)arg;
    int i;

    for (i = 3 * k - 1; i < n; i += 2 * k)
    {
        WaitForSingleObject(mutexes[i], INFINITE);
        b[i] += b[i - k];
        ReleaseMutex(mutexes[i]);
    }
}


int main(int argc, char* argv[])
{
    int k;
    if (argc != 2)
    {
        printf("[USAGE] lab7.exe <nr of elements>");
        return 1;
    }
    int noThreads;
    n = atoi(argv[1]);

    clock_t start = clock();

    int i;
    for (i = 0; i < n; i++)
    {
        a[i] = rand() % 10;
        b[i] = a[i];
        mutexes[i] = CreateMutex(NULL, FALSE, NULL);
    }

    
    /*
    for (i = 0; i < n; i++)
    {
        printf("%d ", b[i]);
    }

    printf("\n");
    */

    int cnt = 0;

    for (k = 1; k < n; k = k*2, cnt++)
    {
        tids[cnt] = CreateThread(NULL,
            0,
            (LPTHREAD_START_ROUTINE)compute_f1,
            (PVOID)k,
            0,
            NULL
        );
    }

    for (i = 0; i < cnt; i++)
    {
        WaitForSingleObject(tids[i], INFINITE);
    }

    k = k / 4;
    cnt = 0;
    for (; k > 0; k = k/2, cnt++)
    {
        tids[cnt] = CreateThread(NULL,
            0,
            (LPTHREAD_START_ROUTINE)compute_f2,
            (PVOID)k,
            0,
            NULL);
    }

    for (i = 0; i < cnt; i++)
    {
        WaitForSingleObject(tids[i], INFINITE);
    }

    /*
    for (i = 0; i < n; i++)
    {
        printf("%d ", b[i]);
    }
    */
    
    clock_t end = clock();

    for (i = 0; i < n; i++)
    {
        CloseHandle(mutexes[i]);
    }

    printf("[TIME] %.4lf\n", (end - start) / (double)CLOCKS_PER_SEC);
}

