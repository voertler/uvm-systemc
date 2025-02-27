# UVM-SystemC regression test suite
 
For running the regression test suite please make sure that the environment variables `SYSTEMC_HOME` and `UVM_SYSTEMC_HOME` are pointing to the respective library installations.

Additionally, it is recommended to run the tests outside of the source directory.

Refer to the `verify-uvm.pl` file in the `scripts`directory for a more complete documentation on how to run the regression tests. In most cases the following example should work:

    objdir> $UVMSC_SRC_PATH/tests/scripts/verify-uvm.pl -e -v -o -std=c++17 uvm-systemc

This will provide warning and error messages (`-e`), verbose output (`-v`), shows how to pass additional compiler options (`-o ...`) and how to specify the test root within the `$UVMSC_SRC_PATH/tests` directory.
