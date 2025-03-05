//----------------------------------------------------------------------
//   Copyright 2021 NXP B.V.
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

#include <systemc>
#include <uvm>

// simple register for demonstration purpose only

class reg_base : public sc_core::sc_object
{
public:
  reg_base(const char* nm) : sc_core::sc_object(nm) {}
  virtual void print( std::ostream& os = std::cout ) const = 0;
};


template < typename T >
class reg :
  public reg_base,
  public uvm::uvm_sc_if<T> // interface to enable backdoor access
{
public:
  reg(const char* name_) : reg_base(name_)
  {}

  reg& operator=(const T& v)
  {
    write(v);
    return *this;
  }

  reg& operator=(const long& v)
  {
    write(v);
    return *this;
  }

  reg& operator=(const reg& r)
  {
    write(r.read());
    return *this;
  }

  void write_notify()
  {
    if (sc_core::sc_get_status() == sc_core::SC_RUNNING)
      ev.notify();
  }

  bool write(const T& v, int start = -1, int stop = -1)
  {
    if ((start == -1) && (stop == -1))
    {
      r = v;
      write_notify();
      return true;
    }

    if ((stop == -1) || (start == stop))
    {
      r[start] = v;
      write_notify();
      return true;
    }

    r.range(start, stop) = v;
    write_notify();
    return true;
  }

  T read(int start = -1, int stop = -1) const
  {
    T val;

    if ((start ==- 1) && (stop == -1))
      return r;

    if ((stop == -1) || (start == stop))
    {
      val = r[start];
      return val;
    }

    val = r.range(start, stop);
    return val;
  }


  void print( ::std::ostream& os = ::std::cout ) const
  {
    os << r;
  }

  unsigned int to_uint() const
  {
    return r.to_uint();
  }

  const sc_core::sc_event& default_event() const
  {
    return ev;
  }

  const sc_core::sc_event& value_changed_event() const
  {
    return ev;
  }

private:
  T r;
  sc_core::sc_event ev;
};

inline std::ostream& operator<<( std::ostream& os, const reg_base& v )
{
  v.print( os );
  return os;
}
