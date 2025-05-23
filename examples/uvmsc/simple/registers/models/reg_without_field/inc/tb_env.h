// 
// -------------------------------------------------------------
//    Copyright 2021 NXP B.V.
//    Copyright 2004-2011 Synopsys, Inc.
//    Copyright 2010-2011 Mentor Graphics Corporation
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

#ifndef TB_ENV_H_
#define TB_ENV_H_

#include <systemc>
#include <uvm>

#include "reg_model.h"

class reg_R_fd; /* forward declaration */

class tb_env : public uvm::uvm_env
{
    public:
        UVM_COMPONENT_UTILS(tb_env);

        block_B* regmodel{nullptr};
        reg_R_fd* fd{nullptr};

        tb_env(uvm::uvm_component_name name/*, uvm::uvm_component* parent = nullptr*/) :
            uvm::uvm_env(name/*, parent*/)
    {}
        ~tb_env();

        virtual void build_phase(uvm::uvm_phase & phase);
        virtual void connect_phase(uvm::uvm_phase & phase);
};

class reg_R_fd : public uvm::uvm_reg_frontdoor
{
    public:
        reg_R_fd(const std::string & name = "reg_R_fd") :
            uvm::uvm_reg_frontdoor(name)
            {}

        virtual void body();

    private:
        char R{0};
};

#endif /* TB_ENV_H_ */
