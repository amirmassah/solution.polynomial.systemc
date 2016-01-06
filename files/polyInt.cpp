// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
//
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
//
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#include "systemc.h"
#include <poly.h>
#include "polyInt.h"

void ModPolyIntegral::do_polyIntegral()
{
  while(true) //infinite loop (sc_thread only started once)
  {
    // amount of steps for each integral calculation
    finish.write(false);

    // check start signal
    if(start.read() == true)
    {
      // initialize increment and accumulator
      double bound_low = A.read();
      double bound_high = B.read();
      double low, high = 0;
      int sign;
      
      // lower: smaller value, upper: higher value
      if(bound_low < bound_high)
      {
        low = bound_low;
        high = bound_high;
        sign = 1;
      }
      else if(bound_low > bound_high)
      {
        low = bound_high;
        high = bound_low;
        sign = -1;
      }

      double inc = ( high - low ) / steps;
      double acc = 0;

      for (double x = low; x < high; x += inc)
      {
        X.write(x);
        wait();
        // std::cout << sc_time_stamp() << " calculated Point ("<< x << ", "<< Y.read() << ")\n";
        acc += Y.read();
      }
      acc *= inc * sign;
      // return result
      Res.write(acc);
      finish.write(true);
    }//if(start)
  wait();
  }// while(true)
}// do_polyIntegral
