//----------------------------------------------------------------------
//   Copyright 2023 COSEDA Technologies GmbH
//   Copyright 2014 NXP B.V.
//   Copyright 2007-2010 Mentor Graphics Corporation
//   Copyright 2007-2011 Cadence Design Systems, Inc.
//   Copyright 2010-2011 Synopsys, Inc.
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
#include <cstring>

int pseudo_rand() {
    /* initial value */
    static unsigned int randval = 42;

    randval *= 3;
    int int_randval;
    std::memcpy(&int_randval, &randval, sizeof(int_randval));
    return (int_randval < 0)? -int_randval : int_randval;
}
