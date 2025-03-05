//----------------------------------------------------------------------
//   Copyright 2007-2011 Cadence Design Systems, Inc.
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

#ifndef UVC_INTF_H_
#define UVC_INTF_H_

#include <systemc>
#include <uvm>

typedef sc_core::sc_signal<transaction> uvc_intf;

/*
struct uvc_intf : virtual public sc_core::sc_interface
{
  virtual int read() = 0;
  virtual write() = 0;
};


class uvc_channel : public uvc_intf, public sc_core::sc_module
{
public:
  virtual transaction read() { return tr; }
  virtual const sc_core::sc_event& default_event() const { return m_ev; }

  void write(transaction req) // was drive_tr
  {
    tr = req;
    m_ev.notify();
  }

private:
  transaction tr;
  sc_core::sc_event m_ev;
};
*/

#endif // UVC_INTF_H_
