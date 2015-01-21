//----------------------------------------------------------------------
//   Copyright 2009 Cadence Design Systems, Inc.
//   Copyright 2012-2014 NXP B.V.
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
//   SVN Version       :  $Revision: 477 $
//   SVN last checkin  :  $Date: 2014-07-06 17:47:13 +0200 (Sun, 06 Jul 2014) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: uvm_void.h 477 2014-07-06 15:47:13Z barnasconi $
//
//----------------------------------------------------------------------

#ifndef UVM_VOID_H_
#define UVM_VOID_H_

namespace uvm {

//------------------------------------------------------------------------------
// CLASS: uvm_void
//
// !Empty root class, base of everything
//------------------------------------------------------------------------------

class uvm_void
{
 public:
  uvm_void() {};
  virtual ~uvm_void() {};
};

} // namespace uvm

#endif /* UVM_VOID_H_ */
