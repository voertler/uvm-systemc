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
//
//   SVN Version       :  $Revision: 494 $
//   SVN last checkin  :  $Date: 2014-09-02 12:07:50 +0200 (Tue, 02 Sep 2014) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: uvm_domain.cpp 494 2014-09-02 10:07:50Z barnasconi $
//
//----------------------------------------------------------------------

#include "uvmsc/phasing/uvm_domain.h"
#include "uvmsc/base/uvm_object_globals.h"
#include "uvmsc/base/uvm_globals.h"
#include "uvmsc/phasing/uvm_topdown_phase.h"
#include "uvmsc/phasing/uvm_common_phases.h"
#include "uvmsc/phasing/uvm_runtime_phases.h"
#include "uvmsc/conf/uvm_config_db.h"

//////////////

namespace uvm {

//------------------------------------------------------------------------------
// Initialization of static data members
//------------------------------------------------------------------------------

uvm_phase* uvm_domain::m_uvm_schedule = NULL;
uvm_domain* uvm_domain::m_uvm_domain = NULL;
uvm_domain* uvm_domain::m_common_domain = NULL;

//------------------------------------------------------------------------------
// Constructor: uvm_domain
//------------------------------------------------------------------------------
uvm_domain::uvm_domain( const std::string& name )
  : uvm_phase(name, UVM_PHASE_DOMAIN)
{
  if (m_domains().find(name) != m_domains().end())
  {
    std::ostringstream str;
    str << "Domain created with non-unique name '" << name << "'.";
    uvm_report_error("UNIQDOMNAM", str.str());
  }
  m_domains()[name] = this;
}

//------------------------------------------------------------------------------
// member function: get_domains
//
//! Returns a list of all domains.
//------------------------------------------------------------------------------

void uvm_domain::get_domains( domains_mapT& domains )
{
  domains = m_domains();
}

//------------------------------------------------------------------------------
// member function: get_uvm_schedule
//
//! Get the "UVM" schedule, which consists of the run-time phases that
//! all components execute when participating in the "UVM" domain.
//------------------------------------------------------------------------------

uvm_phase* uvm_domain::get_uvm_schedule()
{
  get_uvm_domain();
  return m_uvm_schedule;
}

//------------------------------------------------------------------------------
// member function: get_common_domain
//
//! Get the "common" domain, which consists of the common phases that
//! all components execute in sync with each other. Phases in the "common"
//! domain are build, connect, end_of_elaboration, start_of_simulation, run,
//! extract, check, report, and final.
//------------------------------------------------------------------------------

uvm_domain* uvm_domain::get_common_domain()
{
  uvm_domain* domain = NULL;

  if (m_common_domain != NULL)
    return m_common_domain;

  domain = new uvm_domain("common");
  domain->add(uvm_build_phase::get());
  domain->add(uvm_connect_phase::get());
  domain->add(uvm_end_of_elaboration_phase::get());
  domain->add(uvm_start_of_simulation_phase::get());
  domain->add(uvm_run_phase::get());
  domain->add(uvm_extract_phase::get());
  domain->add(uvm_check_phase::get());
  domain->add(uvm_report_phase::get());
  domain->add(uvm_final_phase::get());
  m_domains()[domain->get_name()] = domain;

  /*
  // for backward compatibility, make common phases visible;
  // same as uvm_<name>_phase::get().
  build_ph               = domain.find(uvm_build_phase::get());
  connect_ph             = domain.find(uvm_connect_phase::get());
  end_of_elaboration_ph  = domain.find(uvm_end_of_elaboration_phase::get());
  start_of_simulation_ph = domain.find(uvm_start_of_simulation_phase::get());
  run_ph                 = domain.find(uvm_run_phase::get());
  extract_ph             = domain.find(uvm_extract_phase::get());
  check_ph               = domain.find(uvm_check_phase::get());
  report_ph              = domain.find(uvm_report_phase::get());
  */

  m_common_domain = domain; // common phases

  bool runtime_phasing = true; // default enabled
  uvm_config_db<bool>::get(0, "", "runtime_phasing", runtime_phasing);
  if (runtime_phasing==true)
  {
    domain = get_uvm_domain(); // get uvm.uvm_sched.<runtimephases>
    m_common_domain->add(domain, // add runtime phases to common domain
       m_common_domain->find(uvm_run_phase::get()) ); // with_phase
  }

  return m_common_domain;
}

//------------------------------------------------------------------------------
// member function: add_uvm_phases
//
//! Appends to the given \p schedule the built-in UVM runtime phases.
//------------------------------------------------------------------------------

void uvm_domain::add_uvm_phases( uvm_phase* schedule )
{
  schedule->add(uvm_pre_reset_phase::get());
  schedule->add(uvm_reset_phase::get());
  schedule->add(uvm_post_reset_phase::get());
  schedule->add(uvm_pre_configure_phase::get());
  schedule->add(uvm_configure_phase::get());
  schedule->add(uvm_post_configure_phase::get());
  schedule->add(uvm_pre_main_phase::get());
  schedule->add(uvm_main_phase::get());
  schedule->add(uvm_post_main_phase::get());
  schedule->add(uvm_pre_shutdown_phase::get());
  schedule->add(uvm_shutdown_phase::get());
  schedule->add(uvm_post_shutdown_phase::get());
}

//------------------------------------------------------------------------------
// member function: get_uvm_domain
//
//! Get a handle to the singleton UVM domain
//------------------------------------------------------------------------------

uvm_domain* uvm_domain::get_uvm_domain()
{
  if (m_uvm_domain == NULL)
  {
    m_uvm_domain = new uvm_domain("uvm");
    m_domains()[m_uvm_domain->get_name()] = m_uvm_domain;
    m_uvm_schedule = new uvm_phase("uvm_sched", UVM_PHASE_SCHEDULE);
    add_uvm_phases(m_uvm_schedule);
    m_uvm_domain->add(m_uvm_schedule);
  }
  return m_uvm_domain;
}


////////////////////////////////////////////////////////////////////////
//////// Implementation-defined member functions start here ////////////
////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------
// member function: m_domains
//
//! Implementation defined
//! Explicit static initialization
//------------------------------------------------------------------------------

uvm_domain::domains_mapT& uvm_domain::m_domains()
{
  static domains_mapT map;
  return map;
}


//------------------------------------------------------------------------------
// member function: jump
//
//! Implementation defined
//! Jumps all active phases of this domain to to-phase if
//! there is a path between active-phase and to-phase
//------------------------------------------------------------------------------

void uvm_domain::jump( const uvm_phase* phase )
{
  std::vector<uvm_phase*> phases;
  std::vector<uvm_phase*> active_phases;

  m_get_transitive_children(phases);

  // filter on active phases
  for (unsigned int i=0; i< phases.size(); i++)
    if ((phases[i]->get_state() >= UVM_PHASE_STARTED) && (phases[i]->get_state() <= UVM_PHASE_CLEANUP))
      active_phases.push_back(phases[i]);


  for(unsigned int i=0; i < active_phases.size(); i++)
    if(phases[i]->is_before(phase) || phases[i]->is_after(phase))
      phases[i]->jump(phase);
}

} // namespace uvm
