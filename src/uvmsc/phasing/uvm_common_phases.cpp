//----------------------------------------------------------------------
//   Copyright 2014 Fraunhofer-Gesellschaft zur Foerderung
//					der angewandten Forschung e.V.
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

#include "uvmsc/base/uvm_component.h"
#include "uvmsc/phasing/uvm_common_phases.h"

//////////////

namespace uvm {

//----------------------------------------------------------------------
// Class uvm_build_phase implementation
//----------------------------------------------------------------------

uvm_build_phase::uvm_build_phase( const std::string& name )
  : uvm_topdown_phase(name)
{}

void uvm_build_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->build_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->build_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_build_phase* uvm_build_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_build_phase();
  return m_inst;
}

const std::string uvm_build_phase::get_type_name() const
{
  return type_name;
}

uvm_build_phase* uvm_build_phase::m_inst = NULL;
const std::string uvm_build_phase::type_name = "uvm_build_phase";

//----------------------------------------------------------------------
// Class uvm_connect_phase implementation
//----------------------------------------------------------------------

uvm_connect_phase::uvm_connect_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_connect_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->connect_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->connect_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_connect_phase* uvm_connect_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_connect_phase();
  return m_inst;
}

const std::string uvm_connect_phase::get_type_name() const
{
  return type_name;
}

uvm_connect_phase* uvm_connect_phase::m_inst = NULL;
const std::string uvm_connect_phase::type_name = "uvm_connect_phase";

//----------------------------------------------------------------------
// Class uvm_end_of_elaboration_phase implementation
//----------------------------------------------------------------------

uvm_end_of_elaboration_phase::uvm_end_of_elaboration_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_end_of_elaboration_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->end_of_elaboration_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->end_of_elaboration_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_end_of_elaboration_phase* uvm_end_of_elaboration_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_end_of_elaboration_phase();
  return m_inst;
}

const std::string uvm_end_of_elaboration_phase::get_type_name() const
{
  return type_name;
}

uvm_end_of_elaboration_phase* uvm_end_of_elaboration_phase::m_inst = NULL;
const std::string uvm_end_of_elaboration_phase::type_name = "uvm_end_of_elaboration_phase";

//----------------------------------------------------------------------
// Class uvm_end_of_elaboration_phase implementation
//----------------------------------------------------------------------

uvm_start_of_simulation_phase::uvm_start_of_simulation_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_start_of_simulation_phase::exec_func( uvm_component* comp,
                                               uvm_phase* phase )
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->start_of_simulation_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->start_of_simulation_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_start_of_simulation_phase* uvm_start_of_simulation_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_start_of_simulation_phase();
  return m_inst;
}

const std::string uvm_start_of_simulation_phase::get_type_name() const
{
  return type_name;
}

uvm_start_of_simulation_phase* uvm_start_of_simulation_phase::m_inst = NULL;
const std::string uvm_start_of_simulation_phase::type_name = "uvm_start_of_simulation_phase";

//----------------------------------------------------------------------
// Class uvm_run_phase implementation
//----------------------------------------------------------------------
uvm_run_phase::uvm_run_phase( const std::string& name )
  : uvm_process_phase(name)
{}

void uvm_run_phase::exec_process(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  // At the end of the run_phase, our uvm_component
  // hierarchy might be popped in a different order than it was pushed; see
  // sc_hierarchy_scope::~sc_hierarchy_scope() in sc_object.cpp. This causes
  // errors like "corrupted sc_hierarchy_scope unwinding: current scope t1, expected scope: t1.a1.a.b1"
  // Therefore we have to disable scoped thread hierarchy creation
  // sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->run_phase(*phase);
#else
  // Disable for consistency with SystemC 3.0 release
  // comp->simcontext()->hierarchy_push( comp );
  comp->run_phase(*phase);
  // comp->simcontext()->hierarchy_pop();
#endif
}

uvm_run_phase* uvm_run_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_run_phase();
  return m_inst;
}

const std::string uvm_run_phase::get_type_name() const
{
  return type_name;
}

uvm_run_phase* uvm_run_phase::m_inst = NULL;
const std::string uvm_run_phase::type_name = "uvm_run_phase";


//----------------------------------------------------------------------
// Class uvm_extract_phase implementation
//----------------------------------------------------------------------

uvm_extract_phase::uvm_extract_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_extract_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->extract_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->extract_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_extract_phase* uvm_extract_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_extract_phase();
  return m_inst;
}

const std::string uvm_extract_phase::get_type_name() const
{
  return type_name;
}

uvm_extract_phase* uvm_extract_phase::m_inst = NULL;
const std::string uvm_extract_phase::type_name = "uvm_extract_phase";


//----------------------------------------------------------------------
// Class uvm_check_phase implementation
//----------------------------------------------------------------------

uvm_check_phase::uvm_check_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_check_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->check_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->check_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_check_phase* uvm_check_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_check_phase();
  return m_inst;
}

const std::string uvm_check_phase::get_type_name() const
{
  return type_name;
}

uvm_check_phase* uvm_check_phase::m_inst = NULL;
const std::string uvm_check_phase::type_name = "uvm_check_phase";

//----------------------------------------------------------------------
// Class uvm_report_phase implementation
//----------------------------------------------------------------------

uvm_report_phase::uvm_report_phase( const std::string& name )
  : uvm_bottomup_phase(name)
{}

void uvm_report_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->report_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->report_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_report_phase* uvm_report_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_report_phase();
  return m_inst;
}

const std::string uvm_report_phase::get_type_name() const
{
  return type_name;
}

uvm_report_phase* uvm_report_phase::m_inst = NULL;
const std::string uvm_report_phase::type_name = "uvm_report_phase";

//----------------------------------------------------------------------
// Class uvm_final_phase implementation
//----------------------------------------------------------------------

uvm_final_phase::uvm_final_phase( const std::string& name )
  : uvm_topdown_phase(name)
{}

void uvm_final_phase::exec_func(uvm_component* comp, uvm_phase* phase)
{
#if IEEE_1666_SYSTEMC >= 202301L
  sc_core::sc_hierarchy_scope scope(comp->get_hierarchy_scope());
  comp->final_phase(*phase);
#else
  comp->simcontext()->hierarchy_push( comp );
  comp->final_phase(*phase);
  comp->simcontext()->hierarchy_pop();
#endif
}

uvm_final_phase* uvm_final_phase::get()
{
  if( m_inst == NULL )
     m_inst = new uvm_final_phase();
  return m_inst;
}

const std::string uvm_final_phase::get_type_name() const
{
  return type_name;
}

uvm_final_phase* uvm_final_phase::m_inst = NULL;
const std::string uvm_final_phase::type_name = "uvm_final_phase";


} // namespace uvm
