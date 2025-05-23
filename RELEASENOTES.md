# UVM-SystemC Release Notes

July 01, 2024

## License

This library is licensed under the Apache Software Foundations Apache License, 
Version 2.0, January 2004. 
The full license is available at: http://www.apache.org/licenses/

## Disclaimer

THE CONTRIBUTORS AND THEIR LICENSORS MAKE NO WARRANTY OF ANY KIND WITH REGARD
TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

!!!!!!!!!!!!!! THIS SOFTWARE IS IN BETA PHASE AND IS HIGHLY EXPERIMENTAL; USE 
AT YOUR OWN RISK. THIS SOFTWARE SHALL BE SOLELY USED FOR STUDY PURPOSES AND 
SHALL NOT BE USED IN ANY PRODUCTION ENVIRONMENT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

## Acknowledgements

The creation of this document has been supported by the European Commission as 
part of the Seventh Framework Programme (FP7) for Research and Technological 
Development in the project 'VERIFICATION FOR HETEROGENOUS RELIABLE DESIGN AND 
INTEGRATION' (VERDI). The research leading to this result has received funding 
from the European Commission under grand agreement No 287562.

More information on the Seventh Framework Programme (FP7) and VERDI project 
can be found here:

   http://cordis.europa.eu/fp7

Special thanks to the Accellera Systems Initiative to grant authorization to 
use portions of its Universal Verification Methodology Reference Implementation
(UVM version 1.1d, March 2013) in this document.

The partners in the VERDI consortium wish to thank Cadence Design Systems Inc. 
for the initial donation of the UVM-SC Library Reference and documentation 
(UVM version 1.0, June 2011). This document has been derived from this work, 
and further enhanced and extended to make it compatible with the UVM 1.1 
standard.

## What's new in this release?

Compared to the 1.0-beta5 release, this release adds:
  - Bugfixes

Usage of "uvm.h" header is deprecated in favour of <uvm>. A preprocessor warning
is issued if used. This can be suppressed by defining "SUPPRESS_UVM_H_WARNING"
during compilation of your testbench.

## Known bugs
The simple/registers/models/aliasing test is failing in case the TODO section
from its source file tb_test.h is uncommented. This test has been literally
copied from UVM-SystemVerilog. We doubt whether this test case passes in the
UVM-SystemVerilog environment, and if it does, whether it should. See [1].

[1]: https://forums.accellera.org/topic/7400-clarification-needed-on-mix-between-bit-bash-sequence-and-single-register-write/

## Bugs and Suggestions

Please report bugs and suggestions about this library to:

  uvm-systemc-feedback@lists.accellera.org


## Library status

This library is in beta status, which means not all UVM functions are implemented
nor tested. The list below gives an overview of the UVM functionality and their 
status (T=testing, X=missing, I=incomplete). 

Base classes
    uvm_void                  T
    uvm_typed                 T
    uvm_object                T
    uvm_transaction           I
    uvm_root                  T
    uvm_port_base             I
    uvm_component             T
    uvm_event                 T
    uvm_event_callback        T
    uvm_object_globals        T
    uvm_coreservice_t         T
    uvm_default_coreservice_t T
    uvm_export_base           T
    uvm_mutex                 T
    uvm_version               T
    
Callback classes
    uvm_callback              T
    uvm_callback_iter         T
    uvm_callbacks             T
    uvm_callbacks_base        T
    uvm_derived_callbacks     T
    uvm_typed_callbacks       T
    uvm_typeid                T

Component classes
    uvm_agent                 T
    uvm_driver                T
    uvm_env                   T
    uvm_monitor               T
    uvm_scoreboard            T
    uvm_subscriber            T
    uvm_test                  T

Configuration, resource and container classes
    uvm_config_db             T
    uvm_config_db_options     T
    uvm_object_string_pool    T
    uvm_resource              T
    uvm_resource_base         T
    uvm_resource_converter    T
    uvm_resource_db           T
    uvm_resource_db_options   T
    uvm_resource_options      T
    uvm_resource_pool         T
    uvm_resource_types        T
    uvm_queue                 T
    
