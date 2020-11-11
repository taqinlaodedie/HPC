#ifndef MOUVEMENT_SIMD_H
#define MOUVEMENT_SIMD_H

void SigmaDelta_step0_SIMD(vuint8 **M0, vuint8 **I0, vuint8 **V0, int m, int n);
void SigmaDelta_1step_SIMD(vuint8 **M_t0, vuint8 **M_t1, vuint8 **I_t0, vuint8 **O_t0, vuint8 **V_t0, vuint8 **V_t1, vuint8 **E_t0, int m, int n);

#endif