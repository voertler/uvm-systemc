> DISCLAIMER - THIS SOFTWARE IS IN BETA PHASE AND IS HIGHLY EXPERIMENTAL; USE
> AT YOUR OWN RISK. THIS SOFTWARE SHALL BE SOLELY USED FOR STUDY PURPOSES AND
> SHALL NOT BE USED IN ANY PRODUCTION ENVIRONMENT.

# Installation notes for UVM-SystemC

**Contents**
* Installation Notes for Linux
* Installation Notes for Windows

# Installation Notes for Linux

## System Requirements

UVM-SystemC was tested on the following Linux 64-bit platforms against SystemC
2.3.3, 2.3.4 and 3.0.0:

|      OS             |    Target     |    Compiler
| ------------------- | ------------- |  --------------
| RHEL 7.9            |    x86_64     |  gcc 9.3.0
| RHEL 8.9            |    x86_64     |  gcc 11.2.0
| RHEL 8.9            |    x86_64     |  gcc 13.2.0
| Ubuntu 18.04        |    x86_64     |  gcc 7.5.0
| Ubuntu 20.04        |    x86_64     |  gcc 9.4.0
| Ubuntu 22.04        |    x86_64     |  gcc 11.4.0
| Ubuntu 24.04        |    x86_64     |  gcc 13.2.0
| Debian 12           |    x86_64     |  gcc 12.2.0

An installation of UVM-SystemC on other, related platforms and not explictly
tested compiler combinations may be possible. Please note that C++11
compatibility is required to build UVM-SystemC. C++17 compatibility is
required to build against SystemC 3.0.0.

## Sources for Compilers and Related Tools

To build, install, and use UVM-SystemC on UNIX platforms, you need
the following tools:

1. GNU C++ compiler or Clang compiler with C++11 support.

2. GNU Make (gmake)

3. Accellera Systems Initiative SystemC reference implementation version 2.3.3,
2.3.4 or 3.0.0

GCC, Clang, and gmake are free software that you can
obtain from the following sources:

* GCC: http://www.gnu.org/software/gcc/gcc.html
* Clang: http://clang.llvm.org/
* gmake: http://www.gnu.org/software/make/make.html

The SystemC reference implementations are available under Apache License
Version 2.0 and can be obtained from the following location:

* SystemC: https://www.accellera.org/downloads/standards/systemc

> **Note:**
> Various EDA vendors natively support SystemC. Please consult your EDA vendors
> to make use of the build-in SystemC capabilities of their simulation
> framework.

## Basic UVM-SystemC Installation

To install UVM-SystemC on a Linux system, do the following steps:

1. Change to the top level directory

2. Create a temporary directory, e.g.,
```
        > mkdir objdir
```

3. Change to the temporary directory, e.g.,
```
        > cd objdir
```

4. Set the following environment variable(s); for gcc compilers on Linux:
```
        > setenv CXX g++
```
> You can also specify an absolute path to the compiler of your choice.

5. Configure the package for your system, e.g.,
(The configure script is explained below.)
```
        > ../configure
```

> While the `configure` script is running, which takes a few moments,
> it prints messages to inform you of the features it is checking.
> It also detects the platform.

> As UVM-SystemC relies on the availability of a SystemC installation
> directory, the configure script will automatically check this. In case
> the configure script cannot find SystemC, it will stop. You can specify
> the path to the SystemC installation directory as follows:
```
        > ../configure --with-systemc=/path/to/your/systemc
```
> **Note for System V users:**
> If you are using `csh` on an older version of System V, you might
> need to use the `sh ../configure` command instead of `../configure`.
> Otherwise, `csh` will attempt to `configure` itself.

> **Note:**
> As IEEE Std. 1666-2023 mandates C++17 as the baseline for SystemC
> implementations, make sure you enable the compiler flag to select C++17
> for UVM-SystemC as well, e.g.:
```
        > ../configure 'CXXFLAGS=-std=c++17'
```
> In case you want to install the package in another place than the
> top level directory, configure the package e.g. as
> follows:
```
        > ../configure --prefix=/usr/local/uvm-systemc
```
> **Note:**
> Make sure you have created the target directory before installing the
> package. Do _not_ use /usr/local as a prefix.

> See the section on the general usage of the configure script and
> `../configure --help` for more information.

> **Note:**
> If you change the configuration after having compiled the package already,
> you should run a "gmake clean" before recompiling.

6. Compile the package.
```
        > gmake
```
> **Note:**
> The explicit gmake targets "opt" and "debug", etc. have been removed in
> this package.  Use the corresponding options to the configure script
> instead.

