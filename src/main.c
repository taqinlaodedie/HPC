#include <stdio.h>
#include <time.h>
#include "test_mouvement.h"
#include "test_morpho.h"
#include "test_mouvement_SIMD.h"
#include "mymacro.h"

int main() {
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();
	// test_mouvement_SIMD();
	test_mouvement();
	// test_morpho();
	end_t = clock();
	total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("Temps total : %f\n", total_t);

	return 0;
}
