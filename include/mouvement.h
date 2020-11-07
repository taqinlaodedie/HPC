#ifndef MOUVEMENT_H
#define MOUVEMENT_H

#include "nrdef.h"

void SigmaDelta_step0(uint8 **M0, uint8 **I0, uint8 **V0, int m, int n);
void SigmaDelta_1step(uint8 **M_t0, uint8 **M_t1, uint8 **I_t, int m, int n);
void SigmaDelta_2step(uint8 **O_t, uint8 **M_t, uint8 **I_t, int m, int n);
void SigmaDelta_3step(uint8 **V_t0, uint8 **V_t1, uint8 **O_t, int m, int n, int N);
void SigmaDelta_4step(uint8 **O_t, uint8 **V_t, uint8 **E_t, int m, int n);

#endif