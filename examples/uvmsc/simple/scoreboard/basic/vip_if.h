//----------------------------------------------------------------------
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
//   Original Author: Martin Barnasconi, NXP Semiconductors
//   Created on: 2012-10-27
//
//----------------------------------------------------------------------
//
//   SVN Version       :  $Revision: 504 $
//   SVN last checkin  :  $Date: 2014-12-24 17:11:29 +0100 (Wed, 24 Dec 2014) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: vip_if.h 504 2014-12-24 16:11:29Z barnasconi $
//
//----------------------------------------------------------------------

// interface definitions for VIP

#ifndef VIP_IF_H_
#define VIP_IF_H_

#include <systemc>
#include <uvm>

using namespace uvm;

class vip_if
{
 public:
  sc_core::sc_signal<int> sig_data;

  vip_if() {}
};


#endif /* VIP_IF_H_ */
