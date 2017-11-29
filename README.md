--------------------------    README    --------------------------

I. Monte Carlo computation of statistical moments
------------------------------------------------------------------

This program can be used to compute statistical moments of a
function. The moments are computed using a Monte Carlo method.

II. Compiling
------------------------------------------------------------------

The program makes use of a lua library. If Lua is installed on the
computer, proceed to the "project building" section. If Lua is not
installed, proceed to the "Lua library building" section.


II. a) Lua library building
---------------------------------
– Get in the /pcsc_montercalo/lua directory in the terminal.
– Run the command "make xxx" where xxx is your platform :
  aix bsd c89 freebsd generic linux macosx mingw posix solaris
– Run the command "make install"
– To compile the program, proceed to the "Project building"
  section

II. b) Project building
---------------------------------
- Get in the /pcsc_montercarlo directory in the terminal.
– Generate the Makefile with CMake command : "ccmake ."
– Compile the main program with "make MCMoment_Calculator"
– Compile the test suite with "make Test_Suite"
– The program binary is inside the "/bin" folder
- The test suite binary is inside the "/Test_Suite" folder.


III. Configuration
------------------------------------------------------------------

The program execution requires a configuration file. It consists
in a list of parameter values specified inside "" delimiters.
-- ALL parameters must be specified (even if unused in the
simulation).
-- The parameters order must NOT CHANGE.
See Standard_Config.dat for an example and parameters values


To evaluate the moments of a continuous function, the function must be
given in a Lua file. See Template_Lua_Function.lua for more details.

To evaluate the moments of a discrete function, the function must be given
in a CSV file.


IV. Authors
------------------------------------------------------------------

Clément Lefebvre : clement.lefebvre@epfl.ch
Vincent Pollet   : vincent.pollet@epfl.ch