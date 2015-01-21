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
//   SVN Version       :  $Revision: 499 $
//   SVN last checkin  :  $Date: 2014-10-26 23:15:36 +0100 (Sun, 26 Oct 2014) $
//   SVN checkin by    :  $Author: barnasconi $
//   SVN Id            :  $Id: rcv_subscriber.cpp 499 2014-10-26 22:15:36Z barnasconi $
//
//----------------------------------------------------------------------

#include <systemc>
#include <uvm>

#include "rcv_subscriber.h"
#include "vip_packet.h"
#include "scoreboard.h"

using namespace uvm;
using namespace sc_core;

rcv_subscriber::rcv_subscriber( uvm_name name ) : uvm_subscriber<vip_packet>( name )
{
	std::cout << sc_time_stamp() << ": constructor " << name << std::endl;
}

void rcv_subscriber::write(const vip_packet& p)
{
  std::cout << sc_time_stamp() << ": " << name() << " received value " << p.data << std::endl;

  uvm_object* obj;
  scoreboard* sb;

  uvm::uvm_config_db<uvm_object*>::get(this, "", "sb", obj);

  sb = dynamic_cast<scoreboard*>(obj);

  sb->write_rcv(p);
}
