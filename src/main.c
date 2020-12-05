#include <stdio.h>
#include "test_mouvement.h"
#include "test_mouvement_SIMD.h"
#include "test_morpho.h"
#include "test_morpho_SIMD.h"

int main() {

	test_unitaire_morpho();
	test_unitaire_morpho_SIMD();

	test_mouvement();
	test_mouvement_SIMD();
	test_morpho();
	test_morpho_SIMD();

	test_multi_mouvement();
	test_multi_mouvement_SIMD();
	test_multi_morpho();
	test_multi_morpho_SIMD();

	return 0;
}
