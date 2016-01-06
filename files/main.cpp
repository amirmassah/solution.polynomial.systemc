// Copyright (C) 2015 University of Kaiserslautern
// Microelectronic System Design Research Group
// 
// This file is part of the FPGAHS Course
// de.uni-kl.eit.course.fpgahs
// 
// Matthias Jung <jungma@eit.uni-kl.de>
// Christian De Schryver <schryver@eit.uni-kl.de>
// Markus Steffes <steffesm@rhrk.uni-kl.de>

#include "polyInt.h"
#include "polyInt_tb.h"

using namespace std;


int sc_main(int argc, char* argv[])
{
  sc_signal<double> ASig, BSig, ResSig;
  sc_signal<bool> StartSig, FinishSig;

// a clock that has a positive edge only at 10 ns 
  sc_clock TestClk("TestClock", 10, SC_NS,0.5, 10, SC_NS);

  polyInt_tb TB1("Testbench");
  TB1.Start(StartSig);
  TB1.Finish(FinishSig);
  TB1.A(ASig);      // Module Output A
  TB1.B(BSig);      // Module Output B
  TB1.Res(ResSig);
  TB1.Clk(TestClk); // Module Input Clock

  ModPolyInt DUT("DUT_PolyIntegral");
  DUT.clk(TestClk);
  DUT.start(StartSig);
  DUT.finish(FinishSig);
  DUT.A(ASig);        // Module Input A
  DUT.B(BSig);        // Module Input B
  DUT.Res(ResSig);    // Module Output Res

  sc_start();  // run forever

  return 0;

}