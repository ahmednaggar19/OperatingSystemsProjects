#ifndef THREADS_FIXED_PT_H
#define THREADS_FIXED_PT_H

/* Fixed-point new data type */
typedef int fixed_pt;

/* Radix = (2 ^ 14) */
#define F (int)(1 << 14)

/* Casts the normal integer N to fixed point representation. */
#define FIXED_PT(N) F * N

/*Floors the given fixed_pt number FP to int.*/
#define ROUND_ZERO(FP) FP / F

/*Rounds the given fixed_pt FP to the neares int.*/
#define ROUND_NEAREST(FP) FP > 0 ? (FP + F/2) / F \
                                  : (FP - F/2) / F
/*Adds two fixed_pt numbers, X and Y.*/
#define FIXED_PT_ADD(X, Y) (X + Y)

/*Adds fixed_pt number FP to  int N.*/
#define INT_ADD(FP, N) (FP + N*F)

/*Subtracts int N from fixed_pt number FP.*/
#define INT_SUB(FP, N) (FP - N*F)

/*Increments fixed_pt number X.*/
#define FIXED_PT_INCREMENT(X) INT_ADD(X, 1)

/*Subtracts two fixed_pt numbers, Y from X.*/
#define FIXED_PT_SUB(X, Y) (X - Y)

/*Multiplies two fixed_pt numbers, X and Y.*/
#define FIXED_PT_MUL(X, Y) ((int64_t)X * Y / F)

/*Multiplies fixed_pt X by int N.*/
#define INT_MUL(X, N) (X * N)

/*Divides two fixed_pt numbers, X by Y.*/
#define FIXED_PT_DIV(X, Y) ((int64_t)X * F / Y)

/*Divides fixed_pt number X by int N .*/
#define INT_DIV(X, N) (X / N)

#endif
