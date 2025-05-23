// 
// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
//    Copyright 2010-2011 Cadence Design Systems, Inc.
//    All Rights Reserved Worldwide
// 
//    Licensed under the Apache License, Version 2.0 (the
//    "License"); you may not use this file except in
//    compliance with the License.  You may obtain a copy of
//    the License at
// 
//        http://www.apache.org/licenses/LICENSE-2.0
// 
//    Unless required by applicable law or agreed to in
//    writing, software distributed under the License is
//    distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
//    CONDITIONS OF ANY KIND, either express or implied.  See
//    the License for the specific language governing
//    permissions and limitations under the License.
// -------------------------------------------------------------
// 

#include <systemc>

#include "../inc/dut_top.h"

dut_top::dut_top(const sc_core::sc_module_name & name) :
    sc_core::sc_module(name),
    apb0(nullptr),
    dut0(nullptr),
    rst("rst") {
        dut0 = new dut<>("dut0");
        assert(dut0);
        apb0 = new apb_if("apb0");
        assert(apb0);

        dut0->pclk(apb0->pclk);
        dut0->paddr(apb0->paddr);
        dut0->psel(apb0->psel);
        dut0->penable(apb0->penable);
        dut0->pwrite(apb0->pwrite);
        dut0->prdata(apb0->prdata);
        dut0->pwdata(apb0->pwdata);
        dut0->rst(rst);

        apb0->pclk = sc_dt::SC_LOGIC_0;
        rst = sc_dt::SC_LOGIC_0;

        SC_THREAD(clk_thread);
    }

dut_top::~dut_top() {
    if (apb0) {
        delete apb0;
    }
    if (dut0) {
        delete dut0;
    }
}

void dut_top::clk_thread()
{
    while(1) {
        sc_core::wait(10, sc_core::SC_NS);
        apb0->pclk = ~(sc_dt::sc_logic(apb0->pclk));
    }
}
