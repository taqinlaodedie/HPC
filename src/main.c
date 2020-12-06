#include <stdio.h>
#include "test_mouvement.h"
#include "test_mouvement_SIMD.h"
#include "test_morpho.h"
#include "test_morpho_SIMD.h"

int main() {

	test_unitaire_mouvement();
	test_unitaire_morpho();
	test_unitaire_morpho_SIMD();

	test_mouvement();
	test_morpho();
	printf("\nTraitement d'image test de 576*576\n\n");
	test_mouvement_SIMD();
	test_morpho_SIMD();

	printf("\nTraitement images car_3000\n\n");
	test_multi_mouvement();
	test_multi_mouvement_SIMD();
	test_multi_morpho();
	test_multi_morpho_SIMD();
	test_morpho_SIMD_para(0);
	test_morpho_SIMD_para(1);

	return 0;
}
