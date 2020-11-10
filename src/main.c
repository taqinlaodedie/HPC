#include <stdio.h>
#include "test_mouvement.h"
#include "test_morpho.h"
#include "test_mouvement_SIMD.h"

int main() {
	test_mouvement_SIMD();
	test_mouvement();
	test_morpho();

	return 0;
}