//----------------------------------------------------------------------
//   Copyright 2013 Cadence Design Inc
//   Copyright 2016 NXP B.V.
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

#ifndef UVM_CORESERVICE_T_
#define UVM_CORESERVICE_T_

#include <systemc>
#include <array>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <utility>
#include <vector>

//////////////

namespace uvm {

// forward declaration of necessary classes.
class uvm_factory;
class uvm_default_factory;
class uvm_report_server;
class uvm_default_report_server;
class uvm_root;
//class uvm_visitor;
//class uvm_component_name_check_visitor;
class uvm_component;
//class uvm_tr_database;
//class uvm_text_tr_database;
class uvm_default_coreservice_t;

// Additional forward declarations for refactored global/static storage.
class uvm_object;
class uvm_packer;
class uvm_comparer;
class uvm_printer;
class uvm_table_printer;
class uvm_tree_printer;
class uvm_line_printer;
class uvm_report_message;
class uvm_status_container;
class uvm_resource_pool;
class uvm_reg_map;
template <typename T> class uvm_phase_queue;
class uvm_phase;
class uvm_domain;
class uvm_build_phase;
class uvm_connect_phase;
class uvm_end_of_elaboration_phase;
class uvm_start_of_simulation_phase;
class uvm_run_phase;
class uvm_extract_phase;
class uvm_check_phase;
class uvm_report_phase;
class uvm_final_phase;
class uvm_pre_reset_phase;
class uvm_reset_phase;
class uvm_post_reset_phase;
class uvm_pre_configure_phase;
class uvm_configure_phase;
class uvm_post_configure_phase;
class uvm_pre_main_phase;
class uvm_main_phase;
class uvm_post_main_phase;
class uvm_pre_shutdown_phase;
class uvm_shutdown_phase;
class uvm_post_shutdown_phase;
template <typename OBJ, typename CB> class uvm_callback_iter;
class uvm_report_object;
class uvm_report_catcher;
typedef uvm_callback_iter<uvm_report_object, uvm_report_catcher> uvm_report_cb_iter;
class uvm_callback;
class uvm_typeid_base;
template <typename T> class uvm_queue;
class uvm_callbacks_base;
class uvm_objection;
class uvm_objection_context_object;
class uvm_reg_block;
class uvm_reg_read_only_cbs;
class uvm_reg_write_only_cbs;
class uvm_report_catcher_data;

struct uvm_coreservice_store_base
{
  virtual ~uvm_coreservice_store_base() {}
  virtual const std::type_info& type() const = 0;
};

template <typename T>
struct uvm_coreservice_store : public uvm_coreservice_store_base
{
  template <typename... Args>
  explicit uvm_coreservice_store( Args&&... args )
    : value(std::forward<Args>(args)...)
  {
  }

  virtual const std::type_info& type() const
  {
    return typeid(T);
  }

  T value;
};

//----------------------------------------------------------------------
// Class: uvm_coreservice_t
//
// The singleton instance of uvm_coreservice_t provides a common point for all central 
// uvm services such as uvm_factory, uvm_report_server, ...
// The service class provides a static <::get> which returns an instance adhering to uvm_coreservice_t
// the rest of the set_<facility> get_<facility> pairs provide access to the internal uvm services
//
// Custom implementations of uvm_coreservice_t can be included in uvm_pkg::*
// and can selected via the define UVM_CORESERVICE_TYPE. They cannot reside in another package.
//----------------------------------------------------------------------

class uvm_coreservice_t
{
 public:

  virtual std::shared_ptr<uvm_factory> get_factory() = 0;
  virtual void set_factory( std::shared_ptr<uvm_factory> f ) = 0;

  virtual std::shared_ptr<uvm_report_server> get_report_server() = 0;
  virtual void set_report_server( std::shared_ptr<uvm_report_server> ) = 0;

//  virtual uvm_tr_database* get_default_tr_database() = 0;
//  virtual void set_default_tr_database( uvm_tr_database db ) = 0;

//  virtual void set_component_visitor( uvm_visitor<uvm_component> v ) = 0;
//  virtual uvm_visitor<uvm_component> get_component_visitor() const = 0;

