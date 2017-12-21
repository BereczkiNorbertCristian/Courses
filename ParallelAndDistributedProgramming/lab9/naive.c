#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <iostream>

using namespace std;

int poly1_ln = 16;
int poly2_ln = 16;
int poly_res_ln = poly1_ln + poly2_ln - 1;

int min(int a, int b) {
	if (a < b)
		return a;
	return b;
}

void randPoly(int* poly, int poly_ln) {
	srand(time(0));
	for (int i = 0; i < poly_ln; ++i) {
		// poly[i] = rand() % 5;
		poly[i] = 1;
		std::cout << poly[i] << ' ';
	}
	std::cout << '\n';
}

void deb(int nr) {
	if (nr == 1) {
		std::cerr << "Wrong size:" << nr << "\n";
	}
}

void printPoly(int* poly, int poly_ln) {
	for (int i = 0; i < poly_ln; ++i) {
		cout << poly[i] << ' ';
	}
	cout << '\n';
}

int main() {

	MPI_Init(0, 0);

	int me;
	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &me);

	int* poly1 = (int*) malloc(poly1_ln * sizeof(int));
	int* poly2 = (int*) malloc(poly2_ln * sizeof(int));

	if (me == 0) {
		std::cout << "POLY 1: " << '\n';
		randPoly(poly1, poly1_ln);
		std::cout << "POLY 2: " << '\n';
		randPoly(poly2, poly2_ln);

		int* poly_res = (int*) malloc(poly_res_ln * sizeof(int));
		int step = poly_res_ln / (size - 1) + 1;

		int* recv_arr = (int*) malloc((step + 1) * sizeof(int));
		int* beg_arr = (int*) malloc(size * sizeof(int));
		int* end_arr = (int*) malloc(size * sizeof(int));

		int stepi = 0;
		int cnt = 0;
		while (stepi < poly_res_ln ) {
			++cnt;
			beg_arr[cnt] = stepi;
			end_arr[cnt] = min(poly_res_ln, step + stepi);
			MPI_Ssend(beg_arr + cnt, 1, MPI_INT, cnt, 123, MPI_COMM_WORLD);
			MPI_Ssend(end_arr + cnt, 1, MPI_INT, cnt, 123, MPI_COMM_WORLD);
			MPI_Ssend(poly1, poly1_ln, MPI_INT, cnt, 123, MPI_COMM_WORLD);
			MPI_Ssend(poly2, poly2_ln, MPI_INT, cnt, 123, MPI_COMM_WORLD);
			stepi += step;
		}
		int cnti = 1;
		MPI_Status status;
		while (cnti <= cnt) {
			MPI_Recv(recv_arr, end_arr[cnti] - beg_arr[cnti], MPI_INT, cnti, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
			for (int i = beg_arr[cnti]; i < end_arr[cnti]; ++i) {
				poly_res[i] = recv_arr[i - beg_arr[cnti]];
			}
			++cnti;
		}
		std::cout << "FINAL: " << '\n';
		for (int i = 0; i < poly_res_ln; ++i) {
			std::cout << poly_res[i] << ' ';
		}
		std::cout << '\n';
		free(poly_res);
		free(recv_arr);
		free(beg_arr);
		free(end_arr);
	}
	else {
		MPI_Status status;
		int begIdx;
		int endIdx;
		int nr;

		MPI_Recv(&begIdx, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &nr);

		MPI_Recv(&endIdx, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &nr);

		MPI_Recv(poly1, poly1_ln, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &nr); deb(nr);

		MPI_Recv(poly2, poly2_ln, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
		MPI_Get_count(&status, MPI_INT, &nr); deb(nr);

		int* send_arr = (int*) malloc((endIdx - begIdx) * sizeof(int));
		for (int i = 0; i <= endIdx - begIdx; ++i) {
			send_arr[i] = 0;
		}
		for (int coef = begIdx; coef < endIdx; ++coef) {
			for (int i = 0; i < poly2_ln; ++i) {
				int j = coef - i;
				if (j < 0) break;
				if (j >= poly1_ln) continue;
				send_arr[coef - begIdx] += poly1[j] * poly2[i];
			}
		}
		MPI_Ssend(send_arr, endIdx - begIdx, MPI_INT, 0, 123, MPI_COMM_WORLD);
		free(send_arr);
	}


	MPI_Finalize();
	free(poly1);
	free(poly2);
	return 0;
}