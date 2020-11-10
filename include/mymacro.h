#ifndef MYMACRO_H
#define MYMACRO_H

#define HAUT	239
#define LARG	319

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

#define SIGMADELTA(Iprec,Iact,Mprec,Mact,Oact,Vprec,Vact,Eact,cte) SigmaDelta_0step(Mprec,Iprec,Vprec,HAUT,LARG);SigmaDelta_1step(Mact,Mprec,Iact,HAUT,LARG);SigmaDelta_2step(Oact,Mact,Iact,HAUT,LARG);SigmaDelta_3step(Vact,Vprec,Oact,HAUT,LARG,cte);SigmaDelta_4step(Oact,Vprec,Eact,HAUT,LARG)
#define COPIER_MATRICES(src,dst) copy_ui8matrix_ui8matrix(src, 0, HAUT, 0, LARG, dst)
#define SIGMADELTA_SIMD(Iprec,Iact,Mprec,Mact,Oact,Vprec,Vact,Eact) SigmaDelta_0step_SIMD(Mprec,Iprec,Vprec,HAUT,LARG);SigmaDelta_1step_SIMD(Mact,Mprec,Iact,HAUT,LARG);SigmaDelta_2step_SIMD(Oact,Mact,Iact,HAUT,LARG);SigmaDelta_3step_SIMD(Vact,Vprec,Oact,HAUT,LARG);SigmaDelta_4step_SIMD(Oact,Vprec,Eact,HAUT,LARG)
#define COPIER_MATRICES_SIMD(src,dst) copy_vui8matrix_vui8matrix(src, 0, HAUT, 0, LARG, dst)

#endif