  virtual uvm_root* get_root() = 0;
  
  virtual std::shared_ptr<uvm_packer> get_default_packer() = 0;
  virtual void set_default_packer(std::shared_ptr<uvm_packer>) = 0;
  

  virtual std::shared_ptr<uvm_comparer> get_default_comparer() = 0;
  virtual void set_default_comparer(std::shared_ptr<uvm_comparer>) = 0;
  

  virtual std::shared_ptr<uvm_printer> get_default_printer() = 0;
  virtual void set_default_printer(std::shared_ptr<uvm_printer>) = 0;
  
  static uvm_default_coreservice_t* get();
  
  // Implementation defined

  typedef std::map<uvm_object*, uvm_queue<uvm_callback*>*> callback_pool_map_t;
  typedef std::map<std::string, uvm_domain*> domain_map_t;
  typedef std::vector<uvm_objection*> objection_list_t;
  typedef std::vector<uvm_objection_context_object*> objection_context_list_t;
  typedef std::map<uvm_phase*, bool> phase_execution_map_t;
  typedef std::map<std::string, uvm_phase*> phase_node_map_t;
  typedef std::map<uvm_reg_block*, bool> reg_block_roots_map_t;
  typedef std::map<int, bool> recorder_handle_map_t;
  typedef std::map<std::string, bool> reg_field_policy_map_t;
  typedef std::map<uvm_typeid_base*, uvm_callbacks_base*> typeid_map_t;
  typedef std::map<uvm_callbacks_base*, uvm_typeid_base*> type_map_t;
  typedef std::array<char, 2048> regex_buffer_t;
  typedef std::map<std::string, std::unique_ptr<uvm_coreservice_store_base> > typed_store_map_t;

  // Refactored global/static accessors added after the original coreservice API.

  // Replaces the former static declaration uvmsc/base/uvm_object.h:
  // uvm_object::m_inst_count and its definition in
  // uvmsc/base/uvm_object.cpp: uvm_object::m_inst_count.
  virtual int allocate_uvm_object_m_inst_count() = 0;
  virtual int get_uvm_object_m_inst_count() = 0;

  // Replaces the former static declaration uvmsc/base/uvm_event.h:
  // uvm_event::g_cnt and its definition in uvmsc/base/uvm_event.cpp:
  // uvm_event::g_cnt.
  virtual int& get_uvm_event_g_cnt() = 0;

  // Replaces the former static declaration uvmsc/conf/uvm_resource_base.h:
  // uvm_resource_base::default_precedence and its definition in
  // uvmsc/conf/uvm_resource_base.cpp: uvm_resource_base::default_precedence.
  virtual unsigned int& get_uvm_resource_base_default_precedence() = 0;

  // Replaces the former static declaration uvmsc/factory/uvm_default_factory.h:
  // uvm_default_factory::m_debug_pass and its definition in
  // uvmsc/factory/uvm_default_factory.cpp: uvm_default_factory::m_debug_pass.
  virtual bool& get_uvm_default_factory_m_debug_pass() = 0;

  // Replaces uvmsc/policy/uvm_recorder.h / .cpp:
  // uvm_recorder::handle.
  virtual int& get_uvm_recorder_handle() = 0;
  // Replaces uvmsc/policy/uvm_recorder.h / .cpp:
  // static local variable handles in uvm_recorder::m_handles().
  virtual recorder_handle_map_t& get_uvm_recorder_m_handles() = 0;

  // Replaces uvmsc/seq/uvm_sequencer_base.h / .cpp:
  // uvm_sequencer_base::g_sequencer_id.
  virtual int& get_uvm_sequencer_base_g_sequencer_id() = 0;
  // Replaces uvmsc/seq/uvm_sequencer_base.h / .cpp:
  // uvm_sequencer_base::g_sequence_id.
  virtual int& get_uvm_sequencer_base_g_sequence_id() = 0;
  // Replaces uvmsc/seq/uvm_sequencer_base.h / .cpp:
  // uvm_sequencer_base::g_request_id.
  virtual int& get_uvm_sequencer_base_g_request_id() = 0;

