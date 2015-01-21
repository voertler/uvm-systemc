//----------------------------------------------------------------------
//   Copyright 2015 NXP B.V.
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
//   SVN Version       :  $Revision: 510 $
//   SVN last checkin  :  $Date: 2015-01-08 19:31:34 +0100 (Thu, 08 Jan 2015) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: uvm_name.h 510 2015-01-08 18:31:34Z barnasconi $
//
//----------------------------------------------------------------------

#ifndef UVM_NAME_H_
#define UVM_NAME_H_

#include "sysc/kernel/sc_module.h"
#include "uvmsc/base/uvm_root.h"

//////////////

namespace uvm {


//------------------------------------------------------------------------------
// Class uvm_name
//
//! UVM component name registration. Same mechanism as in SystemC sc_module_name
//! to register the parent-child relationship
//------------------------------------------------------------------------------

class uvm_name
{
public:
  uvm_name( const sc_core::sc_module_name& nm ) : m_name( nm )
  {}

  uvm_name( const char* nm ) : m_name( nm )
  {
    uvm_root::get();
  }

  sc_core::sc_module_name name()
  {
    return m_name;
  }

  operator const char* () const
  {
    return m_name;
  }

private:
  sc_core::sc_module_name m_name;
};

/////////////////////////////////////////////


} // namespace uvm

#endif /* UVM_NAME_H_ */
