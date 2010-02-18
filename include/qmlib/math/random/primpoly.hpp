//
/// \file
/// \brief Primitive Polynomials of Modulo Two Up To Degree 27
/// \ingroup math
//
#ifndef __PrimitivePolynomialsModuloTwoUpToDegree27_QM_H__
#define __PrimitivePolynomialsModuloTwoUpToDegree27_QM_H__
//
//
// � 2002 "Monte Carlo Methods in Finance"
//
//
// ================================================================================
// Copyright (C) 2002 "Monte Carlo Methods in Finance". All rights reserved.
//
// Permission to use, copy, modify, and distribute this software is freely granted,
// provided that this notice is preserved.
// ================================================================================
//
//
// This file is provided for the use with Sobol' sequences of higher dimensions. For the construction
// of Sobol' numbers, I recommend the algorithms published in "Numerical Recipes in C", W. H. Press,
// S. A. Teukolsky, W. t. Vetterling, B. P. Flannery, second edition, section 7.7, page 309,
// ISBN 0-521-43108-5.
//
// The dimensionality of the Sobol' sequence can be extended to virtually any size you ever might
// need by the aid of the table of primitive polynomials modulo two as provided ready for
// compilation in the directory "PrimitivePolynomialsModuloTwo" on the CD accompanying the book
// "Monte Carlo Methods in Finance" by Peter J�ckel. You should initialise them as described in
// the section "The initialisation of Sobol' numbers". Note that you should always use Sobol'
// sequences in conjunction with the Brownian Bridge.
//

//
//	PPMT : Primitive Polynomials Modulo Two
//
//
// The encoding is as follows:
//
//  The coefficients of each primitive polynomial are the bits of the given integer.
//  The leading and trailing coefficients, which are 1 for all of the polynomials,
//  have been omitted.
//
//  Example: The polynomial
//
//      4    2
//     x  + x  + 1
//
// is encoded as  2  in the array of polynomials of degree 4 because the binary sequence of coefficients
//
//   10101
//
// becomes
//
//    0101
//
// after stripping off the top bit, and this is converted to
//
//     010
//
// by right-shifting and losing the rightmost bit. Similarly, we have
//
//   5    4    2
//  x  + x  + x  + x + 1
//
// encoded as  13  [ (1)1101(1) ]  in the array for degree 5.
//
//
// 
// It is up to you to define a macro PPMT_MAX_DIM to a positive integer
// less than or equal to 8129334. If you don't define it, it will be set
// below to N_PRIMITIVES_UP_TO_DEGREE_18 which is 21200. That's how many
// primitive polynomials will be compiled into a static array. Since 8129334
// longs compile into an object file of at least 32517336 byte size (in fact,
// gcc -c -O0 PrimitivePolynomialsModuloTwoUpToDegree27.c produced a the file
// PrimitivePolynomialsModuloTwoUpToDegree27.o with 32519920 bytes), it
// is recommended to only compile as many as you may ever need. Worse even
// than the  output file size is the virtual memory requirement for the compilation,
// so really only take the maximum of what you think you might ever need.
// After all, you can always recompile with more, should you need it.
//
// Note that PPMT_MAX_DIM will be redefined to be the nearest equal or larger
// number of polynomials up to one of the predefined macros N_PRIMITIVES_UP_TO_DEGREE_01
// below.
//
//
// Example: comment out the line below if you want absolutely all of the provided
// primitive polynomials modulo two.
//
// #define PPMT_MAX_DIM 8129334
//
//