  // Replaces uvmsc/reg/uvm_reg.h / .cpp:
  // uvm_reg::m_max_size.
  virtual unsigned int& get_uvm_reg_m_max_size() = 0;
  // Replaces uvmsc/reg/uvm_mem.h / .cpp:
  // uvm_mem::m_max_size.
  virtual unsigned int& get_uvm_mem_m_max_size() = 0;

  // Replaces uvmsc/reg/uvm_reg_field.h / .cpp:
  // uvm_reg_field::m_predefined.
  virtual bool& get_uvm_reg_field_m_predefined() = 0;
  // Replaces uvmsc/reg/uvm_reg_field.h / .cpp:
  // uvm_reg_field::m_max_size.
  virtual unsigned int& get_uvm_reg_field_m_max_size() = 0;
  // Replaces uvmsc/reg/uvm_reg_field.h / .cpp:
  // static local variable policy_names in uvm_reg_field::m_policy_names().
  virtual reg_field_policy_map_t& get_uvm_reg_field_m_policy_names() = 0;

  // Replaces uvmsc/reg/uvm_reg_block.h / .cpp:
  // uvm_reg_block::id.
  virtual int& get_uvm_reg_block_id() = 0;
  // Replaces uvmsc/reg/uvm_reg_block.h / .cpp:
  // uvm_reg_block::m_roots.
  virtual reg_block_roots_map_t& get_uvm_reg_block_m_roots() = 0;

  // Replaces uvmsc/cb/uvm_typeid.cpp:
  // static local variable typeid_map in uvm_typeid_base::m_access_typeid_map().
  virtual typeid_map_t& get_uvm_typeid_base_typeid_map() = 0;
  // Replaces uvmsc/cb/uvm_typeid.cpp:
  // static local variable type_map in uvm_typeid_base::m_access_type_map().
  virtual type_map_t& get_uvm_typeid_base_type_map() = 0;

  // Replaces uvmsc/reg/uvm_reg_read_only_cbs.h / .cpp:
  // uvm_reg_read_only_cbs::m_me.
  virtual uvm_reg_read_only_cbs* get_uvm_reg_read_only_cbs_m_me() = 0;
  // Replaces uvmsc/reg/uvm_reg_write_only_cbs.h / .cpp:
  // uvm_reg_write_only_cbs::m_me.
  virtual uvm_reg_write_only_cbs* get_uvm_reg_write_only_cbs_m_me() = 0;

  // Replaces uvmsc/report/uvm_report_catcher_data.h:
  // static local variable instance in uvm_report_catcher_data::get().
  virtual uvm_report_catcher_data& get_uvm_report_catcher_data_instance() = 0;

  // Replaces uvmsc/base/uvm_globals.cpp:
  // static char uvm_re[2048].
  virtual regex_buffer_t& get_uvm_globals_uvm_re() = 0;

  // Replaces uvmsc/base/uvm_object.h / .cpp:
  // uvm_object::__m_uvm_status_container.
  virtual uvm_status_container* get_uvm_object__m_uvm_status_container() = 0;
  // Replaces uvmsc/conf/uvm_resource_pool.h / .cpp:
  // uvm_resource_pool::rp.
  virtual uvm_resource_pool* get_uvm_resource_pool_rp() = 0;
  virtual void reset_uvm_resource_pool_rp() = 0;
  // Replaces uvmsc/conf/uvm_resource_pool.h / .cpp:
  // uvm_resource_pool::m_has_wildcard_names.
  virtual bool& get_uvm_resource_pool_m_has_wildcard_names() = 0;

