#
# Copyright 2011 Alan Burlison, alan@bleaklow.com.  All rights reserved.
# Use is subject to license terms.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#  1. Redistributions of source code must retain the above copyright notice,
#     this list of conditions and the following disclaimer.
#
#  2. Redistributions in binary form must reproduce the above copyright notice,
#     this list of conditions and the following disclaimer in the documentation
#     and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY ALAN BURLISON "AS IS" AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL ALAN BURLISON OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# Makefile for building Arduino projects outside of the Arduino environment
#
# This makefile should be included into a per-project Makefile of the following
# form:
#
# ----------
# BOARD = mega
# PORT = /dev/term/0
# INC_DIRS = ../common
# LIB_DIRS = ../libraries/Task ../../libraries/VirtualWire
# include ../../Makefile.master
# ----------
#
# Where:
#   BOARD    : Arduino board type, from $(ARD_HOME)/hardware/boards.txt
#   PORT     : USB port
#   INC_DIRS : List pf directories containing header files
#   LIB_DIRS : List of directories containing library source
#
# Before using this Makefile you can adjust the following macros to suit
# your environment, either by editing this file directly or by defining them in
# the Makefile that includes this one, in which case they will override the
# definitions below:
#   ARD_REV      : arduino software revision, e.g. 0017, 0018
#   ARD_HOME     : installation directory of the Arduino software.
#   ARD_BIN      : location of compiler binaries
#   AVRDUDE      : location of avrdude executable
#   AVRDUDE_CONF : location of avrdude configuration file
#   PROGRAMMER   : avrdude programmer type
#   MON_SPEED    : serial monitor speed
#   EXTRA_FLAGS  : any extra flags that should be passed to the compilers
#

# Global configuration.
include Makefile.silencer

# Platform-specific settings.
PLATFORM = $(shell uname -s)
ifeq "$(PLATFORM)" "SunOS"
    define run-monitor
	${QE} "[RUN  ] Running monitor ..."
	${QS}gnome-terminal -t '$(BOARD) $(PORT)' \
	    -e 'env -i tip -$(MON_SPEED) $(PORT)' &
    endef
    define kill-monitor
	${QE} "[KILL ] Killing monitor ..."
	- ${QS}pkill -f 'tip.*$(PORT)'
    endef
else ifeq "$(PLATFORM)" "Linux"
    define run-monitor
	${QE} "[RUN  ] Running monitor ..."
	${QS}screen $(PORT) $(MON_SPEED)
    endef
    define kill-monitor
	${QE} "[KILL ] Killing monitor ..."
	- ${QS}pkill -f 'screen.*$(PORT)'
    endef
else ifeq "$(PLATFORM)" "Darwin"
    $(error No monitor command for platform $(PLATFORM))
else
    $(error Unknown platform $(PLATFORM))
endif

# Standard macros.
SKETCH = $(notdir $(CURDIR))
BUILD_DIR = build
VPATH = $(LIB_DIRS)

# Build tools.
CC = gcc
CXX = g++
CXXFILT = c++filt
OBJCOPY = objcopy
OBJDUMP = objdump
AR = ar
SIZE = size
NM = nm
LD = gcc
MKDIR = mkdir -p
RM = rm -rf
MV = mv -f

# Compiler flags.
INC_FLAGS ?= \
    $(addprefix -I,$(INC_DIRS)) $(addprefix -I,$(LIB_DIRS)) -I$(ARD_SRC_DIR)
INC_FLAGS += -I$(ARD_HOME)/hardware/arduino/variants/standard -I$(ARD_HOME)/hardware/arduino/variants/mega
INC_FLAGS += -pthread -lX11 -lGL -lGLU -lglut
ARD_FLAGS = -DF_CPU=$(F_CPU) -DARDUINO=$(ARD_REV)
ARD_FLAGS += -pthread -lX11 -lGL -lGLU -lglut
C_CXX_FLAGS = \
    -Wall -Wextra -Wundef -Wno-unused-parameter \
    -fdiagnostics-show-option -g -Wa,-adhlns=$(BUILD_DIR)/$*.lst \
    $(EXTRA_FLAGS)
C_FLAGS = \
    -std=gnu99 -Wno-old-style-declaration $(C_CXX_FLAGS)
CXX_FLAGS = \
    $(C_CXX_FLAGS)

