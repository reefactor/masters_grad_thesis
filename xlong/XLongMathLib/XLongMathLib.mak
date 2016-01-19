# Microsoft Developer Studio Generated NMAKE File, Based on XLongMathLib.dsp
!IF "$(CFG)" == ""
CFG=XLongMathLib - Win32 Debug
!MESSAGE No configuration specified. Defaulting to XLongMathLib - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "XLongMathLib - Win32 Release" && "$(CFG)" != "XLongMathLib - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "XLongMathLib.mak" CFG="XLongMathLib - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "XLongMathLib - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "XLongMathLib - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "XLongMathLib - Win32 Release"

OUTDIR=.\out
INTDIR=.\out
# Begin Custom Macros
OutDir=.\out
# End Custom Macros

ALL : "$(OUTDIR)\XLongMathLib.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\Xlong.obj"
	-@erase "$(INTDIR)\XLongMathLib.obj"
	-@erase "$(OUTDIR)\XLongMathLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /ML /W3 /GX /O2 /Ob2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XLongMathLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\XLongMathLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Xlong.obj" \
	"$(INTDIR)\XLongMathLib.obj"

"$(OUTDIR)\XLongMathLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "XLongMathLib - Win32 Debug"

OUTDIR=.\out
INTDIR=.\out
# Begin Custom Macros
OutDir=.\out
# End Custom Macros

ALL : "$(OUTDIR)\XLongMathLib.lib"


CLEAN :
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\Xlong.obj"
	-@erase "$(INTDIR)\XLongMathLib.obj"
	-@erase "$(OUTDIR)\XLongMathLib.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MLd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /Fp"$(INTDIR)\XLongMathLib.pch" /YX /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\XLongMathLib.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\XLongMathLib.lib" 
LIB32_OBJS= \
	"$(INTDIR)\Xlong.obj" \
	"$(INTDIR)\XLongMathLib.obj"

"$(OUTDIR)\XLongMathLib.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 

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


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("XLongMathLib.dep")
!INCLUDE "XLongMathLib.dep"
!ELSE 
!MESSAGE Warning: cannot find "XLongMathLib.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "XLongMathLib - Win32 Release" || "$(CFG)" == "XLongMathLib - Win32 Debug"
SOURCE=.\Xlong.cpp

"$(INTDIR)\Xlong.obj" : $(SOURCE) "$(INTDIR)"


SOURCE=.\XLongMathLib.cpp

"$(INTDIR)\XLongMathLib.obj" : $(SOURCE) "$(INTDIR)"



!ENDIF 