  // Replaces uvmsc/print/uvm_printer_globals.h / .cpp:
  // uvm_default_table_printer.
  virtual std::shared_ptr<uvm_table_printer> get_uvm_default_table_printer() = 0;
  // Replaces storage for the implementation-defined default table printer.
  virtual void set_uvm_default_table_printer( std::shared_ptr<uvm_table_printer> printer ) = 0;
  // Replaces uvmsc/print/uvm_printer_globals.h / .cpp:
  // uvm_default_tree_printer.
  virtual std::shared_ptr<uvm_tree_printer> get_uvm_default_tree_printer() = 0;
  virtual void set_uvm_default_tree_printer(std::shared_ptr<uvm_tree_printer> printer ) =0 ;
  // Replaces uvmsc/print/uvm_printer_globals.h / .cpp:
  // uvm_default_line_printer.
  virtual std::shared_ptr<uvm_line_printer> get_uvm_default_line_printer() = 0;
  virtual void set_uvm_default_line_printer( std::shared_ptr<uvm_line_printer> printer ) =0 ;
  // Replaces uvmsc/phasing/uvm_phase.h / .cpp:
  // uvm_phase::m_phase_hopper.
  virtual uvm_phase_queue<uvm_phase*>* get_uvm_phase_m_phase_hopper() = 0;
  // Replaces uvmsc/phasing/uvm_phase.h / .cpp:
  // uvm_phase::m_phase_trace.
  virtual bool& get_uvm_phase_m_phase_trace() = 0;

  // Replaces uvmsc/base/uvm_root.cpp:
  // file-scope variable m_uvm_timeout_overridable.
  virtual bool& get_uvm_root_m_uvm_timeout_overridable() = 0;
  // Replaces uvmsc/base/uvm_component.cpp:
  // uvm_component::global_timeout_spawned_.
  virtual bool& get_uvm_component_global_timeout_spawned_() = 0;
  // Replaces uvmsc/base/uvm_component.cpp:
  // file-scope variable print_config_matches.
  virtual bool& get_uvm_component__print_config_matches() = 0;
  // Replaces uvmsc/conf/uvm_resource_options.h / .cpp:
  // uvm_resource_options::auditing.
  virtual bool& get_uvm_resource_options_auditing() = 0;
  // Replaces uvmsc/conf/uvm_resource_db_options.cpp:
  // file-scope variable ready.
  virtual bool& get_uvm_resource_db_options_ready() = 0;
  // Replaces uvmsc/conf/uvm_resource_db_options.cpp:
  // file-scope variable tracing.
  virtual bool& get_uvm_resource_db_options_tracing() = 0;
  // Replaces uvmsc/conf/uvm_config_db_options.cpp:
  // file-scope variable ready.
  virtual bool& get_uvm_config_db_options_ready() = 0;
  // Replaces uvmsc/conf/uvm_config_db_options.cpp:
  // file-scope variable tracing.
  virtual bool& get_uvm_config_db_options_tracing() = 0;
  // Replaces uvmsc/base/uvm_root.cpp:
  // file-scope variable m_uvm_header_done.
  virtual bool& get_uvm_root_m_uvm_header_done() = 0;
  // Replaces uvmsc/report/uvm_report_catcher.cpp:
  // function-local static variable in_catcher.
  virtual bool& get_uvm_report_catcher_in_catcher() = 0;
  // Replaces uvmsc/cb/uvm_callbacks_base.cpp:
  // uvm_callbacks_base::m_tracing.
  virtual bool& get_uvm_callbacks_base_m_tracing() = 0;

