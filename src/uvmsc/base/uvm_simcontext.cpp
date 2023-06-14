//----------------------------------------------------------------------
//   Copyright 2023 COSEDA Technologies GmbH
//   Copyright 2012-2022 NXP B.V.
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
#include "uvm_simcontext.h"
using namespace uvm;
uvm_simcontext &uvm_simcontext::get()
{
    static uvm_simcontext instance;
    // Return a reference to our instance.
    return instance;
  
}

uvm_simcontext::uvm_simcontext() 
{

}