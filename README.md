Paraview reader for the file formats supported by SMTK.
Currently only the formats supported by SMTK CGM session (.off .cholla .brep
.occ .iges .igs .step .stp .stl) could be read.

This plugin requires SMTK. The easiest way to obtain SMTK is to build
the cmb-superbuild project from sorces (SMTK should be compiled with all
the desirable kernel types: cgm, etc.). The building was tested on Debian stable
and was passed seamlessly (if all the dependencies are preinstalled). The only
found problem is some fails of automatic downloading via curl (which can be done
manually).

Author:
Maxim Torgonskiy ( kriolog@gmail.com )

License:
This project is distributed under the OSI-approved BSD 3-clause License.
See LICENSE.txt for details.

