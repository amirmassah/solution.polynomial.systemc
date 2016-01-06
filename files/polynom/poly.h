// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#ifndef POLY_H
#define POLY_H
#include "systemc.h"

// simple polynomial for easy debugging
// configurable degree of polynomial
const unsigned int poly_degree = 2;

// configurable coefficients (index equal to associated power of x)
const double poly_coeff[poly_degree + 1] = {
  0,
  0,
  1
};

/*
// more complex polynomial for extensive testing
// configurable degree of polynomial
const unsigned int poly_degree = 7;

// configurable coefficients (index equal to associated power of x)
const double poly_coeff[poly_degree + 1] = {
  8.34,
  20.0,
  1.64,
  -28.73,
  92.429,
  48.902,
  98.902,
  34.565
};
*/

// evaluates a polynomial in position x, returns associated y value
double polyEval(const double x);

SC_MODULE(ModPolyEval)
{

  sc_in<double> X;
  sc_out<double> Y;

  SC_CTOR(ModPolyEval)
  {
    SC_METHOD(do_polyEval);
    sensitive << X;
  }

  void do_polyEval()
  {
    Y.write( polyEval(X.read()) ); //Y = polyEval(X)
  }

  
};


#endif // POLY_H
