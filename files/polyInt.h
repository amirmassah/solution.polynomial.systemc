// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>


#ifndef POLYMOD_H
#define POLYMOD_H   
#include "systemc.h"
#include <poly.h>

SC_MODULE(ModPolyIntegral)
{
  sc_in<bool> clk;

  sc_in<double> A, B;   // Integral Bounds
  sc_in<bool> start;    // true: module starts calculating, A, B valid

  sc_out<double> Res;   // Integral Result
  sc_out<bool> finish;  // true: module finished calculating, Res valid

  // Interface to Polynomial Evaluation Module
  sc_out<double> X; // In(x)
  sc_in<double>  Y; // Out(y)

  static const int steps = 100;

  void do_polyIntegral();
  // {
  //   Res.write(polyIntegral( A.read(), B.read() )); //Y = polyIntegral(a, b)
  // }

  SC_CTOR(ModPolyIntegral)
  {
    SC_THREAD(do_polyIntegral);
        sensitive << clk.pos();
        // sensitive << A << B;
  }
};

SC_MODULE(ModPolyInt)
{
  sc_in<bool> clk;

  sc_in<double> A, B;   // Integral Bounds
  sc_in<bool> start;    // true: module starts calculating, A, B valid

  sc_out<double> Res;   // Integral Result
  sc_out<bool> finish;  // true: module finished calculating, Res valid

  //internal modules
  ModPolyEval mod_eval;
  ModPolyIntegral mod_integr;

  // internal signals (Eval <=> Integral)
  sc_signal<double> XSig; // In(x)
  sc_signal<double> YSig; // Out(y)


  SC_CTOR(ModPolyInt) : mod_eval("eval1"), mod_integr("integr")
  {
    // bind submodule for Evaluation
    mod_eval.X(XSig);       // Module Input X
    mod_eval.Y(YSig);       // Module Output Y

    // bind submodule for Integral
    mod_integr.clk(clk);
    mod_integr.A(A);
    mod_integr.B(B);
    mod_integr.start(start);
    mod_integr.Res(Res);
    mod_integr.finish(finish);
    mod_integr.X(XSig);
    mod_integr.Y(YSig);
  }
};

#endif // POLYMOD_H