  // Replaces uvmsc/reg/uvm_reg_map.h / .cpp:
  // uvm_reg_map::m_backdoor.
  virtual uvm_reg_map* get_uvm_reg_map_m_backdoor() = 0;
  // Replaces uvmsc/phasing/uvm_domain.cpp:
  // file-scope variable m_uvm_schedule.
  virtual uvm_phase* get_uvm_domain_m_uvm_schedule() = 0;
  // Replaces uvmsc/phasing/uvm_domain.cpp:
  // file-scope variable m_common_domain.
  virtual uvm_domain* get_uvm_domain_m_common_domain() = 0;
  virtual void set_uvm_domain_m_common_domain( uvm_domain* domain ) = 0;
  // Replaces uvmsc/phasing/uvm_domain.cpp:
  // file-scope variable m_uvm_domain.
  virtual uvm_domain* get_uvm_domain_m_uvm_domain() = 0;
  virtual void set_uvm_domain_m_uvm_domain( uvm_domain* domain ) = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_build_phase::m_inst.
  virtual uvm_build_phase* get_uvm_build_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_connect_phase::m_inst.
  virtual uvm_connect_phase* get_uvm_connect_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_end_of_elaboration_phase::m_inst.
  virtual uvm_end_of_elaboration_phase* get_uvm_end_of_elaboration_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_start_of_simulation_phase::m_inst.
  virtual uvm_start_of_simulation_phase* get_uvm_start_of_simulation_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_run_phase::m_inst.
  virtual uvm_run_phase* get_uvm_run_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_extract_phase::m_inst.
  virtual uvm_extract_phase* get_uvm_extract_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_check_phase::m_inst.
  virtual uvm_check_phase* get_uvm_check_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_report_phase::m_inst.
  virtual uvm_report_phase* get_uvm_report_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_common_phases.h / .cpp:
  // uvm_final_phase::m_inst.
  virtual uvm_final_phase* get_uvm_final_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_pre_reset_phase::m_inst.
  virtual uvm_pre_reset_phase* get_uvm_pre_reset_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_reset_phase::m_inst.
  virtual uvm_reset_phase* get_uvm_reset_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_post_reset_phase::m_inst.
  virtual uvm_post_reset_phase* get_uvm_post_reset_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_pre_configure_phase::m_inst.
  virtual uvm_pre_configure_phase* get_uvm_pre_configure_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_configure_phase::m_inst.
  virtual uvm_configure_phase* get_uvm_configure_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_post_configure_phase::m_inst.
  virtual uvm_post_configure_phase* get_uvm_post_configure_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_pre_main_phase::m_inst.
  virtual uvm_pre_main_phase* get_uvm_pre_main_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_main_phase::m_inst.
  virtual uvm_main_phase* get_uvm_main_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_post_main_phase::m_inst.
  virtual uvm_post_main_phase* get_uvm_post_main_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_pre_shutdown_phase::m_inst.
  virtual uvm_pre_shutdown_phase* get_uvm_pre_shutdown_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_shutdown_phase::m_inst.
  virtual uvm_shutdown_phase* get_uvm_shutdown_phase_m_inst() = 0;
  // Replaces uvmsc/phasing/uvm_runtime_phases.h / .cpp:
  // uvm_post_shutdown_phase::m_inst.
  virtual uvm_post_shutdown_phase* get_uvm_post_shutdown_phase_m_inst() = 0;

  // Replaces uvmsc/report/uvm_report_message.h / .cpp:
  // static local variable l_report_message in uvm_report_message::new_report_message().
  virtual uvm_report_message* get_uvm_report_message_l_report_message( const std::string& name ) = 0;
  // Replaces uvmsc/report/uvm_report_catcher.cpp:
  // function-local static variable name_iter.
  virtual uvm_report_cb_iter* get_uvm_report_catcher_name_iter() = 0;
  // Replaces uvmsc/report/uvm_report_catcher.cpp:
  // function-local static variable print_iter.
  virtual uvm_report_cb_iter* get_uvm_report_catcher_print_iter() = 0;
  // Replaces uvmsc/cb/uvm_callbacks_base.h / .cpp:
  // uvm_callbacks_base::m_pool.
  virtual callback_pool_map_t& get_uvm_callbacks_base_m_pool() = 0;
  // Replaces uvmsc/cb/uvm_callbacks_base.h / .cpp:
  // uvm_callbacks_base::m_b_inst.
  virtual uvm_callbacks_base* get_uvm_callbacks_base_m_b_inst() = 0;