7. Install the package.
```
        > gmake install
```

8. At this point you may wish to verify the installation by testing the
example suite.
```
        > gmake check
```

> This will compile and run the examples in the subdirectory examples.

9. You can now remove the temporary directory, e.g.,
```
        > cd ..
        > rm -rf objdir
```

> Alternatively, you can keep the temporary directory to allow
> you to:

> a) Experiment with the examples.

> b) Later uninstall the package. To clean up the temporary
   directory, enter:
```
            > gmake clean
```

> To uninstall the package, enter:
```
            > gmake uninstall
```

## Known issues

In case automake gets called during gmake and you end up with an error message
complaining about automake incompatibilities, reset the timestamps of relevant
files before step 5 of the basic installation steps above:
```
    > touch aclocal.m4 configure
    > find . -name Makefile.in -exec touch {} \;
```

## Running the Examples

The UVM-SystemC examples reside in the directory `examples`, within
the temporary directory which was used for the installation
(e.g. objdir).

Use the makefiles provided in the `examples` directory as templates
for makefiles you need for compiling your own examples. In order to
run these example, the environment variable SYSTEMC_HOME should be
set beforehand. The examples can be executed by using `make check`.

## Using the Configure Script

The `configure` shell script tries to determine the correct values for
various system-dependent variables used during compilation. It uses
these values to create a `Makefile` in each directory of the package.
It also creates one or more `.h` files containing system-dependent
definitions if needed. Then, it creates the following files:

* config.status:
    A shell script that you can run at another time to recreate the current
    configuration.
* config.cache:
    A file in which the configure test results are saved to speed up
    reconfiguration.
    Data is appended to the config.cache file.
    You can remove unwanted data.

* config.log:
    A file in which compiler output is saved. This is used to debug the
    configure script.

If you need to use other commands to successfully compile the package
on your system, please try to determine if the configure script can be used
for these commands. Then, send either a diff file or instructions about
the commands you used to the email address provided in the README file.
This information will be used to improve the installation process in
the next release.

The `configure.in` file is provided in case you want to change or regenerate
the `configure` script, for example to use a newer version of `autoconf`.
The `configure.in` file is used by the `autoconf` program to create the
`configure` script.

> **Note for developers:**
>
> In case you have changed the `configure.in` file or one of the
> `Makefile.am` files:
>
> - Use the `config/distclean` script to remove the generated `configure`
>   script, the generated `aclocal.m4` file and the generated `Makefile.in`
>   files.
>
> - Use the `config/bootstrap` script to generate the `configure` script
>   and the necessary `Makefile.in` files. This script makes use of the
>   GNU auto-tools `aclocal`, `automake`, and `autoconf`.

## Compilation and Linking Options

Some systems require compilation or linking options that the `configure`
script does not define. You can define the initial values for these
options by setting them in your environment before running the
`configure` script.

Using a Bourne-compatible shell, the command line entry might be:
```
        > CC=c89 CFLAGS=-O2 LIBS=-lposix ../configure
```

Or, on systems that have the `env` program, the command line entry might be:
```
        > env CPPFLAGS=-I/usr/local/include LDFLAGS=-s ../configure
```

## Specifying the System Type

Some features cannot be automatically determined by `configure` unless
it can detect the host type on which the package will run.
If it prints a message that it cannot determine the host type,
use the `--host=TYPE` option to define it. TYPE can either be a
short system name, such as `sun4`, or a canonical name with three fields:

> CPU-COMPANY-SYSTEM

See the `config.sub` file for details about the values of each field. If
the `config.sub` file is not included in the package, the package does not
need to know the host type.

If you are building compiler tools for cross-compiling, you can also
use the `--target=TYPE` option to select the type of system for which
the code is produced and the `--build=TYPE` option to select the type of
system on which you are compiling the package.

## Sharing Defaults

You can set the default values that `configure` scripts share by
creating a site shell script called `config.site`. This file contains the
default values for variables like `CC`, `cache_file`, and `prefix`.
The `configure` script looks for the `config.site` file in the following
search precedence:

1. PREFIX/share/config.site

2. PREFIX/etc/config.site

Alternatively, you can set the `CONFIG_SITE` environment variable to the
site script path.

> **Note:** 
> The `configure` script for some systems does not look for a site script.

## Operation Controls

The `configure` script recognizes the following options to control its
operation:

