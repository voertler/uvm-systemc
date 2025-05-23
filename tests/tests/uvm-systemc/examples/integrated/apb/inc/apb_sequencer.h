// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010 Mentor Graphics Corporation
//    Copyright 2010 Cadence Design Systems, Inc.
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

#ifndef APB_SEQUENCER_H_
#define APB_SEQUENCER_H_

#include <systemc>
#include <uvm>

#include "apb_rw.h"

class apb_sequencer : public uvm::uvm_sequencer<apb_rw>
{
    public:
        UVM_COMPONENT_UTILS(apb_sequencer);

        apb_sequencer(uvm::uvm_component_name name) :
            uvm::uvm_sequencer<apb_rw>(name) {}
};


#endif /* APB_SEQUENCER_H_ */