#define N_PRIMITIVES_UP_TO_DEGREE_01         1
#define N_PRIMITIVES_UP_TO_DEGREE_02         2
#define N_PRIMITIVES_UP_TO_DEGREE_03         4
#define N_PRIMITIVES_UP_TO_DEGREE_04         6
#define N_PRIMITIVES_UP_TO_DEGREE_05        12
#define N_PRIMITIVES_UP_TO_DEGREE_06        18
#define N_PRIMITIVES_UP_TO_DEGREE_07        36
#define N_PRIMITIVES_UP_TO_DEGREE_08        52
#define N_PRIMITIVES_UP_TO_DEGREE_09       100
#define N_PRIMITIVES_UP_TO_DEGREE_10       160
#define N_PRIMITIVES_UP_TO_DEGREE_11       336
#define N_PRIMITIVES_UP_TO_DEGREE_12       480
#define N_PRIMITIVES_UP_TO_DEGREE_13      1110
#define N_PRIMITIVES_UP_TO_DEGREE_14      1866
#define N_PRIMITIVES_UP_TO_DEGREE_15      3666
#define N_PRIMITIVES_UP_TO_DEGREE_16      5714
#define N_PRIMITIVES_UP_TO_DEGREE_17     13424
#define N_PRIMITIVES_UP_TO_DEGREE_18     21200
#define N_PRIMITIVES_UP_TO_DEGREE_19     48794
#define N_PRIMITIVES_UP_TO_DEGREE_20     72794
#define N_PRIMITIVES_UP_TO_DEGREE_21    157466
#define N_PRIMITIVES_UP_TO_DEGREE_22    277498
#define N_PRIMITIVES_UP_TO_DEGREE_23    634458
#define N_PRIMITIVES_UP_TO_DEGREE_24    910938
#define N_PRIMITIVES_UP_TO_DEGREE_25   2206938
#define N_PRIMITIVES_UP_TO_DEGREE_26   3926838
#define N_PRIMITIVES_UP_TO_DEGREE_27   8129334

#define N_PRIMITIVES N_PRIMITIVES_UP_TO_DEGREE_27


#ifndef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_18
#endif

#if      PPMT_MAX_DIM > N_PRIMITIVES
# error  PPMT_MAX_DIM cannot be greater than N_PRIMITIVES
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_01
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_01
# define N_MAX_DEGREE 01
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_02
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_02
# define N_MAX_DEGREE 02
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_03
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_03
# define N_MAX_DEGREE 03
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_04
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_04
# define N_MAX_DEGREE 04
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_05
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_05
# define N_MAX_DEGREE 05
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_06
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_06
# define N_MAX_DEGREE 06
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_07
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_07
# define N_MAX_DEGREE 07
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_08
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_08
# define N_MAX_DEGREE 08
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_09
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_09
# define N_MAX_DEGREE 09
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_10
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_10
# define N_MAX_DEGREE 10
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_11
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_11
# define N_MAX_DEGREE 11
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_12
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_12
# define N_MAX_DEGREE 12
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_13
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_13
# define N_MAX_DEGREE 13
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_14
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_14
# define N_MAX_DEGREE 14
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_15
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_15
# define N_MAX_DEGREE 15
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_16
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_16
# define N_MAX_DEGREE 16
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_17
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_17
# define N_MAX_DEGREE 17
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_18
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_18
# define N_MAX_DEGREE 18
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_19
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_19
# define N_MAX_DEGREE 19
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_20
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_20
# define N_MAX_DEGREE 20
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_21
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_21
# define N_MAX_DEGREE 21
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_22
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_22
# define N_MAX_DEGREE 22
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_23
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_23
# define N_MAX_DEGREE 23
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_24
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_24
# define N_MAX_DEGREE 24
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_25
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_25
# define N_MAX_DEGREE 25
#elif    PPMT_MAX_DIM <= N_PRIMITIVES_UP_TO_DEGREE_26
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_26
# define N_MAX_DEGREE 26
#else
# undef  PPMT_MAX_DIM
# define PPMT_MAX_DIM N_PRIMITIVES_UP_TO_DEGREE_27
# define N_MAX_DEGREE 27
#endif

//
// You can access the following array as in PrimitivePolynomials[i][j]
// with i and j counting from 0 in C convention. PrimitivePolynomials[i][j]
// will get you the j-th (counting from zero) primitive polynomial of degree
// i+1. Each one-dimensional array of primitive polynomials of a given
// degree is terminated with an entry of -1. Accessing beyond this entry
// will result in a memory violation and must be avoided.
//

/*
#ifdef __cplusplus

extern "C"

#endif

const long *const PrimitivePolynomials[N_MAX_DEGREE];
*/

#include <qmlib/math/random/impl/primpoly_impl.hh>

