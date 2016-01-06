// Copyright (C) 2014 University of Kaiserslautern
// Microelectronic System Design Research Group
// 
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
// 
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#include <iostream>
#include "systemc.h"
#include <poly.h>
#include "stim_polynom.h"
#include "mon_polynom.h"

int sc_main(int argc, char* argv[])
{
  sc_signal<double> XSig, YSig;

// a clock that has a positive edge only at 10 ns 
  sc_clock TestClk("TestClock", 10, SC_NS,0.5, 10, SC_NS);

  stim_polynom Stim1("Stimulus");
  Stim1.X(XSig); 			// Module Output X
  Stim1.Clk(TestClk);		// Module Input Clock

  ModPolyEval DUT("DUT_PolyEval");
  DUT.X(XSig);				// Module Input X
  DUT.Y(YSig);				// Module Output Y

  mon_polynom Monitor1("Monitor");
  Monitor1.X(XSig);			// Module Input X
  Monitor1.Y(YSig);			// Module Input Y
  Monitor1.Clk(TestClk);	// Module Input Clock

  sc_start();  // run forever

  return 0;

}
