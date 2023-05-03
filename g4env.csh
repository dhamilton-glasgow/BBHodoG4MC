#!/bin/tcsh                                                                                                                                                                                                                                                                      

cd /site/12gev_phys/2.3/Linux_CentOS7.9.2009-x86_64-gcc4.8.5/geant4/4.10.04.p02/bin/
source /site/12gev_phys/2.3/Linux_CentOS7.9.2009-x86_64-gcc4.8.5/geant4/4.10.04.p02/bin/geant4.csh
cd -

setenv QTDIR /site/12gev_phys/2.3/Linux_CentOS7.2.1511-x86_64-gcc4.8.5/qt/5.10.1/gcc_64/
setenv QTINC $QTDIR/include
setenv QTLIB $QTDIR/lib
setenv PATH $QTDIR/bin:"$PATH"
setenv LD_LIBRARY_PATH "$LD_LIBRARY_PATH":$QTDIR/lib