`--cache-file=FILE`
        Use and save the test results in FILE instead of
        `./config.cache`. Set FILE to `/dev/null` to disable caching
        when debugging `configure`.

`--help`
        Print a summary of `configure` options and exit.

`--quiet`
`--silent`
`-q`
        Do not print messages about checks being made.
        To suppress all normal output, redirect it to `/dev/null`.
        Error messages continue to print.

`--srcdir=DIR`
        Look for the package's source code in directory DIR.
        Typically `configure` determines the directory automatically.

`--version`
        Print the version of `autoconf` used to generate the `configure`
        script and exit.

Other options that are rarely used are available in the `configure` script.
Use the `--help` option to print a list.


# Installation Notes for Windows 11

## System Requirements

UVM-SystemC was tested on the following Windows platforms against SystemC 3.0.0:

| Platform   | VS 2019 | MinGW64 GCC 13.1 | MinGW64 Clang 16
| ---------- | ------- | ---------------- | ----------------
| Windows 11 |    x    |         x        |         x

> **Note:** SystemC 3.0.0 requires at least Visual Studio 2019 for C++17 support.

Set the following environment variable(s) under Windows:
```
  Variable: SYSTEMC_MSVC
  Value   : c:\my\path\to\systemc\msvc16

  Variable: UVM_SYSTEMC_MSVC
  Value   : c:\my\path\to\uvm-systemc\msvc16
```

## Microsoft Visual Studio C++ 2019 or later

The root directory contains two subdirectories: `msvc16` and `examples`.

The `msvc16` subdirectory `uvmsc` contains the project and workspace files to
compile the `uvm-systemc.lib` library. Double-click on the `uvm-systemc.sln`
file to launch Visual Studio C++ 2015 with the workspace file. The workspace file
will have the proper switches set to compile for Visual Studio C++ 2015.
Select `Build uvm-systemc` under the Build menu or press F7 to build
`uvm-systemc.lib`.

## Running the Examples in Microsoft Visual Studio C++

The UVM-SystemC examples reside in the directory `examples` at the
highest level of the installation.

Each examples contain the project and workspace files in the subdirectory
`msvc16`. Go to one of these examples subdirectories and double-click on
the .vcxproj file to launch Visual Studio C++ with the workspace file. The
workspace file will have the proper switches set to compile for Visual
Studio C++ 2019. Make sure the libraries and examples are all built using
the same configuration (e.g., Release/Win32). Select `Build <example>.exe`
under the Build menu or press F7 to build the example executable.

## Creating UVM-SystemC Applications in Microsoft Visual Studio C++

1. Start Visual Studio. From the Start Page select New Project and Win32
   Console Project. Type the project name and select a suitable location
   then click OK.

2. Select the Application Settings page of the Win32 Application Wizard
   and make sure the `Empty project` box is ticked. Click `Finish` to
   complete the wizard.

3. Add new/existing C++ files to the project and edit code.

4. Display the project Property Pages by selecting `Properties...` from
   the Project menu.

5. Select in Configuration to set the properties for Debug or Release
   
6. From the C/C++ tab, select the General properties and set
   `Detect 64-bit Portability Issues` to No

7. From the C/C++ tab, select the General properties and add to
   `Additional Include Directories` the path 
   `$(UVM_SYSTEMC_MSVC)\..\src;$(SYSTEMC_MSVC)\..\src;`
   
8. From the C/C++ tab, select the Code Generation and set
   `Runtime Library` to `Multi-threaded DLL (/MD)` in case of a Release 
   Configuration or `Multi-threaded Debug DLL (/MDd)` in case of a Debug 
   Configuration

9. From the C/C++ tab, select the Language properties and set
   `Enable Run-Time Type Info` to Yes (/GR)

10. From the C/C++ tab, select the Command Line properties and add /vmg
    to the `Additional Options:` box.

11. From the Linker tab, select the General properties and add to 
    `Additional Library Directories` the path 
    `$(SYSTEMC_MSVC)\SystemC\Release;$(UVM_SYSTEMC_MSVC)\uvmsc\Release;`
    
12. From the Linker tab, select the Input properties and add to 
    `Additional Dependencies` the files `systemc.lib;uvm-systemc.lib;`

13. From the Linker tab, select the System properties and set 
    `Subsystem` to `Console (/SUBSYSTEM:CONSOLE)`

14. Click OK. If necessary repeat the same steps for Configuration Debug 
    or Release

Also make sure that the Windows environment variables SYSTEMC_MSVC and
UVM_SYSTEMC_MSVC are set, see section above.
