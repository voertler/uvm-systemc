//----------------------------------------------------------------------
//   Copyright 2012-2020 NXP B.V.
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

#include <systemc>
#include <uvm>

#include "env.h"

int sc_main(int, char*[]) 
{  
  // https://forums.accellera.org/topic/6274-problem-with-re-directing-report-into-log-file/
  uvm::UVM_FILE default_report;
  std::unique_ptr<std::ofstream> log_file;

  // instantiate environment
  env e("env");

  // https://forums.accellera.org/topic/6274-problem-with-re-directing-report-into-log-file/
  auto m_uvm_root = uvm::uvm_root::get();
  m_uvm_root->set_report_severity_action_hier(uvm::UVM_INFO,    uvm::UVM_DISPLAY | uvm::UVM_LOG);
  m_uvm_root->set_report_severity_action_hier(uvm::UVM_WARNING, uvm::UVM_DISPLAY | uvm::UVM_COUNT | uvm::UVM_LOG);
  m_uvm_root->set_report_severity_action_hier(uvm::UVM_ERROR,   uvm::UVM_DISPLAY | uvm::UVM_COUNT | uvm::UVM_LOG);
  m_uvm_root->set_report_severity_action_hier(uvm::UVM_FATAL,   uvm::UVM_DISPLAY | uvm::UVM_EXIT  | uvm::UVM_LOG);

  log_file = std::unique_ptr<std::ofstream> (new std::ofstream("my_file.log"));
  if (log_file->is_open())
  {
      default_report = log_file.get();
      m_uvm_root->set_report_default_file_hier(default_report);
  }
  else 
  {
      UVM_ERROR("sc_main", "Unable to open my_file.log file");
  } 

  uvm::run_test();

  log_file->close();

  return 0;
}
