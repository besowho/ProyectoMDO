###########################################################################
## Makefile generated for MATLAB file/project 'ssmDetect'. 
## 
## Makefile     : ssmDetect_rtw.mk
## Generated on : Thu Mar 04 09:41:11 2021
## MATLAB Coder version: 2.7 (R2014b)
## 
## Build Info:
## 
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/ssmDetect.a
## Product type : static-library
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile
# COMPUTER                Computer type. See the MATLAB "computer" command.

PRODUCT_NAME              = ssmDetect
MAKEFILE                  = ssmDetect_rtw.mk
COMPUTER                  = MACI64
MATLAB_ROOT               = /Applications/MATLAB_R2014b.app
MATLAB_BIN                = /Applications/MATLAB_R2014b.app/bin
MATLAB_ARCH_BIN           = /Applications/MATLAB_R2014b.app/bin/maci64
MASTER_ANCHOR_DIR         = 
START_DIR                 = /Users/Edwards/Documents/SSM/CODE_TEST
ARCH                      = maci64
RELATIVE_PATH_TO_ANCHOR   = .

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Clang v3.1 | gmake (64-bit Mac)
# Supported Version(s):    3.1
# ToolchainInfo Version:   R2014b
# Specification Revision:  1.0
# 

#-----------
# MACROS
#-----------

ANSI_OPTS       = -fno-common -fexceptions
CPP_ANSI_OPTS   = -fno-common -fexceptions
ARCHS           = x86_64
XCODE_SDK_VER   = $(shell xcodebuild -showsdks | perl -anle 'BEGIN{@l = "";} push @l, $$F[-1] if /macosx/; END{ sort @l; $$_ = $$l[1]; s/macosx//; print $$_;}')
XCODE_SDK       = MacOSX$(XCODE_SDK_VER).sdk
XCODE_DEVEL_DIR = $(shell xcode-select -print-path)
XCODE_SDK_ROOT  = $(shell find $(XCODE_DEVEL_DIR) -name $(XCODE_SDK))

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# C Compiler: Clang C Compiler
CC = xcrun clang

# Linker: Clang Linker
LD = xcrun clang

# C++ Compiler: Clang C++ Compiler
CPP = xcrun clang++

# C++ Linker: Clang C++ Linker
CPP_LD = xcrun clang++

# Archiver: Clang Archiver
AR = xcrun ar

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_BIN)
MEX = $(MEX_PATH)/mex

# Download: Download
DOWNLOAD =

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%/bin/maci64
MAKE = $(MAKE_PATH)/gmake


#-------------------------
# Directives/Utilities
#-------------------------

CDEBUG              = -g
C_OUTPUT_FLAG       = -o
LDDEBUG             = -g
OUTPUT_FLAG         = -o
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = -o
CPPLDDEBUG          = -g
OUTPUT_FLAG         = -o
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @rm -f
ECHO                = @echo
MV                  = @mv
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = ruvs
CFLAGS               = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(ANSI_OPTS) \
                       -O0
CPPFLAGS             = -c -isysroot $(XCODE_SDK_ROOT) -arch $(ARCHS) $(CPP_ANSI_OPTS) \
                       -O0
CPP_LDFLAGS          = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -L"$(MATLAB_ARCH_BIN)"
CPP_SHAREDLIB_LDFLAGS  = -dynamiclib -isysroot $(XCODE_SDK_ROOT) -L"$(MATLAB_ARCH_BIN)" \
                         -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)
DOWNLOAD_FLAGS       =
EXECUTE_FLAGS        =
LDFLAGS              = -arch $(ARCHS) -isysroot $(XCODE_SDK_ROOT) -L"$(MATLAB_ARCH_BIN)"
MEX_CFLAGS           = -MATLAB_ARCH=$(ARCH) $(INCLUDES) \
                         \
                       COPTIMFLAGS="$(ANSI_OPTS)  \
                       -O0 \
                        $(DEFINES)" \
                         \
                       -silent
MEX_LDFLAGS          = LDFLAGS=='$$LDFLAGS'
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    = -dynamiclib -isysroot $(XCODE_SDK_ROOT) -L"$(MATLAB_ARCH_BIN)" \
                       -Wl,$(LD_NAMESPACE) $(LD_UNDEFS)

#--------------------
# File extensions
#--------------------

H_EXT               = .h
OBJ_EXT             = .o
C_EXT               = .c
EXE_EXT             =
SHAREDLIB_EXT       = .so
HPP_EXT             = .hpp
OBJ_EXT             = .o
CPP_EXT             = .cpp
EXE_EXT             =
SHAREDLIB_EXT       = .so
STATICLIB_EXT       = .a
MEX_EXT             = .mexmaci64
MAKE_EXT            = .mk


###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/ssmDetect.a
PRODUCT_TYPE = "static-library"
BUILD_TYPE = "Static Library"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(START_DIR)/codegen/lib/ssmDetect -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_STANDARD = -DMODEL=ssmDetect -DHAVESTDIO -DUSE_RTMODEL -DUNIX

