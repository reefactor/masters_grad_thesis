# Microsoft Developer Studio Generated NMAKE File, Based on XGaloisLib.dsp
!IF "$(CFG)" == ""
CFG=XGaloisLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to XGaloisLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "XGaloisLib - Win32 Release" && "$(CFG)" != "XGaloisLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XGaloisLib.mak" CFG="XGaloisLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XGaloisLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XGaloisLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "XGaloisLib - Win32 Release"

OUTDIR=.\out
INTDIR=.\out
# Begin Custom Macros
OutDir=.\out
# End Custom Macros

ALL : "$(OUTDIR)\XGaloisLib.lib"


CLEAN :
	-@erase "$(INTDIR)\GF2m.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XGaloisLib.obj"
	-@erase "$(INTDIR)\XGaloisMathCore_i386.obj"
	-@erase "$(OUTDIR)\XGaloisLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /ML /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XGaloisLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\XGaloisLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\GF2m.obj" \
	"$(INTDIR)\XGaloisLib.obj" \
	"$(INTDIR)\XGaloisMathCore_i386.obj"

"$(OUTDIR)\XGaloisLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "XGaloisLib - Win32 Debug"

OUTDIR=.\out
INTDIR=.\out
# Begin Custom Macros
OutDir=.\out
# End Custom Macros

ALL : "$(OUTDIR)\XGaloisLib.lib" "$(OUTDIR)\XGaloisLib.bsc"


CLEAN :
	-@erase "$(INTDIR)\GF2m.obj"
	-@erase "$(INTDIR)\GF2m.sbr"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XGaloisLib.obj"
	-@erase "$(INTDIR)\XGaloisLib.sbr"
	-@erase "$(INTDIR)\XGaloisMathCore_i386.obj"
	-@erase "$(INTDIR)\XGaloisMathCore_i386.sbr"
	-@erase "$(OUTDIR)\XGaloisLib.bsc"
	-@erase "$(OUTDIR)\XGaloisLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\XGaloisLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XGaloisLib.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\GF2m.sbr" \
	"$(INTDIR)\XGaloisLib.sbr" \
	"$(INTDIR)\XGaloisMathCore_i386.sbr"

"$(OUTDIR)\XGaloisLib.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\XGaloisLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\GF2m.obj" \
	"$(INTDIR)\XGaloisLib.obj" \
	"$(INTDIR)\XGaloisMathCore_i386.obj"

"$(OUTDIR)\XGaloisLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("XGaloisLib.dep")
!INCLUDE "XGaloisLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "XGaloisLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "XGaloisLib - Win32 Release" || "$(CFG)" == "XGaloisLib - Win32 Debug"
SOURCE=.\GF2m.cpp

!IF  "$(CFG)" == "XGaloisLib - Win32 Release"


"$(INTDIR)\GF2m.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XGaloisLib - Win32 Debug"


"$(INTDIR)\GF2m.obj"	"$(INTDIR)\GF2m.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\XGaloisLib.cpp

!IF  "$(CFG)" == "XGaloisLib - Win32 Release"


"$(INTDIR)\XGaloisLib.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XGaloisLib - Win32 Debug"


"$(INTDIR)\XGaloisLib.obj"	"$(INTDIR)\XGaloisLib.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 

SOURCE=.\XGaloisMathCore_i386.cpp

!IF  "$(CFG)" == "XGaloisLib - Win32 Release"


"$(INTDIR)\XGaloisMathCore_i386.obj" : $(SOURCE) "$(INTDIR)"


!ELSEIF  "$(CFG)" == "XGaloisLib - Win32 Debug"


"$(INTDIR)\XGaloisMathCore_i386.obj"	"$(INTDIR)\XGaloisMathCore_i386.sbr" : $(SOURCE) "$(INTDIR)"


!ENDIF 


!ENDIF 

