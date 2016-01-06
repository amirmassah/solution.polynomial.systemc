// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#include "systemc.h"
#include "polyInt_tb.h"
#include <poly.h>


double polyInt_tb::poly_eval(int poly_degree, double* poly_coeff, double x)
  {
    int i;
    double res = 0.0;
   
    for(i=poly_degree; i >= 0; i--)
    {
      res = res * x + poly_coeff[i];
    }
    return res;
  }// source: http://rosettacode.org/wiki/Horner%27s_rule_for_polynomial_evaluation#C

void polyInt_tb::TestBench_polyInt()
{
  // Test with moving Window Pattern: move the integration window from begin to end
  //define Test Parameters
  double begin= -3;
  double end = 3;
  double length = 3;
  int count = 3;

  // generate array of integral bounds
   double a_test, b_test;

   // Calculate Antiderivative Polynomial
   double integr_poly[poly_degree+2];
   integr_poly[0] = 1;
   for(unsigned int i=1; i<poly_degree+2; i++)
   {
     integr_poly[i] = poly_coeff[i-1]/i;
   }

   std::cout << sc_time_stamp() << " Starting Test\n\n";

  // forward direction
  for(int i=0; i<count; i++)
  {
    a_test = begin + i * (end-begin-length)/count;
    b_test = a_test + length;
    A.write(a_test);
    B.write(b_test);

    std::cout << sc_time_stamp() << " Input set: " << a_test << " to " << b_test << "\n";
    
    // send start signal for 1 clock cycle
    Start.write(true);
    wait();
    Start.write(false);

    // wait for module to finish
    while(Finish.read() != true)
      wait();

    double res_var = Res.read();

    // evaluate result
    double correct =
      poly_eval(poly_degree+1, integr_poly, b_test) -
      poly_eval(poly_degree+1, integr_poly, a_test);

    // calculate relative error
    double rel_err = (res_var - correct) / correct;

    // feedback message
    cout 
      // << "Integral in range " << a_test << " to " << b_test << std::endl
      << ", Calculated Result: " << res_var << std::endl
      << ", Correct Result: " << correct    << std::endl
      << ", Relative Error: " << (rel_err)  << std::endl 
      << " after " << sc_time_stamp()       << std::endl << std::endl;
    ;

  }
  // backward direction
  for(int i=0; i<count; i++)
  {
    a_test = begin + (count - i) * (end-begin-length)/count;
    b_test = a_test - length;
    A.write(a_test);
    B.write(b_test);

    // send start signal for 1 clock cycle
    Start.write(true);
    wait();
    Start.write(false);
    
    std::cout << sc_time_stamp() << " Input set: " << a_test << " to " << b_test << "\n";

    while(Finish.read() != true)
      wait();

    double res_var = Res.read();

    // evaluate result
    double correct =
      poly_eval(poly_degree+1, integr_poly, b_test) -
      poly_eval(poly_degree+1, integr_poly, a_test);

    // calculate relative error
    double rel_err = (res_var - correct) / correct;

    // feedback message
    cout 
      // << "Integral in range " << a_test << " to " << b_test << std::endl
      << ", Calculated Result: " << res_var << std::endl
      << ", Correct Result: " << correct    << std::endl
      << ", Relative Error: " << (rel_err)  << std::endl 
      << " after " << sc_time_stamp()       << std::endl << std::endl;
    ;
  }
  sc_stop();
}