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
//   Created on: 2012-07-20
//
//----------------------------------------------------------------------
//
//   SVN Version       :  $Revision: 492 $
//   SVN last checkin  :  $Date: 2014-08-25 16:46:07 +0200 (Mon, 25 Aug 2014) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: sc_main.cpp 492 2014-08-25 14:46:07Z barnasconi $
//
//----------------------------------------------------------------------

#include <systemc>
#include <uvm>

#include "env.h"

int sc_main(int, char*[]) 
{  
  // instantiate environment
  env e("env");

  uvm::run_test();

  return 0;
}
