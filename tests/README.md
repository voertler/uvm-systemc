# UVM-SystemC regression test suite
 
Refer to the `verify-uvm.pl` file in the `scripts`directory for a more complete documentation on how to run the regression tests. In most cases the following example should work:

It is recommended to call the script from outside the source directory.

This will provide warning and error messages (`-e`), verbose output (`-v`), shows how to pass additional compiler options (`-o ...`) and how to specify the test root within the `$UVMSC_SRC_PATH/tests` directory.

    objdir> $UVMSC_SRC_PATH/tests/scripts/verify-uvm.pl -e -v -o -std=c++17 uvm-systemc