Data Access Policy
	uvm_get_to_lock_dap       T
	uvm_set_before_get_dap    T
	uvm_set_get_dap_base      T
	uvm_simple_lock_dap       T

DPI
	uvm_hdl                   T

Factory classes
    uvm_component_registry    T
    uvm_default_factory       T
    uvm_factory               T
    uvm_factory_override      T
    uvm_object_registry       T
    uvm_object_wrapper        T	

Macros
    uvm_defines               T
    uvm_callback_defines      T
    uvm_component_defines     T
    uvm_message_defines       T
    uvm_object_defines        T
    uvm_reg_defines           T
    uvm_sequence_defines      T
    uvm_string_defines        T

Miscellaneous classes
    uvm_scope_stack           T
    uvm_copy_map              T
    uvm_status_container      T

Phasing and synchronization classes
    uvm_bottomup_phase        T
    uvm_common_phases         T
    uvm_domain                T
    uvm_objection             T
    uvm_phase                 T
    uvm_phase_queue           T
    uvm_process               T
    uvm_process_phase         T
    uvm_runtime_phases        T
    uvm_topdown_phase         T
    uvm_heartbeat             X
    uvm_barrier               X

Policy classes
    uvm_comparer              T
    uvm_packer                T
    uvm_policy                T
    uvm_recorder              T

Printing classes
    uvm_line_printer          T
    uvm_printer               T
    uvm_printer_globals       T
    uvm_printer_knobs         T
    uvm_table_printer         T
    uvm_tree_printer          T

Register abstraction classes
    uvm_hdl_path_concat       T
    uvm_mem                   T
    uvm_mem_mam               T
    uvm_mem_mam_cfg           T
    uvm_mem_mam_policy        T
    uvm_mem_region            T
    uvm_reg                   T
    uvm_reg_adapter           T
    uvm_reg_backdoor          T
    uvm_reg_block             T
    uvm_reg_bus_op            T
    uvm_reg_cbs               T
    uvm_reg_cbs_types         T
    uvm_reg_field             T
    uvm_reg_fifo              T
    uvm_reg_file              T
    uvm_reg_frontdoor         T
    uvm_reg_indirect_data     T
    uvm_reg_indirect_ftdr_seq T
    uvm_reg_item              T
    uvm_reg_map               T
    uvm_reg_model             T
    uvm_reg_predictor         T
    uvm_reg_read_only_cbs     T
    uvm_reg_sequence          T
    uvm_reg_tlm_adapter       T
    uvm_reg_write_only_cbs    T
    uvm_vreg                  T
    uvm_vreg_cbs              T
    uvm_vreg_field            T
    uvm_vreg_field_cbs        T
      
Reporting classes
    uvm_default_report_server T
    uvm_report_catcher_data   T
    uvm_report_catcher        T
    uvm_report_handler        T
    uvm_report_message        T
    uvm_report_object         T
    uvm_report_server         T

Sequence classes
    uvm_sequence              T
    uvm_sequence_base         T
    uvm_sequence_item         T
    uvm_sequencer             T
    uvm_sequencer_base        T
    uvm_sequencer_ifs         T
    uvm_sequencer_param_base  T

TLM-1 classes
    uvm_analysis_export           T
    uvm_analysis_imp              T
    uvm_analysis_port             T
    uvm_sqr_connections           T
    uvm_blocking_put_port         T
    uvm_blocking_get_port         T
    uvm_blocking_peek_port        T
    uvm_blocking_get_peek_port    T
    uvm_nonblocking_put_port      T
    uvm_nonblocking_get_port      T
    uvm_nonblocking_peek_port     T
    uvm_nonblocking_get_peek_port T
    uvm_put_port                  T
    uvm_get_port                  T
    uvm_peek_port                 T
    uvm_get_peek_port             T
    uvm_tlm_req_rsp_channel       T
    uvm_tlm_transport_channel     X

TLM-2.0 classes                   X

Command line interface 
    uvm_cmdline_processor         X