  // Replaces uvmsc/phasing/uvm_domain.h / .cpp:
  // static local variable domains in uvm_domain::m_domains().
  virtual domain_map_t& get_uvm_domain_domains() = 0;
  // Replaces uvmsc/phasing/uvm_objection.h / .cpp:
  // static local variable objections in uvm_objection::m_objections().
  virtual objection_list_t& get_uvm_objection_objections() = 0;
  // Replaces uvmsc/phasing/uvm_objection.h / .cpp:
  // static local variable scheduled_list in uvm_objection::m_scheduled_list().
  virtual objection_context_list_t& get_uvm_objection_scheduled_list() = 0;
  // Replaces uvmsc/phasing/uvm_objection.h / .cpp:
  // static local variable scheduled_list_changed in
  // uvm_objection::m_scheduled_list_changed().
  virtual sc_core::sc_event& get_uvm_objection_scheduled_list_changed() = 0;
  // Replaces uvmsc/phasing/uvm_phase.h / .cpp:
  // static local variable executing_phases in uvm_phase::m_executing_phases().
  virtual phase_execution_map_t& get_uvm_phase_executing_phases() = 0;
  // Replaces uvmsc/phasing/uvm_phase.h / .cpp:
  // static local variable phase_nodes in uvm_phase::m_phase_nodes().
  virtual phase_node_map_t& get_uvm_phase_phase_nodes() = 0;

  // Replaces template static data and template local statics only.
  // Exact template-backed replacements currently using this generic store:
  // - uvmsc/cb/uvm_typeid.h: uvm_typeid<T>::m_b_inst
  // - uvmsc/conf/uvm_object_string_pool.h: uvm_object_string_pool<T>::m_global_pool
  // - uvmsc/conf/uvm_queue.h: uvm_queue<T>::m_global_queue
  // - uvmsc/conf/uvm_resource.h: uvm_resource<T>::m_r2s
  // - uvmsc/conf/uvm_resource.h: uvm_resource<T>::my_type
  // - uvmsc/conf/uvm_config_db.h: uvm_config_db<T>::m_rsc
  // - uvmsc/conf/uvm_config_db.h: uvm_config_db<T>::m_waiters
  // - uvmsc/cb/uvm_typed_callbacks.h: uvm_typed_callbacks<T>::m_tw_cb_q
  // - uvmsc/cb/uvm_typed_callbacks.h: uvm_typed_callbacks<T>::m_typename
  // - uvmsc/cb/uvm_typed_callbacks.h: uvm_typed_callbacks<T>::m_t_inst
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_inst
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_typeid
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_cb_typeid
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_typename
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_cb_typename
  // - uvmsc/cb/uvm_callbacks.h: uvm_callbacks<T,CB>::m_base_inst
  // - uvmsc/cb/uvm_derived_callbacks.h: uvm_derived_callbacks<T,ST,CB>::m_d_inst
  // - uvmsc/cb/uvm_derived_callbacks.h: uvm_derived_callbacks<T,ST,CB>::m_user_inst
  // - uvmsc/cb/uvm_derived_callbacks.h: uvm_derived_callbacks<T,ST,CB>::m_super_inst
  // - uvmsc/cb/uvm_derived_callbacks.h: uvm_derived_callbacks<T,ST,CB>::m_s_typeid
  // - uvmsc/factory/uvm_component_registry.h: uvm_component_registry<T>::me
  // - uvmsc/factory/uvm_object_registry.h: uvm_object_registry<T>::me
  // - uvmsc/seq/uvm_sequencer.h: local static uvm_sequencer<REQ,RSP>::m_if
  virtual typed_store_map_t& get_typed_store() = 0;

  template <typename T, typename... Args>
  T& get_or_create_typed_store( const std::string& key, Args&&... args )
  {
    typed_store_map_t& store = get_typed_store();
    typed_store_map_t::iterator it = store.find(key);

    if (it == store.end())
    {
      std::unique_ptr<uvm_coreservice_store_base> slot(
        new uvm_coreservice_store<T>(std::forward<Args>(args)...));
      it = store.insert(std::make_pair(key, std::move(slot))).first;
    }

    if (it->second->type() != typeid(T))
      throw std::logic_error("uvm_coreservice_t typed store key reused with different type");

    return static_cast<uvm_coreservice_store<T>*>(it->second.get())->value;
  }

 protected:
  uvm_coreservice_t(){};
  virtual ~uvm_coreservice_t(){}

}; // class uvm_coreservice_t



} // namespace uvm

#endif // UVM_CORESERVICE_T_
