//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
//   Copyright 2009 Cadence Design Systems, Inc.
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

//----------------------------------------------------------------------
// test realtobits and bits to realconversion
// no data (bits) should be lost in the transformations
//----------------------------------------------------------------------

#include <systemc>
#include <uvm>

int sc_main(int, char*[])
{
  std::cout << "test started" << std::endl;
  unsigned long long in = 7; //0x7fffffffffffffff; // 0xffffffffffffffff;

  sc_dt::sc_uint<64> uint_in = in;

  std::cout << "in: 0x" << std::hex << in << std::endl;
  std::cout << "uint_in: 0x" << std::hex << uint_in << std::endl;

  double d = uvm::uvm_bitstoreal(uint_in);
  std::cout.precision(std::numeric_limits<double>::digits10 + 1);
  std::cout << "d: " << d << std::endl;

  sc_dt::sc_uint<64> uint_out = uvm::uvm_realtobits(d);
  std::cout << "uint_out: 0x" << std::hex << uint_out << std::endl;

  std::cout << "test ended" << std::endl;

  return 0;
}