DEFINES = $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/codegen/lib/ssmDetect/ssmDetect_rtwutil.c $(START_DIR)/codegen/lib/ssmDetect/ssmDetect_initialize.c $(START_DIR)/codegen/lib/ssmDetect/ssmDetect_terminate.c $(START_DIR)/codegen/lib/ssmDetect/ssmDetect.c $(START_DIR)/codegen/lib/ssmDetect/loadPriorModelFromDisk.c $(START_DIR)/codegen/lib/ssmDetect/rdivide.c $(START_DIR)/codegen/lib/ssmDetect/power.c $(START_DIR)/codegen/lib/ssmDetect/diag.c $(START_DIR)/codegen/lib/ssmDetect/ismatrix.c $(START_DIR)/codegen/lib/ssmDetect/inv.c $(START_DIR)/codegen/lib/ssmDetect/colon.c $(START_DIR)/codegen/lib/ssmDetect/abs.c $(START_DIR)/codegen/lib/ssmDetect/isequal.c $(START_DIR)/codegen/lib/ssmDetect/mean.c $(START_DIR)/codegen/lib/ssmDetect/combine_vector_elements.c $(START_DIR)/codegen/lib/ssmDetect/cov.c $(START_DIR)/codegen/lib/ssmDetect/sum.c $(START_DIR)/codegen/lib/ssmDetect/run_SSM.c $(START_DIR)/codegen/lib/ssmDetect/getUnknownWeightForTheFeatureModel.c $(START_DIR)/codegen/lib/ssmDetect/prod.c $(START_DIR)/codegen/lib/ssmDetect/normpdf.c $(START_DIR)/codegen/lib/ssmDetect/svd.c $(START_DIR)/codegen/lib/ssmDetect/sqrt.c $(START_DIR)/codegen/lib/ssmDetect/bsxfun.c $(START_DIR)/codegen/lib/ssmDetect/exp.c $(START_DIR)/codegen/lib/ssmDetect/imfilter.c $(START_DIR)/codegen/lib/ssmDetect/padarray.c $(START_DIR)/codegen/lib/ssmDetect/rot90.c $(START_DIR)/codegen/lib/ssmDetect/convn.c $(START_DIR)/codegen/lib/ssmDetect/eml_sort.c $(START_DIR)/codegen/lib/ssmDetect/mergePd.c $(START_DIR)/codegen/lib/ssmDetect/mldivide.c $(START_DIR)/codegen/lib/ssmDetect/getEdgeAndObjectsNoScaling.c $(START_DIR)/codegen/lib/ssmDetect/bwmorph.c $(START_DIR)/codegen/lib/ssmDetect/algbwmorph.c $(START_DIR)/codegen/lib/ssmDetect/extractTheLargestRegion.c $(START_DIR)/codegen/lib/ssmDetect/replacement_bwconncomp.c $(START_DIR)/codegen/lib/ssmDetect/unique.c $(START_DIR)/codegen/lib/ssmDetect/diff.c $(START_DIR)/codegen/lib/ssmDetect/extractTheLargestCurve.c $(START_DIR)/codegen/lib/ssmDetect/getOptimalLineImage_constrained.c $(START_DIR)/codegen/lib/ssmDetect/ObjectPart.c $(START_DIR)/codegen/lib/ssmDetect/suppressDetections.c $(START_DIR)/codegen/lib/ssmDetect/Object.c $(START_DIR)/codegen/lib/ssmDetect/ssmDetect_emxutil.c $(START_DIR)/codegen/lib/ssmDetect/rt_nonfinite.c $(START_DIR)/codegen/lib/ssmDetect/rtGetNaN.c $(START_DIR)/codegen/lib/ssmDetect/rtGetInf.c

ALL_SRCS = $(SRCS)

###########################################################################
## OBJECTS
###########################################################################

OBJS = ssmDetect_rtwutil.o ssmDetect_initialize.o ssmDetect_terminate.o ssmDetect.o loadPriorModelFromDisk.o rdivide.o power.o diag.o ismatrix.o inv.o colon.o abs.o isequal.o mean.o combine_vector_elements.o cov.o sum.o run_SSM.o getUnknownWeightForTheFeatureModel.o prod.o normpdf.o svd.o sqrt.o bsxfun.o exp.o imfilter.o padarray.o rot90.o convn.o eml_sort.o mergePd.o mldivide.o getEdgeAndObjectsNoScaling.o bwmorph.o algbwmorph.o extractTheLargestRegion.o replacement_bwconncomp.o unique.o diff.o extractTheLargestCurve.o getOptimalLineImage_constrained.o ObjectPart.o suppressDetections.o Object.o ssmDetect_emxutil.o rt_nonfinite.o rtGetNaN.o rtGetInf.o

ALL_OBJS = $(OBJS)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = 

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = -lm

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_BASIC)

###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build clean info prebuild download execute


all : build
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


prebuild : 


download : build


execute : download


###########################################################################
## FINAL TARGET
###########################################################################

#---------------------------------
# Create a static library         
#---------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS)
	@echo "### Creating static library "$(PRODUCT)" ..."
	$(AR) $(ARFLAGS)  $(PRODUCT) $(OBJS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.o : %.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : %.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/ssmDetect/%.c
	$(CC) $(CFLAGS) -o "$@" "$<"


%.o : $(START_DIR)/codegen/lib/ssmDetect/%.cpp
	$(CPP) $(CPPFLAGS) -o "$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : $(MAKEFILE) rtw_proj.tmw


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(PRODUCT)
	$(RM) $(ALL_OBJS)
	$(ECHO) "### Deleted all derived files."


