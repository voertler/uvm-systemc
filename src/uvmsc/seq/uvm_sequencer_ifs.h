//----------------------------------------------------------------------
//   Copyright 2012-2019 NXP B.V.
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

#ifndef UVM_SEQUENCER_IF_H_
#define UVM_SEQUENCER_IF_H_

#include <tlm>

#include "uvmsc/base/uvm_handle.h"
#include "uvmsc/macros/uvm_defines.h"
namespace uvm {

//------------------------------------------------------------------------------
// CLASS: uvm_sqr_if_base<REQ,RSP>
//
// This class defines an interface for sequence drivers to communicate with
// sequencers. The driver requires the interface via a port, and the sequencer
// implements it and provides it via an export.
//------------------------------------------------------------------------------

template <typename REQ, typename RSP = REQ>
class uvm_sqr_if_base : public virtual sc_core::sc_interface //: public tlm::tlm_blocking_slave_if<REQ, RSP> //
{
 public:

  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual REQ get_next_item( REQ *req ) = 0;

  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual void get_next_item( REQ& req ) { req = get_next_item(nullptr); }

  virtual uvm_handle<REQ>  get_next_item( ) = 0;
  
  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual bool try_next_item( REQ& req ) = 0;

  virtual  uvm_handle<REQ> try_next_item() = 0;

  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")                                   
  virtual void item_done(const RSP& item, bool use_item = true) = 0;
  
  virtual void item_done( uvm_handle<REQ> item) = 0;
  
  virtual void item_done() = 0;

  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual void put_response( const RSP& rsp ) = 0; 

  virtual void put_response( uvm_handle<REQ> rsp ) = 0;
  
  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual REQ get( REQ *req ) = 0;
  
  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual void get( REQ& req ) { req = get(nullptr); }
  
  virtual uvm_handle<REQ>  get( ) = 0;

  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual REQ peek( REQ *req ) = 0; 
 
  UVM_DEPRECATED_1_0("Use of uvm_sequence_item& deprecated use uvm_handle<uvm_sequence_item>")
  virtual void peek( REQ& req ) { req = peek(nullptr); }   // FIXME in SystemC TLM1 this is a const method.


  virtual uvm_handle<REQ> peek() const = 0;    
  // TODO - do we need these at all?
  //virtual void stop_sequences() = 0; // TODO pure virtual or default implementation?
  //virtual void wait_for_sequences() const = 0; // TODO pure virtual or default implementation?
  //virtual bool has_do_available() = 0; // TODO pure virtual or default implementation?

  
  /////////////////////////////////////////////////////
  // Implementation-defined member functions below,
  // not part of UVM Class reference / LRM
  /////////////////////////////////////////////////////
  

  UVM_DEPRECATED_1_0("put has been deprecated, use put_response")
  virtual void put( const RSP& rsp ) = 0;
 protected: // disabled for application
  uvm_sqr_if_base(){};

 private:   // disabled for all
  uvm_sqr_if_base( const uvm_sqr_if_base& );
  uvm_sqr_if_base& operator = ( const uvm_sqr_if_base& );

};

} /* namespace uvm */

#endif /* UVM_SEQUENCER_IF_H_ */
