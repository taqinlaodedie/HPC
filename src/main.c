#include <stdio.h>
#include "test_mouvement.h"
#include "test_morpho.h"
#include "test_mouvement_SIMD.h"
#include "test_morpho_SIMD.h"

int main() {
	test_mouvement();
	test_mouvement_SIMD();
	test_morpho();
	test_morpho_SIMD();

	return 0;
}