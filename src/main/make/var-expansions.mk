# ALG2-TP1 project Makefile
# Variable expansions Makefile
# ==============================================================

# List of all global variables that are expected to be
#   customized according to the use of the user.
GLOBAL_VAR_LIST := CXX FLAGS SOURCE SOURCE_MAIN SOURCE_UNIT			\
  HEADER_MAIN APPLIANCE_MAIN HEADER_UNIT APPLIANCE_UNIT BUILD		\
  BUILD_MAIN BUILD_UNIT MODULES HEADER_EXTENSION APP_EXTENSION	\
  OBJECT_EXTENSION EXECUTABLE_EXTENSION MAIN_FILE TARGET				\
  UNIT_MAIN_FILE UNIT_TARGET

# Set defaults of some variables (format DEFAULT_<VAR_NAME>)
DEFAULT_CXX   := g++
DEFAULT_FLAGS := -std=c++11 -Wall

DEFAULT_SOURCE := src

DEFAULT_SOURCE_MAIN = $(SOURCE)/main
DEFAULT_SOURCE_UNIT = $(SOURCE)/unit

DEFAULT_HEADER_MAIN    = $(SOURCE_MAIN)/header
DEFAULT_APPLIANCE_MAIN = $(SOURCE_MAIN)/appliance
DEFAULT_HEADER_UNIT    = $(SOURCE_UNIT)/header
DEFAULT_APPLIANCE_UNIT = $(SOURCE_UNIT)/appliance

DEFAULT_BUILD := build

DEFAULT_BUILD_MAIN = $(BUILD)/main
DEFAULT_BUILD_UNIT = $(BUILD)/unit

DEFAULT_MODULES :=

DEFAULT_HEADER_EXTENSION     := hpp
DEFAULT_APP_EXTENSION        := cpp
DEFAULT_OBJECT_EXTENSION     := o
DEFAULT_EXECUTABLE_EXTENSION := exe

DEFAULT_MAIN_FILE = $(APPLIANCE_MAIN)/main.$(APP_EXTENSION)
DEFAULT_TARGET    = $(BUILD)/main.$(EXECUTABLE_EXTENSION)

DEFAULT_UNIT_MAIN_FILE = $(APPLIANCE_UNIT)/unit_main.cpp
DEFAULT_UNIT_TARGET    = $(BUILD)/unit_main.exe

# This call only affects those variables that have a default
#   value defined.
$(call lp_apply_defaults, $(GLOBAL_VAR_LIST))

# Checks definition of global variables.
# Function from inspection-functions file ~i_check_vars~ used here.
GLOBAL_VAR_STATUS :=  $(shell $(call i_check_vars, $(GLOBAL_VAR_LIST)))
temp_status := $(lastword $(GLOBAL_VAR_STATUS))
ifneq "$(temp_status)" "0"
  $(call e_fatal, $(temp_status) undefined global variables: \
    $(wordlist 1, $(temp_status), $(GLOBAL_VAR_STATUS)). \
    Verify file $(F_GLOBAL_VARS))
endif
undefine temp_status

# An empty space character
define C_SP =
 
endef

# A newline character
define C_NL :=


endef

vpath %.$(APP_EXTENSION) $(patsubst %, $(APPLIANCE_MAIN)/%, $(MODULES))

# Header files list
HEADER_MAIN_FILES := $(wildcard $(patsubst %, $(HEADER_MAIN)/%/*.$(HEADER_EXTENSION), $(MODULES)))
# Appliance files list
APPLIANCE_MAIN_FILES := $(wildcard $(patsubst %, $(APPLIANCE_MAIN)/%/*.$(APP_EXTENSION), $(MODULES)))

HEADER_UNIT_FILES    := $(wildcard $(patsubst %, $(HEADER_UNIT)/%/*.$(HEADER_EXTENSION), $(MODULES)))
APPLIANCE_UNIT_FILES := $(wildcard $(patsubst %, $(APPLIANCE_UNIT)/%/*.$(APP_EXTENSION), $(MODULES)))

# Searches for files with ~$(OBJECT_EXTENSION)~ extension
OBJECT_MAIN_FILES := $(patsubst $(APPLIANCE_MAIN)%$(APP_EXTENSION), $(BUILD_MAIN)%$(OBJECT_EXTENSION), $(APPLIANCE_MAIN_FILES))
OBJECT_UNIT_FILES := $(patsubst $(APPLIANCE_UNIT)%$(APP_EXTENSION), $(BUILD_UNIT)%$(OBJECT_EXTENSION), $(APPLIANCE_UNIT_FILES))

# Compiled files directory list
OBJECT_DIRS := $(BUILD_MAIN) $(BUILD_UNIT)

# Command for compiling each object
COMPIL_OBJECT_CODE_MAIN = $(CXX) $(FLAGS) -I $(HEADER_MAIN) -c $< -o $@
# Links objects
LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER_MAIN) $(OBJECT_MAIN_FILES) $(MAIN_FILE) -o $@

COMPIL_OBJECT_CODE_UNIT = $(CXX) $(FLAGS) -I $(HEADER_MAIN) -I $(HEADER_UNIT) -c $< -o $@
UNIT_LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER_MAIN) -I $(HEADER_UNIT) $(OBJECT_MAIN_FILES) $(OBJECT_UNIT_FILES) $(UNIT_MAIN_FILE) -o $(UNIT_TARGET)

# For use in creating directories rule
#-- Do not use "/" in the end!
#-- Otherwise it won't recognize the directory's existance.
OBJECT_MOD_DIRS  := $(foreach mod, $(MODULES), $(foreach obj_dir, $(OBJECT_DIRS), $(patsubst %, %/$(mod), $(obj_dir))))

BUILD_MODS_MAIN := $(patsubst %, $(BUILD_MAIN)/%, $(MODULES))
BUILD_MODS_UNIT := $(patsubst %, $(BUILD_UNIT)/%, $(MODULES))

TARGET_DEPENDENCIES := $(MAIN_FILE) $(HEADER_MAIN_FILES) $(APPLIANCE_MAIN_FILES) $(BUILD_MODS_MAIN) $(OBJECT_MAIN_FILES)

UNIT_TARGET_DEPENDENCIES := $(UNIT_MAIN_FILE) $(HEADER_UNIT_FILES) $(APPLIANCE_UNIT_FILES) $(HEADER_MAIN_FILES) $(APPLIANCE_MAIN_FILES) $(BUILD_MODS_UNIT) $(OBJECT_MAIN_FILES) $(OBJECT_UNIT_FILES)
