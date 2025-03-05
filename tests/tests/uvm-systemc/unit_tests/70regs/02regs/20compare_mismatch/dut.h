//----------------------------------------------------------------------
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   All Rights Reserved Worldwide
//
//   Licensed under the Apache License, Version 2.0 (the
//   "License"); you may not use this file except in
//   compliance with the License.  You may obtain a copy of
//   the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in
//   writing, software distributed under the License is
//   distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//   CONDITIONS OF ANY KIND, either express or implied.  See
//   the License for the specific language governing
//   permissions and limitations under the License.
//----------------------------------------------------------------------

#ifndef DUT_H_
#define DUT_H_

#include <systemc>
#include <uvm>

#include "uvc_intf.h"
#include "transaction.h"

// TODO move to command line option
#define NUM_REGS 10

class dut : public sc_core::sc_module
{
public:
  sc_core::sc_in<transaction> in;

  // Dummy Registers
  sc_dt::sc_lv<32> myreg[NUM_REGS];

  SC_HAS_PROCESS(dut);

  dut( sc_core::sc_module_name name ) : sc_core::sc_module(name)
  {
    reset();
    SC_THREAD(proc);
    sensitive << in;
  }

  void reset()
  {
    for (int i = 0; i < NUM_REGS; i++)
      myreg[i]=0x12345678;
  }

  void proc()
  {
    tr = in.read();
    int addr_loc = tr.addr.to_int()/4;

    if(tr.dir == uvm::UVM_WRITE)
      myreg[addr_loc] = tr.data;
    else
      tr.data = myreg[addr_loc];
  }

 private:
  transaction tr;

};

#endif // DUT_H_
