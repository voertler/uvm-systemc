//---------------------------------------------------------------------------
//   Copyright 2014 NXP B.V.
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
//---------------------------------------------------------------------------

#ifndef RDB_H_
#define RDB_H_

#include <systemc>
#include <uvm>

#include <string>

// Number of addrMaps = 1
// Number of regFiles = 1
// Number of registers = 10
// Number of memories = 0

//---------------------------------------------------------------------------
// Register definitions
//---------------------------------------------------------------------------

class ureg0_t : public uvm::uvm_reg
{
public:

  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  // TODO randomization
  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /* TODO constraints
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg0_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg0_t);

  ureg0_t( const std::string& name = "unnamed-ureg0_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}
};


class ureg1_t : public uvm::uvm_reg
{
public:

  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg1_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg1_t);

  ureg1_t( const std::string& name= " unnamed-ureg1_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}
};


class ureg2_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg2_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg2_t);

  ureg2_t( const std::string& name= " unnamed-ureg2_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}
};


class ureg3_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg3_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg3_t);

  ureg3_t( const std::string& name= " unnamed-ureg3_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}
};


class ureg4_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg4_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg4_t);

  ureg4_t( const std::string& name = "unnamed-ureg4_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}
};


class ureg5_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg5_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg5_t);

  ureg5_t( const std::string& name = "unnamed-ureg5_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}

};


class ureg6_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg6_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg6_t);

  ureg6_t( const std::string& name = "unnamed-ureg6_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}

};


class ureg7_t : public uvm::uvm_reg
{
public:
  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg7_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg7_t);

  ureg7_t( const std::string& name = "unnamed-ureg7_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}

};


class ureg8_t : public uvm::uvm_reg
{
public:

  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg8_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg8_t);

  ureg8_t( const std::string& name = "unnamed-ureg8_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}

};


class ureg9_t : public uvm::uvm_reg
{
public:

  /*
  typedef enum logic [1:0] {
    k0=0, k1=1, k2=2, k3=3
  } framek_enum;
  */

  /* rand */ uvm::uvm_reg_field* destination;
  /* rand */ uvm::uvm_reg_field* frame_kind;
  /* rand */ uvm::uvm_reg_field* rsvd;

  /*
  constraint frame_kind_enum {
    frame_kind.value inside { k0, k1, k2, k3 };
  }
  */

  virtual void build()
  {
    destination = uvm::uvm_reg_field::type_id::create("destination");
    destination->configure(this, 14, 0, "RW", 0, 0x0, 1, 1, 0);
    frame_kind = uvm::uvm_reg_field::type_id::create("frame_kind");
    frame_kind->configure(this, 2, 14, "RW", 0, 0x0, 1, 1, 0);
    rsvd = uvm::uvm_reg_field::type_id::create("rsvd");
    rsvd->configure(this, 16, 16, "RW", 0, 0x0, 1, 1, 0);
  }

  UVM_REGISTER_CB(ureg9_t, uvm::uvm_reg_cbs);
  UVM_OBJECT_UTILS(ureg9_t);

  ureg9_t( const std::string& name = "unnamed-ureg9_t")
  : uvm::uvm_reg(name, 32, uvm::UVM_NO_COVERAGE)
  {}

};

//---------------------------------------------------------------------------
// Register block definition
//---------------------------------------------------------------------------

class rfile0_t : public uvm::uvm_reg_block
{
public:
  /* rand */ ureg0_t* ureg0;
  /* rand */ ureg1_t* ureg1;
  /* rand */ ureg2_t* ureg2;
  /* rand */ ureg3_t* ureg3;
  /* rand */ ureg4_t* ureg4;
  /* rand */ ureg5_t* ureg5;
  /* rand */ ureg6_t* ureg6;
  /* rand */ ureg7_t* ureg7;
  /* rand */ ureg8_t* ureg8;
  /* rand */ ureg9_t* ureg9;

  virtual void build()
  {
    // Now create all registers
    ureg0 = ureg0_t::type_id::create("ureg0", NULL, get_full_name());
    ureg1 = ureg1_t::type_id::create("ureg1", NULL, get_full_name());
    ureg2 = ureg2_t::type_id::create("ureg2", NULL, get_full_name());
    ureg3 = ureg3_t::type_id::create("ureg3", NULL, get_full_name());
    ureg4 = ureg4_t::type_id::create("ureg4", NULL, get_full_name());
    ureg5 = ureg5_t::type_id::create("ureg5", NULL, get_full_name());
    ureg6 = ureg6_t::type_id::create("ureg6", NULL, get_full_name());
    ureg7 = ureg7_t::type_id::create("ureg7", NULL, get_full_name());
    ureg8 = ureg8_t::type_id::create("ureg8", NULL, get_full_name());
    ureg9 = ureg9_t::type_id::create("ureg9", NULL, get_full_name());

    // Now build the registers. Set parent and hdl_paths
    ureg0->build();
    ureg0->configure(this, NULL, "myreg[0]");
    ureg1->build();
    ureg1->configure(this, NULL, "myreg[1]");
    ureg2->build();
    ureg2->configure(this, NULL, "myreg[2]");
    ureg3->build();
    ureg3->configure(this, NULL, "myreg[3]");
    ureg4->build();
    ureg4->configure(this, NULL, "myreg[4]");
    ureg5->build();
    ureg5->configure(this, NULL, "myreg[5]");
    ureg6->build();
    ureg6->configure(this, NULL, "myreg[6]");
    ureg7->build();
    ureg7->configure(this, NULL, "myreg[7]");
    ureg8->build();
    ureg8->configure(this, NULL, "myreg[8]");
    ureg9->build();
    ureg9->configure(this, NULL, "myreg[9]");

    // Now define address mappings

    default_map = create_map("default_map", 0, 4, uvm::UVM_LITTLE_ENDIAN);
    default_map->add_reg(ureg0, 0x0, "RW");
    default_map->add_reg(ureg1, 0x4, "RW");
    default_map->add_reg(ureg2, 0x8, "RW");
    default_map->add_reg(ureg3, 0xc, "RW");
    default_map->add_reg(ureg4, 0x10, "RW");
    default_map->add_reg(ureg5, 0x14, "RW");
    default_map->add_reg(ureg6, 0x18, "RW");
    default_map->add_reg(ureg7, 0x1c, "RW");
    default_map->add_reg(ureg8, 0x20, "RW");
    default_map->add_reg(ureg9, 0x24, "RW");
    lock_model();
  }

  UVM_OBJECT_UTILS(rfile0_t);

  rfile0_t( const std::string& name = "unnamed-rfile0")
  : uvm::uvm_reg_block(name, uvm::UVM_NO_COVERAGE)
  {}

};


//---------------------------------------------------------------------------
// Address map definition
//---------------------------------------------------------------------------

class mmap0_type : public uvm::uvm_reg_block
{
public:
  /* rand */ rfile0_t* rfile0;

  void build()
  {
    // Now define address mappings
    default_map = create_map("default_map", 0, 4, uvm::UVM_LITTLE_ENDIAN);
    rfile0 = rfile0_t::type_id::create("rfile0", NULL, get_full_name());
    rfile0->build();
    rfile0->configure(this, "dut");
    default_map->add_submap(rfile0->default_map, 0x0);
    set_hdl_path_root("testm");
    lock_model();
  }

  UVM_OBJECT_UTILS(mmap0_type);

  mmap0_type( const std::string& name = "unnamed-mmap0_type")
  : uvm::uvm_reg_block(name, uvm::UVM_NO_COVERAGE)
  {}

};



#endif // RDB_H_
