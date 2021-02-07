# ALG2-TP1 project Makefile
# Variable expansions Makefile
# ==============================================================

# List of all global variables that are expected to be
#   customized according to the use of the user.
GLOBAL_VAR_LIST := CXX FLAGS SOURCE SOURCE_VAL_NAMES SOURCE_MAIN		 \
  SOURCE_UNIT SOURCE_MAIN_VAL_NAMES HEADER APPLIANCE								 \
  SOURCE_UNIT_VAL_NAMES BUILD MODULES HEADER_EXTENSION APP_EXTENSION \
  OBJECT_EXTENSION EXECUTABLE_EXTENSION MAIN_FILE TARGET						 \
  UNIT_MAIN_FILE UNIT_TARGET

# Set defaults of some variables (format DEFAULT_<VAR_NAME>)
DEFAULT_CXX   := g++
DEFAULT_FLAGS := -std=c++11 -Wall

DEFAULT_SOURCE := src

DEFAULT_SOURCE_VAL_NAMES := SOURCE_MAIN SOURCE_UNIT

DEFAULT_SOURCE_MAIN := main
DEFAULT_SOURCE_UNIT := unit

DEFAULT_SOURCE_MAIN_VAL_NAMES := HEADER APPLIANCE

DEFAULT_HEADER    := header
DEFAULT_APPLIANCE := appliance

DEFAULT_SOURCE_UNIT_VAL_NAMES = $(MODULES)

DEFAULT_BUILD := build

DEFAULT_MODULES :=

DEFAULT_HEADER_EXTENSION     := hpp
DEFAULT_APP_EXTENSION        := cpp
DEFAULT_OBJECT_EXTENSION     := o
DEFAULT_EXECUTABLE_EXTENSION := exe

DEFAULT_MAIN_FILE = $(APPLIANCE)/main.$(APP_EXTENSION)
DEFAULT_TARGET    = $(BUILD)/main.$(EXECUTABLE_EXTENSION)

DEFAULT_UNIT_MAIN_FILE = $(SOURCE_UNIT)/unit_main.cpp
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

# Add prefix to directories inside ~$(SOURCE)~
override SOURCE_MAIN := $(SOURCE)/$(SOURCE_MAIN)
override SOURCE_UNIT := $(SOURCE)/$(SOURCE_UNIT)

# Add prefix to directories inside ~$(SOURCE_MAIN)~
$(eval \
$(foreach src_dir, $(SOURCE_MAIN_VAL_NAMES),\
override $(src_dir) := $(SOURCE_MAIN)/$($(src_dir))$(C_NL)) \
)

vpath %.$(APP_EXTENSION) $(patsubst %, $(APPLIANCE)/%, $(MODULES))

# Header files list
HEADER_FILES := $(wildcard $(patsubst %, $(HEADER)/%/*.$(HEADER_EXTENSION), $(MODULES)))
# Appliance files list
APPLIANCE_FILES := $(wildcard $(patsubst %, $(APPLIANCE)/%/*.$(APP_EXTENSION), $(MODULES)))

# Searches for files with ~$(OBJECT_EXTENSION)~ extension
OBJECT_FILES := $(patsubst $(APPLIANCE)%$(APP_EXTENSION), $(BUILD)%$(OBJECT_EXTENSION), $(APPLIANCE_FILES))

# Compiled files directory list
OBJECT_DIRS := $(BUILD)

# Command for compiling each object
COMPIL_OBJECT_CODE = $(CXX) $(FLAGS) -I $(HEADER) -c $< -o $@
# Links objects
LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER) $(OBJECT_FILES) $(MAIN_FILE) -o $@

# For use in creating directories rule
#-- Do not use "/" in the end!
#-- Otherwise it won't recognize the directory's existance.
OBJECT_MOD_DIRS  := $(foreach mod, $(MODULES), $(patsubst %, %/$(mod), $(OBJECT_DIRS)))
BUILD_MODS       := $(patsubst %, $(BUILD)/%, $(MODULES))

TARGET_DEPENDENCIES := $(MAIN_FILE) $(HEADER_FILES) $(APPLIANCE_FILES) $(BUILD_MODS) $(OBJECT_FILES)

# Regarding unit rule
UNIT_FILES := $(wildcard $(patsubst %, $(SOURCE_UNIT)/%/*.$(APP_EXTENSION), $(MODULES)))

$(info $(UNIT_FILES))

UNIT_LINK_CODE = $(CXX) $(FLAGS) -I $(HEADER) $(OBJECT_FILES) $(UNIT_FILES) $(UNIT_MAIN_FILE) -o $(UNIT_TARGET)

UNIT_TARGET_DEPENDENCIES := $(UNIT_MAIN_FILE) $(UNIT_FILES) $(HEADER_FILES) $(APPLIANCE_FILES) $(BUILD_MODS) $(OBJECT_FILES)