# Optimiser flags.
#     optimise for size, unsigned by default, pack data.
#     separate sections, drop unused ones, shorten branches, jumps.
#     don't inline, vectorise loops. no exceptions.
#     no os preamble, use function calls in prologues.
# http://gcc.gnu.org/onlinedocs/gcc-4.3.5/gcc/
# http://www.tty1.net/blog/2008-04-29-avr-gcc-optimisations_en.html
OPT_FLAGS = \
    -Os -finline -fgcse -fcrossjumping \
    -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
    -ffunction-sections -fdata-sections -Wl,--gc-sections,--relax \
    -fno-inline-small-functions -fno-tree-scev-cprop -fno-exceptions \
    -ffreestanding 

# Build parameters.
IMAGE = $(BUILD_DIR)/$(SKETCH)
ARD_C_SRC = $(wildcard $(ARD_SRC_DIR)/*.c)
ARD_CXX_SRC = $(wildcard $(ARD_SRC_DIR)/*.cpp)
ARD_C_OBJ = $(patsubst %.c,%.o,$(notdir $(ARD_C_SRC)))
ARD_CXX_OBJ = $(patsubst %.cpp,%.o,$(notdir $(ARD_CXX_SRC)))
ARD_LIB = arduino
ARD_AR = $(BUILD_DIR)/lib$(ARD_LIB).a
ARD_AR_OBJ = $(ARD_AR)($(ARD_C_OBJ) $(ARD_CXX_OBJ))

# Workaround for http://gcc.gnu.org/bugzilla/show_bug.cgi?id=34734
$(ARD_AR)(Tone.o) : CXX_FLAGS += -w

# Sketch libraries.
LIB_C_SRC = $(foreach ld,$(LIB_DIRS),$(wildcard $(ld)/*.c))
LIB_CXX_SRC = $(foreach ld,$(LIB_DIRS),$(wildcard $(ld)/*.cpp))
LIB_SRC = $(LIB_C_SRC) $(LIB_CXX_SRC)
ifneq "$(strip $(LIB_C_SRC) $(LIB_CXX_SRC))" ""
	LIB_C_OBJ = $(patsubst %.c,%.o,$(notdir $(LIB_C_SRC)))
	LIB_CXX_OBJ = $(patsubst %.cpp,%.o,$(notdir $(LIB_CXX_SRC)))
	LIB_LIB = library
	LIB_AR = $(BUILD_DIR)/lib$(LIB_LIB).a
	LIB_AR_OBJ = $(LIB_AR)($(LIB_C_OBJ) $(LIB_CXX_OBJ))
	LIB_LD_FLAG = -l$(LIB_LIB)
endif

# Sketch PDE source.
SKT_PDE_SRC = $(wildcard *.pde)
ifneq "$(strip $(SKT_PDE_SRC))" ""
	SKT_PDE_OBJ = $(BUILD_DIR)/$(SKETCH)_pde.o
endif

# C and C++ source.
SKT_C_SRC = $(wildcard *.c)
SKT_CXX_SRC = $(wildcard *.cpp)
ifneq "$(strip $(SKT_C_SRC) $(SKT_CXX_SRC))" ""
	SKT_C_OBJ = $(patsubst %.c,%.o,$(SKT_C_SRC))
	SKT_CXX_OBJ = $(patsubst %.cpp,%.o,$(SKT_CXX_SRC))
	SKT_LIB = sketch
	SKT_AR = $(BUILD_DIR)/lib$(SKT_LIB).a
	SKT_AR_OBJ = $(SKT_AR)($(SKT_C_OBJ) $(SKT_CXX_OBJ))
	SKT_LD_FLAG = -l$(SKT_LIB)
endif

# Common rule bodies.
define run-cc
	${QE} "[CC   ] Compiling $< ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(CC) -c $(C_FLAGS) $(OPT_FLAGS) $(ARD_FLAGS) $(INC_FLAGS) \
	    -MD -MT '$@($%)' -MF $(@D)/.$(@F)_$*.dep $< -o $(BUILD_DIR)/$%
	${QE} "[AR   ] Archiving $@($<) ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(AR) rc $@ $(BUILD_DIR)/$%
	${QS}$(RM) $(BUILD_DIR)/$%
	${QS}$(CXXFILT) < $(BUILD_DIR)/$*.lst > $(BUILD_DIR)/$*.lst.tmp
	${QS}$(MV) $(BUILD_DIR)/$*.lst.tmp $(BUILD_DIR)/$*.lst
endef

define run-cxx
	${QE} "[CXX  ] Compiling $< ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(CXX) -c $(CXX_FLAGS) $(OPT_FLAGS) $(ARD_FLAGS) $(INC_FLAGS) \
	    -MD -MT '$@($%)' -MF $(@D)/.$(@F)_$*.dep $< -o $(BUILD_DIR)/$%
	${QE} "[AR   ] Archiving $@($<) ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(AR) rc $@ $(BUILD_DIR)/$%
	${QS}$(RM) $(BUILD_DIR)/$%
	${QS}$(CXXFILT) < $(BUILD_DIR)/$*.lst > $(BUILD_DIR)/$*.lst.tmp
	${QS}$(MV) $(BUILD_DIR)/$*.lst.tmp $(BUILD_DIR)/$*.lst
endef

# Rules.
.PHONY : all clean upload monitor upload_monitor

all : $(BUILD_DIR) $(IMAGE).hex

clean :
	${QE} "[CLEAN] Cleaning $(BUILD_DIR) ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(RM) $(BUILD_DIR)

$(BUILD_DIR) :
	${QE} "[MKDIR] Creating $@ ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(MKDIR) $@

$(SKT_PDE_OBJ) : $(SKT_PDE_SRC) x86_main.tpl
	${QE} "[CXX  ] Compiling $< ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}cat $(SKT_PDE_SRC) > $(BUILD_DIR)/$(SKETCH)_pde.cpp
	${QS}cat "x86_main.tpl" >> $(BUILD_DIR)/$(SKETCH)_pde.cpp
	${QS}cd $(BUILD_DIR) && $(CXX) -c $(subst build/,,$(CXX_FLAGS)) \
	    $(OPT_FLAGS) $(ARD_FLAGS) -I.. \
	    $(patsubst -I..%,-I../..%,$(INC_FLAGS)) \
	    $(SKETCH)_pde.cpp -o $(@F)

(%.o) : $(ARD_SRC_DIR)/%.c
	$(run-cc)

(%.o) : $(ARD_SRC_DIR)/%.cpp
	$(run-cxx)

(%.o) : %.c
	$(run-cc)

(%.o) : %.cpp
	$(run-cxx)

$(BUILD_DIR)/%.d : %.c
	$(run-cc-d)

$(BUILD_DIR)/%.d : %.cpp
	$(run-cxx-d)

# The multiple "-lm" flags are to work around a linker bug.
$(IMAGE).hex : $(LIB_AR_OBJ) $(SKT_AR_OBJ) $(SKT_PDE_OBJ) 
	${QE} "[LD   ] Linking $@ ..."|sed -e "s/$(shell echo `pwd`|sed -e 's/\//\\\//g')/./g"
	${QS}$(LD) -lm $(CXX_FLAGS) $(OPT_FLAGS) $(ARD_FLAGS) -L$(BUILD_DIR) \
	    $(SKT_PDE_OBJ) $(SKT_LD_FLAG) $(LIB_LD_FLAG) \
	    -lm -o $(IMAGE).elf
	${QS}$(OBJCOPY) -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load \
	    --no-change-warnings --change-section-lma .eeprom=0 $(IMAGE).elf \
	    $(IMAGE).eep
	${QS}$(OBJCOPY) -O ihex -R .eeprom $(IMAGE).elf $(IMAGE).hex
	${QS}$(OBJDUMP) -h -S $(IMAGE).elf | $(CXXFILT) -t > $(IMAGE).lst
	${QS}$(SIZE) $(IMAGE).elf

upload : all
	$(kill-monitor)
	${QE} "[AVR  ] Uploading ..."
	- ${QS}$(AVRDUDE) -V -C$(AVRDUDE_CONF) -p$(MCU) -c$(PROGRAMMER) -P$(PORT) \
	    -b$(UPLOAD_SPEED) -D -Uflash:w:$(IMAGE).hex:i

monitor :
	$(kill-monitor)
	$(run-monitor)

upload_monitor : upload monitor

-include $(wildcard $(BUILD_DIR)/.*.dep))