//
// Below is a test program whose output is attached beneath.
// The macro PPMT_MAX_DIM was defined to be 8129334 at the beginning of this header
// and PrimitivePolynomialsModuloTwoUpToDegree27.c was compiled separately.
// The main program below was then linked against PrimitivePolynomialsModuloTwoUpToDegree27.o.
// Be warned though, you will need a lot of virtual memory to compile PrimitivePolynomialsModuloTwoUpToDegree27.c
// when PPMT_MAX_DIM is defined as 8129334.
//
//
//      #include <stdio.h>
//
//      #include "PrimitivePolynomialsModuloTwoUpToDegree27.h"
//
//      int main (int argc, char * argv[]) {
//       unsigned long i=0,j=0,n=0;
//       long polynomial=0;
//       while (n<PPMT_MAX_DIM || polynomial!=-1) {
//         if (polynomial==-1){
//           ++i; // Increase degree index
//           j=0; // Reset index of polynomial in degree.
//         }
//         polynomial = PrimitivePolynomials[i][j];
//         if (polynomial==-1){
//           printf("There were %7lu polynomials in degree %2lu. Total number of polynomials up to (including) degree %2lu is %7lu.\n",j,i+1,i+1,n);
//           --n;
//         }
//         ++j; // Increase index of polynomial in degree.
//         ++n; // Increase overall polynomial counter.
//       }
//       return 0;
//      }
//
//
//  Output:
//
//
//      There were       1 polynomials in degree  1. Total number of polynomials up to (including) degree  1 is       1.
//      There were       1 polynomials in degree  2. Total number of polynomials up to (including) degree  2 is       2.
//      There were       2 polynomials in degree  3. Total number of polynomials up to (including) degree  3 is       4.
//      There were       2 polynomials in degree  4. Total number of polynomials up to (including) degree  4 is       6.
//      There were       6 polynomials in degree  5. Total number of polynomials up to (including) degree  5 is      12.
//      There were       6 polynomials in degree  6. Total number of polynomials up to (including) degree  6 is      18.
//      There were      18 polynomials in degree  7. Total number of polynomials up to (including) degree  7 is      36.
//      There were      16 polynomials in degree  8. Total number of polynomials up to (including) degree  8 is      52.
//      There were      48 polynomials in degree  9. Total number of polynomials up to (including) degree  9 is     100.
//      There were      60 polynomials in degree 10. Total number of polynomials up to (including) degree 10 is     160.
//      There were     176 polynomials in degree 11. Total number of polynomials up to (including) degree 11 is     336.
//      There were     144 polynomials in degree 12. Total number of polynomials up to (including) degree 12 is     480.
//      There were     630 polynomials in degree 13. Total number of polynomials up to (including) degree 13 is    1110.
//      There were     756 polynomials in degree 14. Total number of polynomials up to (including) degree 14 is    1866.
//      There were    1800 polynomials in degree 15. Total number of polynomials up to (including) degree 15 is    3666.
//      There were    2048 polynomials in degree 16. Total number of polynomials up to (including) degree 16 is    5714.
//      There were    7710 polynomials in degree 17. Total number of polynomials up to (including) degree 17 is   13424.
//      There were    7776 polynomials in degree 18. Total number of polynomials up to (including) degree 18 is   21200.
//      There were   27594 polynomials in degree 19. Total number of polynomials up to (including) degree 19 is   48794.
//      There were   24000 polynomials in degree 20. Total number of polynomials up to (including) degree 20 is   72794.
//      There were   84672 polynomials in degree 21. Total number of polynomials up to (including) degree 21 is  157466.
//      There were  120032 polynomials in degree 22. Total number of polynomials up to (including) degree 22 is  277498.
//      There were  356960 polynomials in degree 23. Total number of polynomials up to (including) degree 23 is  634458.
//      There were  276480 polynomials in degree 24. Total number of polynomials up to (including) degree 24 is  910938.
//      There were 1296000 polynomials in degree 25. Total number of polynomials up to (including) degree 25 is 2206938.
//      There were 1719900 polynomials in degree 26. Total number of polynomials up to (including) degree 26 is 3926838.
//      There were 4202496 polynomials in degree 27. Total number of polynomials up to (including) degree 27 is 8129334.
//
#endif  //  __PrimitivePolynomialsModuloTwoUpToDegree27_QM_H__
//
