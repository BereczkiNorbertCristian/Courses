#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>

using namespace std;

int n = 16;
// int proc_size = 0;
int size_int = sizeof(int);

void zeroPoly(int* x, int ln) {
	for (int i = 0; i < ln; ++i) {
		x[i] = 0;
	}
}

void printPoly(int* poly, int poly_ln) {
	for (int i = 0; i < poly_ln; ++i) {
		cout << poly[i] << ' ';
	}
	cout << '\n';
}

void randPoly(int* poly) {
	for (int i = 0; i < n; ++i) {
		poly[i] = 1;
		cout << poly[i] << ' ';
	}
	cout << '\n';
}

void brute(int* a, int* b, int* res, int poly_ln) {
	for(int i=0;i<poly_ln*2;++i) {
		res[i] = 0;
	}
	for (int i = 0; i < poly_ln; ++i) {
		for (int j = 0; j < poly_ln; ++j) {
			res[i + j] += a[i] * b[j];
		}
	}
}

void send_to_node(int *a, int *b, int n, int nr_proc, int node_id) {
	MPI_Ssend(&nr_proc, 1, MPI_INT, node_id, 123, MPI_COMM_WORLD);
	MPI_Ssend(&n, 1, MPI_INT, node_id, 123, MPI_COMM_WORLD);
	MPI_Ssend(a, n, MPI_INT, node_id, 123, MPI_COMM_WORLD);
	MPI_Ssend(b, n, MPI_INT, node_id, 123, MPI_COMM_WORLD);
}

void recv_from_node(int *res, int n, int node_id) {
	MPI_Status status;
	MPI_Recv(res, 2 * n, MPI_INT, node_id, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
}

void karatsuba(int *a, int *b, int *res, int n, int nr_proc, int me) {
	if (n <= 4) {
		brute(a, b, res, n);
		return;
	}

	int *ar = a;
	int *al = a + n / 2;
	int *br = b;
	int *bl = b + n / 2;
	int *asum = res + n * 5;
	int *bsum = res + n * 5 + n / 2;
	int *x1 = res + n * 0;
	int *x2 = res + n * 1;
	int *x3 = res + n * 2;

	for (int i = 0; i < n / 2; ++i) {
		asum[i] = ar[i] + al[i];
		bsum[i] = br[i] + bl[i];
	}
	if (nr_proc < 3 ) {
		karatsuba(ar, br, x1, n / 2, nr_proc, me);
		karatsuba(al, bl, x2, n / 2, nr_proc, me);
		karatsuba(asum, bsum, x3, n / 2, nr_proc, me);
	}
	else {
		int new_nr_proc = nr_proc / 3;
		int nod1 = me * 3;
		int nod2 = me * 3 + 1;
		int nod3 = me * 3 + 2;

		send_to_node(ar, br, n / 2, new_nr_proc, nod1);
		send_to_node(al, bl, n / 2, new_nr_proc, nod2);
		send_to_node(asum, bsum, n / 2, new_nr_proc, nod3);

		recv_from_node(x1, n / 2, nod1);
		recv_from_node(x2, n / 2, nod2);
		recv_from_node(x3, n / 2, nod3);
	}
	for (int i = 0; i < n; ++i) {
		x3[i] = x3[i] - x1[i] - x2[i];
	}
	for (int i = 0; i < n; ++i) {
		res[i + n / 2] += x3[i];
	}
}

void slave(int me) {

	int parent = me / 3;
	// if (parent == 1) parent = 0;
	int nr_proc, size;

	MPI_Status status;
	MPI_Recv(&nr_proc, 1, MPI_INT, parent, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(&size, 1, MPI_INT, parent, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	int *a = (int*) malloc(size * size_int);
	int *b = (int*) malloc(size * size_int);
	int *res = (int*) malloc(size * 6 * size_int);
	zeroPoly(res, size * 6);

	MPI_Recv(a, size, MPI_INT, parent, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	MPI_Recv(b, size, MPI_INT, parent, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

	karatsuba(a, b, res, size, nr_proc, me);

	MPI_Ssend(res, 2 * size, MPI_INT, parent, 123, MPI_COMM_WORLD);
	free(a);
	free(b);
	free(res);
}

int main() {

	MPI_Init(0, 0);

	int me;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);
	// proc_size = size;
	if (me == 0) {
		// n = 2*n - 1 ;
		while (n != (n & -n)) ++n;
		int *a = (int*) malloc(n * size_int);
		int *b = (int*) malloc(n * size_int);
		int *res = (int*) malloc(n * 6 * size_int);
		zeroPoly(res, n * 6);

		cout << "POLY 1: \n";
		randPoly(a);
		cout << "POLY 2: \n";
		randPoly(b);

		send_to_node(a, b, n, size - 2, 1);
		recv_from_node(res, n, 1);

		for (int i = 0; i < 2 * n; ++i) {
			cout << res[i] << ' ';
		}
		cout << '\n';
		free(a);
		free(b);
		free(res);
	}
	else {
		// int how_much = size - 2;
		// how_much = how_much % 3;
		if ( me == 2) {
			// if (((how_much == 1 || how_much == 2) && me == size - 1) || (how_much == 2 && me == size - 2)) {

			cout << "FINALIZED: " << me << '\n';
			cout.flush();
			MPI_Finalize();
			return 0;
		}
		slave(me);
	}

	cout << "FINALIZED: " << me << '\n';
	cout.flush();
	MPI_Finalize();
	return 0;
}
