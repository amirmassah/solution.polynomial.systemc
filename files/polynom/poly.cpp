// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#include <iostream>
#include "poly.h"

double polyEval(const double x)
{
    double y = 0; // result storage
    // classic algorithm
    double xpi = 1; // helper variable for x^i

    double tmp1, tmp2, tmp3;
    for (unsigned int i = 0; i < poly_degree+1; i++)
    {
      // y += poly_coeff[i] * xpi; xpi *= x;
      tmp1 = poly_coeff[i] * xpi;
      tmp2 = xpi * x;
      xpi = tmp2;
      tmp3 = y + tmp1;
      y = tmp3;
    }
/*
    // horner
    polyEval_summation:for(i = poly_degree; i >= 0 ; --i)
    {
      y = y * x + poly_coeff[i];
    }
*/
    return y;
}
