// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#ifndef POLYINT_TB_H
#define POLYINT_TB_H   
#include "systemc.h"

SC_MODULE(polyInt_tb)
{
  sc_out<bool> Start;
  sc_in<bool> Finish;
  sc_in<double> Res;
  sc_out<double> A, B;
  sc_in<bool> Clk;

  double poly_eval(int poly_degree, double* poly_coeff, double x);
  void TestBench_polyInt();

  // create module
  SC_CTOR(polyInt_tb)
  {
    SC_THREAD(TestBench_polyInt);
    sensitive << Clk.pos();
  }
};

#endif // POLYINT_TB_H