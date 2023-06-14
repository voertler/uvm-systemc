//----------------------------------------------------------------------
//   Copyright 2023 COSEDA Technologies GmbH
//   Copyright 2012-2022 NXP B.V.
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

#ifndef UVM_SIMCONTEXT_H_
#define UVM_SIMCONTEXT_H_

#include "uvmsc/base/uvm_default_coreservice_t.h"
#include "uvmsc/policy/uvm_packer.h"
#include "uvmsc/base/uvm_root.h"

#include <memory>
namespace uvm {


class uvm_simcontext {
 public:
  static uvm_simcontext& get();

  uvm_simcontext(uvm_simcontext const&) = delete;          
  uvm_simcontext(uvm_simcontext&&) = delete;               
  uvm_simcontext& operator=(uvm_simcontext const&) = delete;
  uvm_simcontext& operator=(uvm_simcontext &&) = delete;    

  //--------------------------------------------------------------------------
  // member variable: uvm_component::print_config_matches
  //
  // Setting this static variable causes get_config_* to print info about
  // matching configuration settings as they are being applied.
  //
  // TODO: prefixed with underscore since we made this a method in UVM-SystemC
  //--------------------------------------------------------------------------
  bool uvm_component__print_config_matches {false};

  std::unique_ptr<uvm_default_coreservice_t> uvm_default_coreservice_t_inst;

  char uvm_globals_uvm_re[2048];

  std::unique_ptr<uvm_packer> uvm_object_uvm_packer;
  
  std::unique_ptr<uvm_root> uvm_object_uvm_root;

  bool uvm_root_m_uvm_header_lnp {false};

  bool uvm_root_m_uvm_timeout_overridable {true};

  bool uvm_callback_base_m_tracing {true};

  ~uvm_simcontext() {}
 private:
  uvm_simcontext();

  };

} // namespace uvm

#endif /* UVM_SIMCONTEXT_H_ */
