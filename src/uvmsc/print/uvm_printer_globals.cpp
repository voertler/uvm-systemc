//----------------------------------------------------------------------
//   Copyright 2012-2014 NXP B.V.
//   Copyright 2007-2011 Mentor Graphics Corporation
//   Copyright 2007-2010 Cadence Design Systems, Inc.
//   Copyright 2010 Synopsys, Inc.
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

#include "uvmsc/print/uvm_printer_globals.h"
#include "uvmsc/base/uvm_coreservice_t.h"
#include "uvmsc/base/uvm_default_coreservice_t.h"

namespace uvm {

//----------------------------------------------------------------------
// Group: Default printers
//----------------------------------------------------------------------

//----------------------------------------------------------------------
// Member variable: uvm_default_table_printer
//
//! The table printer is a global object that can be used with
//! uvm_object::do_print to get tabular style printing.
//----------------------------------------------------------------------

uvm_table_printer* uvm_get_default_table_printer()
{
  return uvm_coreservice_t::get()->get_uvm_default_table_printer();
}

//----------------------------------------------------------------------
// Member variable: uvm_default_printer
//
//! The default printer policy. Used when calls to uvm_object::print
//! or uvm_object::sprint do not specify a printer policy.
//!
//! The default printer may be set to any legal #uvm_printer derived type,
//! including the global line, tree, and table printers described above.
//----------------------------------------------------------------------

uvm_printer* uvm_get_default_printer()
{
  return uvm_coreservice_t::get()->get_uvm_default_printer();
}

uvm_printer*& uvm_default_printer_ref()
{
  return uvm_coreservice_t::get()->get_uvm_default_printer_ref();
}

void uvm_set_default_printer( uvm_printer* printer )
{
  uvm_coreservice_t::get()->set_uvm_default_printer(printer);
}

//----------------------------------------------------------------------
// Member variable: uvm_default_tree_printer
//
//! The tree printer is a global object that can be used with
//! uvm_object::do_print to get multi-line tree style printing.
//----------------------------------------------------------------------

uvm_tree_printer* uvm_get_default_tree_printer()
{
  return uvm_coreservice_t::get()->get_uvm_default_tree_printer();
}

//----------------------------------------------------------------------
// Member variable: uvm_default_line_printer
//
//! The line printer is a global object that can be used with
//! uvm_object::do_print to get single-line style printing.
//----------------------------------------------------------------------

uvm_line_printer* uvm_get_default_line_printer()
{
  return uvm_coreservice_t::get()->get_uvm_default_line_printer();
}


} /* namespace uvm */
